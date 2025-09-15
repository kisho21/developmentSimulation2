#include "InfoUi.hpp"

InfoUi::InfoUi()
	:m_topUi{ U"image/ui/2d/ui-top.png" }
{

}

void InfoUi::setResources(const std::map<ResourceType, int>& resources)
{
	m_playerResources = &resources;
}

void InfoUi::Draw() const
{
	int win_x = 1280;
	int win_y = 720;

	m_topUi.draw(Vec2( win_x / 2 - 500, 0 ));

	// 資源の所持数をUIパネル内に表示
	if (m_playerResources)
	{
		int i = 0;
		for (const auto& pair : *m_playerResources)
		{
			m_font(U"{} : {}"_fmt(ToString(pair.first), pair.second)).draw(Vec2(win_x / 2 - 490, 10 + (i * 25)));
			i++;
		}
	}
}
