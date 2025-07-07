#pragma once
#include <Siv3D.hpp>
#include "Config.hpp"
#include "../Player/CameraController.h"
#include "../World/Tile.hpp"

class Tile;

class Game
{
public:
	Game();
	bool Update();
	void Draw() const;

private:
	MSRenderTexture m_renderTexture;
	DebugCamera3D m_cam;

	PixelShader m_ps;
	Texture m_tex;

	void initLighting() const;

	Tile tile;
};
