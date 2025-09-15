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

	//ウィンドウ右下の端に横320、縦240のUI
	m_botUi.draw(Vec2(win_x - 320, win_y - 240));

	// タイルの種類に応じてボタンを表示
	switch (m_currentTileType)
	{
	case 0: // 森
		m_font(U"伐採所を建てる").drawAt(Scene::Center().movedBy(0, -50));
		if (SimpleGUI::Button(U"建設", Scene::Center().movedBy(0, 0)))
		{
			// 伐採所建築ロジック
		}
		break;
	case 1: // 岩山
		m_font(U"鉱山を建てる").drawAt(Scene::Center().movedBy(0, -50));
		if (SimpleGUI::Button(U"建設", Scene::Center().movedBy(0, 0)))
		{
			// 鉱山建築ロジック
		}
		break;
	case 2: // 草原
		m_font(U"家を建てる").drawAt(Vec2(win_x - 160, win_y - 200), Palette::Black);
		if (SimpleGUI::Button(U"建設", Vec2(win_x - 200, win_y - 100)))
		{
			if (m_buildHandler)
			{
				// 家のタイルタイプIDを渡す
				m_buildHandler(10); // 例: 家のIDを10とする
			}
		}

		// 農場を建てるボタンを追加
		m_font(U"農場を建てる").drawAt(Vec2(win_x - 160, win_y - 170), Palette::Black);
		if (SimpleGUI::Button(U"建設", Vec2(win_x - 200, win_y - 70)))
		{
			if (m_buildHandler)
			{
				// 農場のタイルタイプIDを渡す
				m_buildHandler(6); // 例: 農場のIDを6とする
			}
		}

		// 牧場を建てるボタンを追加
		m_font(U"牧場を建てる").drawAt(Vec2(win_x - 160, win_y - 140), Palette::Black);
		if (SimpleGUI::Button(U"建設", Vec2(win_x - 200, win_y - 40)))
		{
			if (m_buildHandler)
			{
				// 牧場のタイルタイプIDを渡す
				m_buildHandler(5); // 例: 牧場のIDを5とする
			}
		}
		break;
	}
}
