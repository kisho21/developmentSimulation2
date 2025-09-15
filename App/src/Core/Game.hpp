#pragma once
#include <Siv3D.hpp>
#include "Config.hpp"
#include "Fader.hpp"
#include "SceneTitle.hpp"
#include "../Player/CameraController.hpp"
#include "../World/Tile.hpp"
#include "../World/BuildJob.hpp"
#include "../Ui/InfoUi.hpp"
#include "../Ui/ArchitectUi.hpp"
#include "../Resource/Resource.hpp"
#include "../Resource/ResourceJob.hpp"


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
	SceneState m_currentScene = SceneState::Game;
	ManagerState m_managerState = ManagerState::FadeIn;

	MSRenderTexture m_renderTexture;
	DebugCamera3D m_cam;
	CameraController m_cameraController;

	PixelShader m_ps;
	Texture m_tex;

	//選択中のタイルの座標
	GridIndex m_selectedTileIndex;
	//建築待ちのタイルの座標
	Optional<GridIndex> m_tileToBuild;

	//進行中の資源獲得タスクのリスト
	std::vector<ResourceJob> m_activeJobs;
	//プレイヤーの資源所持量を管理する
	std::map<ResourceType, int> m_playerResources;
	//進行中の建築タスクのリスト
	std::vector<BuildJob> m_activeBuildJobs;

	void initLighting() const;
	//void updateCamera();
	void drawSelection() const;
	void startBuilding(int buildingType);

	Tile tile;
	InfoUi infoUi;
	ArchitectUi architectUi;


	//
	s3d::Font font;
};
