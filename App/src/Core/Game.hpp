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
#include "../Resource/Build.hpp"


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
	//建築に必要な資源があるか確認、消費する関数
	bool checkAndConsumeResources(int buildingType);

	void initLighting() const;
	//void updateCamera();
	void drawSelection() const;
	void startBuilding(int buildingType);
	void startResourceGathering(int tileType);

	Tile tile;
	InfoUi infoUi;
	ArchitectUi architectUi;


	//
	s3d::Font font;
};

// 建物ごとの建築コストを定義する
const std::map<int, std::vector<BuildCost>> s_buildCosts =
{
	//家を建てるコスト:木10個
	{ 10, { { ResourceType::Wood, 10 } } },
	//農場を建てるコスト:木5個、石3個
	{ 6, { { ResourceType::Wood, 2 }, { ResourceType::Stone, 1 } } },
	//牧場を建てるコスト:木8個
	{ 5, { { ResourceType::Wood, 3 } } },
	//鉱山を建てるコスト:石8個
	{ 4, { { ResourceType::Stone, 5 } } },
	//精錬所を建てるコスト:石15個、石レンガ5個
	{ 8, { { ResourceType::Stone, 8 }, { ResourceType::Wood, 2 } } },
	//加工場を建てるコスト:木20個、石10個
	{ 12, { { ResourceType::Wood, 5 } } },
	//交易所を建てるコスト:木材10個、石レンガ10個、布10個
	{ 7, { { ResourceType::Wood, 5 }, { ResourceType::Stone, 5 } } }
};
