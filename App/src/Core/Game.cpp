#include <Siv3D.hpp>
#include "Game.hpp"

Game::Game()
	: m_renderTexture{ Scene::Size(),TextureFormat::R8G8B8A8_Unorm_SRGB,HasDepth::Yes }
	, m_cam{ m_renderTexture.size(), Config::CamFOV, Config::CamInitialPosition, Vec3{ 15, 0, 15 } }
	, m_cameraController{ m_cam }
	, m_ps{ HLSL{ U"example/shader/hlsl/forward_triplanar.hlsl",U"PS"} }
	, m_tex{ U"example/texture/uv.png" }
	, m_selectedTileIndex{ 14,14 }
	, m_font{ 20 }
	, m_bgm{ Audio::Stream, U"music/bgm/bgm.mp3", Loop::Yes }
	, uiFlg{ true }
{
	if (!m_ps) throw Error{ U"Failed to load PixelShader" };		//パスが間違っているとき任意でエラーを出すようにできる
	initLighting();
	m_title.Init();
	m_fader.startFadeIn();		//フェードイン処理開始

	//所持資材を0で初期化
	for (const auto& type : allResources)
	{
		m_playerResources[type] = 0;
	}

	//ArchitectUiに建築ハンドラを設定
	architectUi.setBuildHandler([this](int type) {
		this->startBuilding(type);
	});
	//ArchitectUiに資源獲得ハンドラを設定
	architectUi.setResourceHandler([this](int type) {
		//this->startResourceGathering(type);
		this->debugStartResourceGathering(type);	//即時採取
	});
	//ArchitectUiに資源加工ハンドラを設定
	architectUi.setProcessHandler([this](int type) {
		this->startProcessing(type);
	});
	//ArchitectUiに建築コスト情報を設定
	architectUi.setBuildCosts(&s_buildCosts);
	//ArchitectUiに所持資源情報を設定
	architectUi.setPlayerResources(&m_playerResources);
}

void Game::initLighting() const
{
	Graphics3D::SetGlobalAmbientColor(ColorF(0.5));
	Graphics3D::SetSunColor(ColorF(1.0));								//平行光
	Graphics3D::SetSunDirection(Vec3(-0.2, 1, -0.2).normalized());		//normalized()→スクリーン座標を標準化するため
}

/*
void Game::updateCamera()
{
	// 選択中のタイルの3D座標を計算
	const double x_gap = (m_selectedTileIndex.col % 2 == 1) ? 0.5 : 0;
	const Vec3 targetPos = Vec3{ m_selectedTileIndex.row + x_gap, 0, 0.866 * m_selectedTileIndex.col };

	// カメラの目標位置を設定
	const Vec3 cameraOffset = Vec3{ 10, 15, -10 }; // 斜め上からの俯瞰
	const Vec3 newEyePos = targetPos - cameraOffset;

	// CameraControllerのsetViewを呼び出す
	m_cameraController.setView(newEyePos, targetPos);
}*/

//選択中のタイルをハイライト
void Game::drawSelection() const
{
	const double x_gap = (m_selectedTileIndex.col % 2 == 1) ? 0.5 : 0;
	const Vec3 center3D = Vec3{ m_selectedTileIndex.row + x_gap, 0, 0.866 * m_selectedTileIndex.col };

	const double R = 1.0 / Math::Sqrt(3);	//6角形の中心から頂点までの距離
	constexpr double highlightY = 0.2;		//描画の高さ

	s3d::Array<s3d::Vec3> points3D;			//六角形を構成する3D頂点配列

	//頂点を生成
	for (int i = 0; i < 6; ++i)
	{
		const double angle = 90_deg + i * 60_deg;

		const double x = center3D.x + R * Cos(angle);
		const double z = center3D.z + R * Sin(angle);		//Z軸が画面奥方向

		points3D.push_back({ x, highlightY, z });
	}

	//辺の描画
	const ColorF highlightColor = Palette::Yellow;
	//constexpr double thickness = 0.1;	//線の太さ
	for (int i = 0; i < 6; ++i)
	{
		const Vec3& p1 = points3D[i];
		const Vec3& p2 = points3D[(i + 1) % 6];		//最後の頂点は最初に戻る

		Line3D{ p1, p2 }.draw(highlightColor);
	}
}

