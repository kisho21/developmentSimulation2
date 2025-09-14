#include "Game.hpp"
#include "../Util/RayCaster.hpp"

Game::Game()
	: m_renderTexture{ Scene::Size(),TextureFormat::R8G8B8A8_Unorm_SRGB,HasDepth::Yes }
	, m_cam{ m_renderTexture.size(), Config::CamFOV, Config::CamInitialPosition }
	, m_cameraController{ m_cam }
	, m_ps{ HLSL{ U"example/shader/hlsl/forward_triplanar.hlsl",U"PS"} }
	, m_tex{ U"example/texture/uv.png" }
{
	if (!m_ps) throw Error{ U"Failed to load PixelShader" };		//パスが間違っているとき任意でエラーを出すようにできる
	initLighting();
}

void Game::initLighting() const
{
	Graphics3D::SetGlobalAmbientColor(ColorF(0.1));
	Graphics3D::SetSunColor(ColorF(1.0));							//平行光
	Graphics3D::SetSunDirection(Vec3(0.3, 1, 0.2).normalized());	//normalized()→スクリーン座標を標準化するため
}

bool Game::Update()
{
	m_cameraController.Update(Scene::DeltaTime());
	Graphics3D::SetCameraTransform(m_cam);

	if (s3d::MouseL.down())
	{
		//RayCaster::CreateRay() を使用せず、直接Rayを生成
		const s3d::Ray ray = m_cam.screenToRay(s3d::Cursor::PosF());

		const s3d::Plane groundPlane{ 0.0f, 1.0f, 0.0f, 0.0f };

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
	const ColorF bg{ 0.2, 0.5, 0.8 };

	//3D描画処理
	{
		const ScopedRenderTarget3D target{ m_renderTexture.clear(bg) };
		Graphics3D::SetPSTexture(0, m_tex);

		tile.Draw();
	}
	
	//2D転送
	{
		Graphics3D::Flush();						//スクリーンに映すまでの流れ、定型文
		m_renderTexture.resolve();					//スクリーンに映すまでの流れ、定型文
		Shader::LinearToScreen(m_renderTexture);	//スクリーンフリップ
	}

	//2D描画処理
	{
		infoUi.Draw();
		//architectUi.Draw();
	}
}
