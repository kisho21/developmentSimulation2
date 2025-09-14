#pragma once
#include <Siv3D.hpp>
#include "Config.hpp"
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
	MSRenderTexture m_renderTexture;
	DebugCamera3D m_cam;
	CameraController m_cameraController;

	PixelShader m_ps;
	Texture m_tex;

	void initLighting() const;

	InfoUi infoUi;
	Tile tile;
	//ArchitectUi architectUi;
};