bool Game::Update()
{
	// マネージャの状態に応じて処理を分岐
	switch (m_managerState)
	{
	case ManagerState::Standby:
		// 現在のシーンの更新
		if (m_currentScene == SceneState::Title)
		{
			m_title.Update();
			if (m_title.isRequestToChangeScene())
			{
				m_managerState = ManagerState::FadeOut;
				m_fader.startFadeOut();
			}
		}
		else if (m_currentScene == SceneState::Game)
		{
			//m_cam.update(2.0);
			m_cameraController.Update(Scene::DeltaTime());
			Graphics3D::SetCameraTransform(m_cam);

			m_bgm.play();

			infoUi.setResources(m_playerResources);

			//WASDキーによるタイル選択
			int newRow = m_selectedTileIndex.row;
			int newCol = m_selectedTileIndex.col;

			if (s3d::KeyW.down()) { newCol++; }
			if (s3d::KeyS.down()) { newCol--; }
			if (s3d::KeyA.down()) { newRow--; }
			if (s3d::KeyD.down()) { newRow++; }

			//新しい座標が有効範囲内か確認
			const auto& tileTypes = tile.getTileTypes();
			if (newCol >= 0 && newCol < tileTypes.size() && newRow >= 0 && newRow < tileTypes[0].size())
			{
				m_selectedTileIndex = { newRow, newCol };
				infoUi.setDrawInfo(m_selectedTileIndex, tile);
			}

			//選択されたタイルの種類に応じてUIを表示
			const int tileType = tileTypes[m_selectedTileIndex.col][m_selectedTileIndex.row];
			architectUi.show(tileType);

			// 進行中の資源獲得タスクを更新
			for (auto& job : m_activeJobs)
			{
				job.elapsedTime += Scene::DeltaTime();
			}

			// 進行中の建築タスクを更新
			for (auto& job : m_activeBuildJobs)
			{
				job.elapsedTime += Scene::DeltaTime();
			}

			// 完了したタスクを処理
			std::erase_if(m_activeJobs, [this](const ResourceJob& job)
			{
					if (job.elapsedTime >= job.requiredTime)
					{
						// 資源をプレイヤーに加算
						for (const auto& res : job.resources)
						{
							m_playerResources[res.type] += res.amount;
						}
						//Print << U"資源の獲得が完了しました！";
						return true; // 完了したタスクをリストから削除
					}
					return false; // 継続
			});

			std::erase_if(m_activeBuildJobs, [this](const BuildJob& job)
			{
				if (job.elapsedTime >= job.requiredTime)
				{
					//モデルを置き換える
					tile.setTileModel(job.index, tile.getModel(job.tileType));
					//タイルタイプを更新する
					tile.updateTileType(job.index, job.tileType);

					//デバッグ
					//Print << U"建築完了: ({}, {})"_fmt(job.index.row, job.index.col);
					return true;
				}
				return false;
			});

			if (uiFlg && KeyAlt.down()) { uiFlg = false; }
			else if (!uiFlg && KeyAlt.down()) { uiFlg = true; }

			// ... 既存のデバッグ表示 ...
			/*for (const auto& pair : m_playerResources)
			{
				Print << U"{} : {}個"_fmt(ToString(pair.first), pair.second);
			}*/

		}
		break;

	case ManagerState::FadeOut:
		m_fader.Update();
		if (m_fader.isFinished() && m_fader.getAlpha() >= 1.0)
		{
			m_managerState = ManagerState::ChangeScene;
		}
		break;

	case ManagerState::ChangeScene:
		if (m_currentScene == SceneState::Title)
		{
			m_currentScene = SceneState::Game;
			//updateCamera();
		}
		else
		{
			m_currentScene = SceneState::Title;
		}
		m_managerState = ManagerState::FadeIn;
		m_fader.startFadeIn();
		break;

	case ManagerState::FadeIn:
		m_fader.Update();
		if (m_fader.isFinished() && m_fader.getAlpha() <= 0.0)
		{
			m_managerState = ManagerState::Standby;
		}
		break;
	}

	// WASDキーによるタイル選択が行われたかどうかにかかわらず、毎フレームカメラを更新する
	if (m_currentScene == SceneState::Game)
	{
		//updateCamera();
	}

	// === デバッグ表示 ===
	//Print << U"Selected Tile: ({}, {})"_fmt(m_selectedTileIndex.row, m_selectedTileIndex.col);

	return true;
}

