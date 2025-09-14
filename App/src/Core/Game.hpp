#pragma once
#include <Siv3D.hpp>
#include "Config.hpp"
#include "Fader.hpp"
#include "SceneTitle.hpp"
#include "../Player/CameraController.h"
#include "../World/Tile.hpp"
#include "../Ui/InfoUi.hpp"
#include "../Ui/ArchitectUi.hpp"

class Tile;
class InfoUi;
class ArchitectUi;

class Game
{
public:
	Game();
	bool Update();
	void Draw() const;

private:
	//シーン切り替え関連
	Fader m_fader;
	SceneTitle m_title;
	SceneState m_currentScene = SceneState::Title;
	ManagerState m_managerState = ManagerState::FadeIn;

	MSRenderTexture m_renderTexture;
	DebugCamera3D m_cam;
	CameraController m_cameraController;

	PixelShader m_ps;
	Texture m_tex;

	void initLighting() const;

	Tile tile;
	InfoUi infoUi;
	//ArchitectUi architectUi;


	//
	s3d::Font font;
};
