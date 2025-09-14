#include "Game.hpp"
#include "../Util/RayCaster.hpp"

Game::Game()
	: m_renderTexture{ Scene::Size(),TextureFormat::R8G8B8A8_Unorm_SRGB,HasDepth::Yes }
	, m_cam{ m_renderTexture.size(), Config::CamFOV, Config::CamInitialPosition }
	, m_cameraController{ m_cam }
	, m_ps{ HLSL{ U"example/shader/hlsl/forward_triplanar.hlsl",U"PS"} }
	, m_tex{ U"example/texture/uv.png" }
	//
	, font{ 20 }
{
	if (!m_ps) throw Error{ U"Failed to load PixelShader" };		//パスが間違っているとき任意でエラーを出すようにできる
	initLighting();
	m_title.Init();
	m_fader.startFadeIn();		//フェードイン処理開始
}

void Game::initLighting() const
{
	Graphics3D::SetGlobalAmbientColor(ColorF(0.1));
	Graphics3D::SetSunColor(ColorF(1.0));							//平行光
	Graphics3D::SetSunDirection(Vec3(0.3, 1, 0.2).normalized());	//normalized()→スクリーン座標を標準化するため
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
			/*if (s3d::Keyboard::Escape.down())
			{
				m_managerState = ManagerState::FadeOut;
				m_fader.startFadeOut();
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

	

	if (MouseL.down())
	{
		//RayCaster::CreateRay() を使用せず、直接Rayを生成
		const Ray ray = m_cam.screenToRay(s3d::Cursor::PosF());

		const Plane groundPlane{ 0.0f, 1.0f, 0.0f, 0.0f };

		//IntersectsPlane() に直接 ray と plane を渡す
		if (const auto hitPos = RayCaster::IntersectsPlane(ray, groundPlane))
		{
			//3D座標からグリッド座標に変換
			if (const auto selectedGrid = tile.getGridPosFromWorldPos(hitPos.value()))
			{
				//タイルがクリックされた
				const int selectedRow = selectedGrid->row;
				const int selectedCol = selectedGrid->col;

				ClearPrint();
				Print << U"Hit Position: " << hitPos.value();
			}
		}
	}


	////マウス左ボタンが押された瞬間を検出
	//if (s3d::MouseL.down())
	//{
	//	// 1. カメラオブジェクトを明示的にキャスト
	//	// 2. カーソル位置を s3d::::Cursor::PosF() で明示
	//	const s3d::Ray ray = RayCaster::CreateRay(static_cast<const s3d::BasicCamera3D&>(m_cam), s3d::Cursor::PosF());

	//	const s3d::Plane groundPlane{ 0.0f, 1.0f, 0.0f, 0.0f };

	//	if (const auto hitPos = RayCaster::IntersectsPlane(ray, groundPlane))
	//	{
	//		//3D座標からグリッド座標に変換
	//		if (const auto selectedGrid = tile.getGridPosFromWorldPos(hitPos.value()))
	//		{
	//			//タイルがクリックされた
	//			const int selectedRow = selectedGrid->row;
	//			const int selectedCol = selectedGrid->col;

	//			ClearPrint();
	//			Print << U"Hit Position: " << hitPos.value();
	//		}
	//	}
	//}

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

		Graphics3D::Flush();
		m_renderTexture.resolve();
		Shader::LinearToScreen(m_renderTexture);

		infoUi.Draw();
	}


	//const ColorF bg{ 0.2, 0.5, 0.8 };

	//// 現在のシーンを描画
	//if (m_currentScene == SceneState::Title)
	//{
	//	m_title.Draw();
	//}
	//else if (m_currentScene == SceneState::Game)
	//{
	//	//3D描画処理
	//	{
	//		const ScopedRenderTarget3D target{ m_renderTexture.clear(bg) };
	//		Graphics3D::SetPSTexture(0, m_tex);
	//		 
	//		tile.Draw();
	//	}

	//	//2D転送
	//	{
	//		Graphics3D::Flush();						//スクリーンに映すまでの流れ、定型文
	//		m_renderTexture.resolve();					//スクリーンに映すまでの流れ、定型文
	//		Shader::LinearToScreen(m_renderTexture);	//スクリーンフリップ
	//	}

	//	//2D描画処理
	//	{
	//		infoUi.Draw();
	//		//architectUi.Draw(); 
	//	}
	//}

	
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