void Game::Draw()
{
	if (m_currentScene == SceneState::Title)
	{
		m_title.Draw();
	}
	else if (m_currentScene == SceneState::Game)
	{
		const ColorF bg{ 0.1, 0.4, 1.0 };
		const ScopedRenderTarget3D target{ m_renderTexture.clear(bg) };
		Graphics3D::SetPSTexture(0, m_tex);

		tile.Draw();
		drawSelection();		//選択中のタイルをハイライト表示

		//建築残り時間ゲージの描画
		for (const auto& job : m_activeBuildJobs)
		{
			//タイル中心の3D座標計算
			const GridIndex& index = job.index;
			const double x_gap = (index.col % 2 == 1) ? 0.5 : 0;
			const Vec3 tileCenter = Vec3{ index.row + x_gap, 0, 0.866 * index.col };

			//ゲージの中心座標
			const Vec3 gaugeCenter = tileCenter + Vec3(0, 1.0, 0);	//Y軸方向に1.0上

			//進行度の計算（0.0から1.0）
			const double progress = s3d::Min(job.elapsedTime / job.requiredTime, 1.0);

			//ゲージのサイズ
			constexpr double gaugeWidth = 0.8;	//ゲージの幅
			constexpr double gaugeHeight = 0.1; //ゲージの高さ
			constexpr double gaugeDepth = 0.1;	//ゲージの奥行き

			//ゲージ全体の枠（背景）を描画
			const Box frameBox{ gaugeCenter, gaugeWidth, gaugeHeight, gaugeDepth };
			frameBox.drawFrame(ColorF(1.0, 0.0, 1.0, 1.0));

			//ゲージの進捗を描画
			if (progress < 1.0)
			{
				//埋まり部分の幅
				const double filledWidth = gaugeWidth * progress;
				//ゲージの左端から伸びる
				const double xOffset = -(gaugeWidth - filledWidth) / 2.0;

				const Vec3 filledCenter = gaugeCenter + Vec3(xOffset, 0, 0);
				const Box filledBox{ filledCenter, filledWidth, gaugeHeight * 0.9, gaugeDepth * 0.9 };	//枠より少し小さくする

				filledBox.draw(ColorF(1.0, 0.5, 1.0, 0.9));
			}
		}

		//資源採取ジョブのゲージ描画を【追加】
		for (const auto& job : m_activeJobs)
		{
			//タイル中心の3D座標計算
			const GridIndex& index = job.index;
			const double x_gap = (index.col % 2 == 1) ? 0.5 : 0;
			const Vec3 tileCenter = Vec3{ index.row + x_gap, 0, 0.866 * index.col };

			//ゲージの中心座標 (Y軸方向に1.0上)
			const Vec3 gaugeCenter = tileCenter + Vec3(0, 1.0, 0);

			//進行度の計算（0.0から1.0）
			const double progress = s3d::Min(job.elapsedTime / job.requiredTime, 1.0);

			//ゲージのサイズ
			constexpr double gaugeWidth = 0.8;	//ゲージの幅
			constexpr double gaugeHeight = 0.1; //ゲージの高さ
			constexpr double gaugeDepth = 0.1;	//ゲージの奥行き

			//ゲージ全体の枠（背景）を描画
			const Box frameBox{ gaugeCenter, gaugeWidth, gaugeHeight, gaugeDepth };
			frameBox.drawFrame(ColorF(0.8, 0.3, 0.0, 0.8));

			//ゲージの進捗を描画 (建築と区別するため、例えば青色に設定)
			if (progress < 1.0)
			{
				//埋まり部分の幅
				const double filledWidth = gaugeWidth * progress;
				//ゲージの左端から伸びる
				const double xOffset = -(gaugeWidth - filledWidth) / 2.0;

				const Vec3 filledCenter = gaugeCenter + Vec3(xOffset, 0, 0);
				const Box filledBox{ filledCenter, filledWidth, gaugeHeight * 0.9, gaugeDepth * 0.9 };	//枠より少し小さくする

				filledBox.draw(ColorF(1.0, 0.7, 0.0, 0.9));
			}
		}

		Graphics3D::Flush();
		m_renderTexture.resolve();
		Shader::LinearToScreen(m_renderTexture);

		if (uiFlg)
		{
			infoUi.Draw();
			architectUi.Draw();
		}
	}
	
	//// === デバッグ表示 ===
	//// 現在のシーン状態を画面左上に表示する
	//if (m_currentScene == SceneState::Title)
	//{
	//	font(U"SceneState: Title").draw(10, 10);
	//}
	//else
	//{
	//	font(U"SceneState: Game").draw(10, 10);
	//}
	//// 現在のシーンマネージャーを画面左上に表示する
	//if (m_managerState == ManagerState::FadeIn)
	//{
	//	font(U"ManagerState: FadeIn").draw(10, 30);
	//}
	//else if(m_managerState == ManagerState::Standby)
	//{
	//	font(U"SceneState: Standby").draw(10, 30);
	//}
	//else if (m_managerState == ManagerState::FadeOut)
	//{
	//	font(U"SceneState: FadeOut").draw(10, 30);
	//}
	//else if (m_managerState == ManagerState::ChangeScene)
	//{
	//	font(U"SceneState: ChangeScene").draw(10, 30);
	//}

	m_fader.Draw();
}

