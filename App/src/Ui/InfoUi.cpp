#include "InfoUi.hpp"

InfoUi::InfoUi()
	:m_topUi{ U"image/ui/2d/ui-top.png" }
{

}

void InfoUi::Draw() const
{
	int win_x = 1280;
	int win_y = 720;

	m_topUi.draw(Vec2( win_x / 2 - 500, 0 ));
}
