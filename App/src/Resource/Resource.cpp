#include "Resource.hpp"

// m_tileResourcesの定義と初期化
const std::map<int, std::vector<TileResource>> Resource::m_tileResources =
{
	{ 0, { { ResourceType::Wood, 1 } } },		// 森:木
	{ 1, { { ResourceType::Stone, 1 } } },		// 岩:石
	{ 2, { } },                                 // 草原:資源なし
	{ 3, { } },                                 // 湖:資源なし
	{ 4, { { ResourceType::Ore, 1 } } },		// 鉱山:鉱石
	{ 5, { { ResourceType::Wool, 1 } } },		// 牧場:羊毛
	{ 6, { { ResourceType::Food, 1 } } },		// 農場:食料
	{ 7, { { ResourceType::Timber, 1 }, { ResourceType::Breck, 1 }, { ResourceType::Cloth, 1 } } },      // 加工場:木材、石レンガ、布
	{ 8, { { ResourceType::Ingot, 1 } } },		// 精錬所:インゴット
};

//タイルタイプに応じた資源情報を返す
const std::vector<TileResource>& Resource::getResources(int tileType)
{
	//タイルタイプが存在しない場合は空のリストを返す
	static const std::vector<TileResource> emptyList;
	if (m_tileResources.count(tileType))
	{
		return m_tileResources.at(tileType);
	}
	return emptyList;
}
