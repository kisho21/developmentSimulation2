#include "InfoUi.hpp"

InfoUi::InfoUi()
	:m_topUi{ U"image/ui/2d/ui-top.png" }
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

	//m_topUi.draw(Vec2( win_x / 2 - 500, 0 ));

	//画面左上に資源の所持数を表示
	const Vec2 basePos{ win_x / 2 - 490, 10 };
	double yOffset = 0;

	for (const auto& pair : m_resources)
	{
		const auto& resourceType = pair.first;
		const int amount = pair.second;

		//資源名と数量を描画
		m_font(U"{} : {}"_fmt(ToString(resourceType), amount)).draw(basePos.x, basePos.y + yOffset);
		yOffset += 25; //次の資源の表示位置を下にずらす
	}
}
