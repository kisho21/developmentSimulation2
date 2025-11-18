#pragma once
#include <Siv3D.hpp>

class SceneTitle
{
public:
	SceneTitle();
	void Init();
	void Update();
	void Draw() const;

	bool isRequestToChangeScene() const { return m_requestChange; }

private:
	bool m_requestChange = false;

	s3d::Font m_titleFont;
	s3d::Font m_messageFont;

	MSRenderTexture m_renderTexture;
	Texture m_tex;
	DebugCamera3D m_camera;

	Model m_house1Model;		//民家レベル1
	double m_rotationAngle = 0.0;

	Audio m_bgm;

	//
	bool m_isKeyInputDetected = false;
};
