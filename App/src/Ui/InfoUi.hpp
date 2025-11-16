#pragma once
#include <Siv3D.hpp>
#include "../Resource/Resource.hpp"
#include "../Resource/Money.hpp"
#include "TileExplanation.hpp"
#include "../World/Tile.hpp"

class Tile;

//画面に常時表示するUI
//人口、金など
class InfoUi
{
public:
	InfoUi();
	void Draw() const;

	//資源情報を設定する関数
	void setResources(const std::map<ResourceType, int>& resources);

	void setDrawInfo(const GridIndex& index, const Tile& tile);

private:
	Texture m_topUi;
	Font m_font;

	//プレイヤーの資源所持数を直接保持
	std::map<ResourceType, int> m_resources;

	const s3d::Array<ResourceType> allResources =
	{
		ResourceType::Wood,
		ResourceType::Stone,
		ResourceType::Ore,
		ResourceType::Wool,
		ResourceType::Food,
		ResourceType::Timber,
		ResourceType::Breck,
		ResourceType::Ingot,
		ResourceType::Cloth
	};

	//選択中のタイルを保持
	GridIndex m_selectedTileIndex = { 0, 0 };
	const Tile* m_pTile = nullptr;
};
