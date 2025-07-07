#include "Game.hpp"

Game::Game()
	: m_renderTexture{ Scene::Size(),TextureFormat::R8G8B8A8_Unorm_SRGB,HasDepth::Yes }
	, m_cam{ m_renderTexture.size(), Config::CamFOV, Config::CamInitialPosition }
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
	m_cam.update(2.0);
	Graphics3D::SetCameraTransform(m_cam);

	return true;
}

void Game::Draw() const
{
	const ColorF bg{ 0.2, 0.5, 0.8 };

	//3D描画処理
	{
		const ScopedRenderTarget3D target{ m_renderTexture.clear(bg) };
		//const ScopedCustomShader3D shader{ m_ps };
		Graphics3D::SetPSTexture(0, m_tex);

		
		tile.Draw();	//←連続してアセットを読み込んでいる、ここから
	}
	
	//2D転送
	{
		Graphics3D::Flush();						//スクリーンに映すまでの流れ、定型文
		m_renderTexture.resolve();					//スクリーンに映すまでの流れ、定型文
		Shader::LinearToScreen(m_renderTexture);	//スクリーンフリップ
	}
}
