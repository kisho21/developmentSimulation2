#include "Game.hpp"

Game::Game()
	: m_renderTexture{ Scene::Size(),TextureFormat::R8G8B8A8_Unorm_SRGB,HasDepth::Yes }
	, m_cam{ m_renderTexture.size(), Config::CamFOV, Config::CamInitialPosition }
	, m_cameraController{ m_cam }
	, m_ps{ HLSL{ U"example/shader/hlsl/forward_triplanar.hlsl",U"PS"} }
	, m_tex{ U"example/texture/uv.png" }
	, m_selectedTileIndex{ 14,14 }
	, font{ 20 }
{
	if (!m_ps) throw Error{ U"Failed to load PixelShader" };		//パスが間違っているとき任意でエラーを出すようにできる
	initLighting();
	m_title.Init();
	m_fader.startFadeIn();		//フェードイン処理開始

	//updateCamera();
}

void Game::initLighting() const
{
	Graphics3D::SetGlobalAmbientColor(ColorF(0.1));
	Graphics3D::SetSunColor(ColorF(1.0));							//平行光
	Graphics3D::SetSunDirection(Vec3(0.3, 1, 0.2).normalized());	//normalized()→スクリーン座標を標準化するため
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

void Game::drawSelection() const
{
	const double x_gap = (m_selectedTileIndex.col % 2 == 1) ? 0.5 : 0;
	const Vec3 highlightPos = Vec3{ m_selectedTileIndex.row + x_gap, 0, 0.866 * m_selectedTileIndex.col };

	// 選択中のタイルに黄色の枠を描画
	Box{ highlightPos, 1.0, 0.5, 1.0 }.drawFrame(Palette::Yellow);
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

			m_cameraController.Update(Scene::DeltaTime());
			Graphics3D::SetCameraTransform(m_cam);

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
			}

			//選択されたタイルの種類に応じてUIを表示
			const int tileType = tileTypes[m_selectedTileIndex.col][m_selectedTileIndex.row];
			architectUi.show(tileType);
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
	Print << U"Selected Tile: ({}, {})"_fmt(m_selectedTileIndex.row, m_selectedTileIndex.col);

	return true;
}

void Game::Draw() const
{
	if (m_currentScene == SceneState::Title)
	{
		m_title.Draw();
	}
	else if (m_currentScene == SceneState::Game)
	{
		const ColorF bg{ 0.2, 0.5, 0.8 };
		const ScopedRenderTarget3D target{ m_renderTexture.clear(bg) };
		Graphics3D::SetPSTexture(0, m_tex);
		tile.Draw();
		drawSelection(); // 選択中のタイルをハイライト表示

		Graphics3D::Flush();
		m_renderTexture.resolve();
		Shader::LinearToScreen(m_renderTexture);

		infoUi.Draw();
		architectUi.Draw();
	}
	
	// === デバッグ表示 ===
	// 現在のシーン状態を画面左上に表示する
	if (m_currentScene == SceneState::Title)
	{
		font(U"SceneState: Title").draw(10, 10);
	}
	else
	{
		font(U"SceneState: Game").draw(10, 10);
	}
	// 現在のシーンマネージャーを画面左上に表示する
	if (m_managerState == ManagerState::FadeIn)
	{
		font(U"ManagerState: FadeIn").draw(10, 30);
	}
	else if(m_managerState == ManagerState::Standby)
	{
		font(U"SceneState: Standby").draw(10, 30);
	}
	else if (m_managerState == ManagerState::FadeOut)
	{
		font(U"SceneState: FadeOut").draw(10, 30);
	}
	else if (m_managerState == ManagerState::ChangeScene)
	{
		font(U"SceneState: ChangeScene").draw(10, 30);
	}

	m_fader.Draw();
}
