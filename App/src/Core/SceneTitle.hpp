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


	//
	bool m_isKeyInputDetected = false;
};
