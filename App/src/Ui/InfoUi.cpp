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
}
