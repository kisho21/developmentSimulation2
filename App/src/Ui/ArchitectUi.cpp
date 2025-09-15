#include "ArchitectUi.hpp"

ArchitectUi::ArchitectUi()
	: m_botUi{ U"image/ui/2d/ui-bottom.png" }
	, m_font{ 20 }
{

}

void ArchitectUi::show(int tileType)
{
	m_isVisible = true;
	m_currentTileType = tileType;
}

void ArchitectUi::hide()
{
	m_isVisible = false;
}

void ArchitectUi::Draw() const
{
	if (!m_isVisible) return;

	// UIパネルの描画
	int win_x = 1280;
	int win_y = 720;

	m_botUi.draw(Vec2(win_x - 320, win_y - 240));

	// タイルの種類に応じてボタンを表示
	switch (m_currentTileType)
	{
	case 0: // 草原
		m_font(U"家を建てる").drawAt(Scene::Center().movedBy(0, -50));
		if (SimpleGUI::Button(U"建設", Scene::Center().movedBy(0, 0)))
		{
			// 建築ロジックをここに書く
			// 例: Game::BuildHouse();
		}
		break;
	case 1: // 森
		m_font(U"伐採所を建てる").drawAt(Scene::Center().movedBy(0, -50));
		if (SimpleGUI::Button(U"建設", Scene::Center().movedBy(0, 0)))
		{
			// 伐採所建築ロジック
		}
		break;
	case 2: // 岩山
		m_font(U"鉱山を建てる").drawAt(Scene::Center().movedBy(0, -50));
		if (SimpleGUI::Button(U"建設", Scene::Center().movedBy(0, 0)))
		{
			// 鉱山建築ロジック
		}
		break;
	}
}
