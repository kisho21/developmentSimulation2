#include "InfoUi.hpp"
#include "../Resource/Money.hpp"

InfoUi::InfoUi()
	: m_topUi{ U"image/ui/2d/ui-top.png" }
	, m_font{ 20 }
{
}

void InfoUi::setResources(const std::map<ResourceType, int>& resources)
{
	m_resources = resources;
}

void InfoUi::setDrawInfo(const GridIndex& index, const Tile& tile)
{
	m_selectedTileIndex = index;
	m_pTile = &tile;	//参照をポインタとして保持
}

void InfoUi::Draw() const
{
	int win_x = 1280;
	int win_y = 720;

	//画面左上に資源の所持数を表示
	const Vec2 basePos{ 0, 10 };
	double yOffset = 0;

	for (const auto& resourceType : allResources)
	{
		//資源の所持数を取得、m_resourcesに存在しない場合は0をデフォルト値として表示
		const int amount = m_resources.contains(resourceType) ? m_resources.at(resourceType) : 0;

		//資源名と数量を描画
		m_font(U"{} : {}"_fmt(ToString(resourceType), amount)).draw(basePos.x, basePos.y + yOffset);
		yOffset += 25;		//次の資源の表示位置を下にずらす
	}

	//画面右上に資金の所持数を表示
	const Vec2 moneyBasePos{ win_x / 2 + 300, 10 };
	const int currentMoney = Money::getAmount();

	m_font(U"所持金: {} G"_fmt(currentMoney)).draw(moneyBasePos.x, moneyBasePos.y);

	//画面左下にタイル説明表示
	if (m_pTile)
	{
		//m_pTileからgetTileTypes()を呼び出す
		const auto& tileTypes = m_pTile->getTileTypes();

		if (m_selectedTileIndex.col < tileTypes.size() && m_selectedTileIndex.row < tileTypes[0].size())
		{
			const int tileType = tileTypes[m_selectedTileIndex.col][m_selectedTileIndex.row];
			const s3d::Array<s3d::String> explanation = TileExplanation::getExplanation(tileType);

			const Vec2 expBasePos{ 20, win_y - 80 };	//描画位置
			double yOffset = 0;

			for (const auto& line : explanation)
			{
				m_font(line).draw(expBasePos.x, expBasePos.y + yOffset);
				yOffset += 25;	//2、3行目を下にずらす
			}
		}
	}
}