void Game::startBuilding(int buildingType)
{
	//Print << U"startBuilding が呼ばれました";
	//建築可能なタイルか確認
	//現在選択されているタイルの種類を取得
	const int currentTileType = tile.getTileTypes()[m_selectedTileIndex.col][m_selectedTileIndex.row];

	// 草原タイル（ID=2）でのみ建築可能と仮定
	if (currentTileType != 2 && currentTileType != 10)
	{
		//Print << U"このタイルには建築できません。";
		return;
	}

	//建築に必要な資源をチェック、消費
	if (!checkAndConsumeResources(buildingType))
	{
		return; //資源が足りなければ処理を中断
	}

	//建築タスクを作成
	BuildJob newJob;
	newJob.index = m_selectedTileIndex;
	newJob.tileType = buildingType;		//どの建物を建てるかのIDをセット
	newJob.requiredTime = 5.0;			//建築に必要な時間（5秒）
	m_activeBuildJobs.push_back(newJob);

	//Print << U"建築予約: ({}, {}) - 5秒後"_fmt(m_selectedTileIndex.row, m_selectedTileIndex.col);
}

void Game::startResourceGathering(int tileType)
{
	//現在選択されているタイルの種類を取得
	const int currentTileType = tile.getTileTypes()[m_selectedTileIndex.col][m_selectedTileIndex.row];

	//UIが提供したタイルタイプが実際に選択されているタイルタイプと一致するか確認
	if (tileType != currentTileType)
	{
		return; //不一致の場合は何もしない
	}

	const auto& resources = Resource::getResources(tileType);

	if (!resources.empty())
	{
		ResourceJob newJob;
		newJob.resources = resources;
		newJob.requiredTime = 5.0;				//採取にかかる時間5秒
		newJob.elapsedTime = 0.0;				//時間経過を0に初期化
		newJob.index = m_selectedTileIndex;		//ゲージ描画のため、選択中のタイルインデックスを保存
		m_activeJobs.push_back(newJob);
		//Print << U"資源獲得を開始しました...";
	}
	else
	{
		//Print << U"このタイルからは資源を得られません";
	}
}

void Game::debugStartResourceGathering(int tileType)
{
	//現在選択されているタイルの種類を取得
	const int currentTileType = tile.getTileTypes()[m_selectedTileIndex.col][m_selectedTileIndex.row];

	//UIが提供したタイルタイプが、実際に選択されているタイルタイプと一致するか確認
	if (tileType != currentTileType)
	{
		return; //不一致の場合は何もしない
	}

	const auto& resources = Resource::getResources(tileType);

	if (!resources.empty())
	{
		//即時獲得処理
		for (const auto& res : resources)
		{
			m_playerResources[res.type] += res.amount;
		}
		//Print << U"資源の即時獲得が完了しました！";
	}
}

bool Game::checkAndConsumeResources(int buildingType)
{
	//建築コストを取得
	const auto& costs = s_buildCosts.at(buildingType);

	//資源が足りているか確認
	for (const auto& cost : costs)
	{
		if (m_playerResources[cost.type] < cost.amount)
		{
			//Print << U"資源「{}」が足りません。"_fmt(ToString(cost.type));
			return false; //資源が不足
		}
	}

	//資源を消費
	for (const auto& cost : costs)
	{
		m_playerResources[cost.type] -= cost.amount;
	}

	return true; //資源を消費できた
}

void Game::startProcessing(int facilityType)
{
	//入力と出力の資源を定義する構造体
	struct Conversion
	{
		ResourceType inputType;
		int inputAmount;
		ResourceType outputType;
		int outputAmount;
	};

	//処理IDに基づいて変換ルールを決定
	Conversion conversion;
	bool isValidConversion = true;

	switch (facilityType)
	{
	case 8:		//精錬所:鉱石→インゴット
		conversion = { ResourceType::Ore, 1, ResourceType::Ingot, 1 };
		break;

	case 1201:	//加工場:原木→木材
		conversion = { ResourceType::Wood, 1, ResourceType::Timber, 1 };
		break;

	case 1202:	//加工場:石材→レンガ
		conversion = { ResourceType::Stone, 1, ResourceType::Breck, 1 };
		break;

	case 1203:	//加工場:羊毛→布
		conversion = { ResourceType::Wool, 1, ResourceType::Cloth, 1 };
		break;

	default:
		isValidConversion = false;
		return;
	}

	if (!isValidConversion) return;

	//資源が足りているかチェック
	if (m_playerResources[conversion.inputType] < conversion.inputAmount)
	{
		// Print << U"資源「{}」が足りません。"_fmt(ToString(conversion.inputType)); //デバッグ用
		return; //資源不足の場合はここで終了
	}

	//資源を消費
	m_playerResources[conversion.inputType] -= conversion.inputAmount;

	//資源を獲得
	m_playerResources[conversion.outputType] += conversion.outputAmount;

	// Print << U"加工完了: {} -> {}"_fmt(ToString(conversion.inputType), ToString(conversion.outputType)); //デバッグ用
}
