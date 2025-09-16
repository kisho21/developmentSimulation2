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
	case 0: //森
		m_font(U"資源を得る").drawAt(Vec2(win_x - 160, win_y - 180), Palette::Black);
		if (SimpleGUI::Button(U"木を獲得", Vec2(win_x - 220, win_y - 120)))
		{
			if (m_resourceHandler)
			{
				m_resourceHandler(m_currentTileType);
			}
		}
		break;
	case 1: //岩山
		m_font(U"資源を得る").drawAt(Vec2(win_x - 160, win_y - 180), Palette::Black);
		if (SimpleGUI::Button(U"石を獲得", Vec2(win_x - 220, win_y - 120)))
		{
			if (m_resourceHandler)
			{
				m_resourceHandler(m_currentTileType);
			}
		}
		break;
	case 2: //草原
		m_font(U"建築する").drawAt(Vec2(win_x - 160, win_y - 200), Palette::Black);
		//家を建てるボタンを追加
		if (SimpleGUI::Button(U"住居", Vec2(win_x - 300, win_y - 160)))
		{
			if (m_buildHandler)
			{
				//家のタイルタイプIDを渡す
				m_buildHandler(10);
			}
		}

		//農場を建てるボタンを追加
		if (SimpleGUI::Button(U"農場", Vec2(win_x - 300, win_y - 110)))
		{
			if (m_buildHandler)
			{
				//農場のタイルタイプIDを渡す
				m_buildHandler(6);
			}
		}

		//牧場を建てるボタンを追加
		if (SimpleGUI::Button(U"牧場", Vec2(win_x - 300, win_y - 60)))
		{
			if (m_buildHandler)
			{
				//牧場のタイルタイプIDを渡す
				m_buildHandler(5);
			}
		}

		//鉱山を建てるボタンを追加
		if (SimpleGUI::Button(U"鉱山", Vec2(win_x - 210, win_y - 160)))
		{
			if (m_buildHandler)
			{
				m_buildHandler(4);
			}
		}

		//精錬所を建てるボタンを追加
		if (SimpleGUI::Button(U"精錬所", Vec2(win_x - 210, win_y - 110)))
		{
			if (m_buildHandler)
			{
				m_buildHandler(8);
			}
		}

		//加工場を建てるボタンを追加
		if (SimpleGUI::Button(U"加工場", Vec2(win_x - 210, win_y - 60)))
		{
			if (m_buildHandler)
			{
				m_buildHandler(12);
			}
		}

		//交易所を建てるボタンを追加
		if (SimpleGUI::Button(U"交易所", Vec2(win_x - 120, win_y - 160)))
		{
			if (m_buildHandler)
			{
				m_buildHandler(7);
			}
		}
		break;
	case 3:	//湖
		break;
	case 4:	//鉱山
		m_font(U"資源を得る").drawAt(Vec2(win_x - 160, win_y - 180), Palette::Black);
		if (SimpleGUI::Button(U"鉱石を獲得", Vec2(win_x - 220, win_y - 120)))
		{
			if (m_resourceHandler)
			{
				m_resourceHandler(m_currentTileType);
			}
		}
		break;
	case 5:	//牧場
		m_font(U"資源を得る").drawAt(Vec2(win_x - 160, win_y - 180), Palette::Black);
		if (SimpleGUI::Button(U"羊毛を獲得", Vec2(win_x - 220, win_y - 120)))
		{
			if (m_resourceHandler)
			{
				m_resourceHandler(m_currentTileType);
			}
		}
		break;
	case 6:	//農場
		m_font(U"資源を得る").drawAt(Vec2(win_x - 160, win_y - 180), Palette::Black);
		if (SimpleGUI::Button(U"食料を獲得", Vec2(win_x - 220, win_y - 120)))
		{
			if (m_resourceHandler)
			{
				m_resourceHandler(m_currentTileType);
			}
		}
		break;
	case 7:	//交易所
		break;
	case 8:	//精錬所
		m_font(U"資源を得る").drawAt(Vec2(win_x - 160, win_y - 180), Palette::Black);
		if (SimpleGUI::Button(U"インゴットを獲得", Vec2(win_x - 220, win_y - 120)))
		{
			if (m_resourceHandler)
			{
				m_resourceHandler(m_currentTileType);
			}
		}
		break;
	case 9:	//橋
		break;
	case 10:	//家1
		m_font(U"アップグレード").drawAt(Vec2(win_x - 160, win_y - 200), Palette::Black);
		//家を建てるボタンを追加
		if (SimpleGUI::Button(U"住居", Vec2(win_x - 300, win_y - 160)))
		{
			if (m_buildHandler)
			{
				//家のタイルタイプIDを渡す
				m_buildHandler(11);
			}
		}
		break;
	case 11:	//家2
		break;
	case 12:	//加工場
		break;
	}
}
