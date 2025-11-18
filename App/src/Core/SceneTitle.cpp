#include "SceneTitle.hpp"

SceneTitle::SceneTitle()
	: m_titleFont{ 72 }
	, m_messageFont{ 20 }
	, m_renderTexture{ Scene::Size(),TextureFormat::R8G8B8A8_Unorm_SRGB,HasDepth::Yes }
	, m_tex{ U"example/texture/uv.png" }
	, m_camera{ m_renderTexture.size(), 30_deg, Vec3{ 0, 1, -3 },Vec3{ 0, -0.5, 0 } }
	, m_house1Model{ U"image/model/building-house.obj" }
	, m_bgm{ Audio::Stream, U"music/bgm/bgm.mp3", Loop::Yes }
{
	Model::RegisterDiffuseTextures(m_house1Model, TextureDesc::MippedSRGB);
}

void SceneTitle::Init()
{
	m_requestChange = false;
	m_isKeyInputDetected = false;
}

void SceneTitle::Update()
{
	m_camera.update(2.0);
	Graphics3D::SetCameraTransform(m_camera);

	m_bgm.play();

	m_rotationAngle += 15_deg * s3d::Scene::DeltaTime();

	//キー入力でシーン切り替え
	if (KeySpace.down())
	{
		m_bgm.stop();
		m_requestChange = true;
		m_isKeyInputDetected = true;
	}
}

void SceneTitle::Draw() const
{
	const ColorF bg{ 0.1, 0.4, 1.0 };
	const ScopedRenderTarget3D target{ m_renderTexture.clear(bg) };
	Graphics3D::SetPSTexture(0, m_tex);

	const Mat4x4 rotationMatrix = Mat4x4::RotateY(m_rotationAngle);
	m_house1Model.draw(rotationMatrix.translated(Vec3(0, -1, 0)));
	//m_house1Model.draw(Vec3(0, -1, 0));

	Graphics3D::Flush();
	m_renderTexture.resolve();
	Shader::LinearToScreen(m_renderTexture);

	m_titleFont(U"Develop Nature").drawAt(s3d::Scene::Center().movedBy(0, -200));
	m_messageFont(U"スペースキーでゲームへ").drawAt(s3d::Scene::Center().movedBy(0, 330));


	// デバッグ表示
	/*if (m_requestChange)
	{
		m_messageFont(U"スペースキーが押されました！").draw(50, 50);
	}*/
}
