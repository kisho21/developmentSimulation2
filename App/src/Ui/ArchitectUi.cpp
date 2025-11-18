#include "ArchitectUi.hpp"

ArchitectUi::ArchitectUi()
	: m_botUi{ U"image/ui/2d/ui-bottom.png" }
	, m_font{ 20 }
	, m_buttonSe{ U"music/se/button.mp3" }
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

void ArchitectUi::setProcessHandler(ProcessHandler handler)
{
	m_processHandler = handler;
}

void ArchitectUi::Draw()
{
	if (!m_isVisible) return;

	//UIの描画
	int win_x = 1270;
	int win_y = 715;

	//ウィンドウ右下の端に横320、縦240のUI
	m_botUi.draw(Vec2(win_x - 320, win_y - 240));

	//タイルの種類に応じてボタンを表示
	if (!m_showConfirm)
	{
		switch (m_currentTileType)
		{
		case 0: //森
			m_font(U"資源を得る").drawAt(Vec2(win_x - 160, win_y - 180), Palette::Black);
			if (SimpleGUI::Button(U"木を獲得", Vec2(win_x - 220, win_y - 120)))
			{
				m_buttonSe.stop();
				m_buttonSe.play();

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
				m_buttonSe.stop();
				m_buttonSe.play();

				if (m_resourceHandler)
				{
					m_resourceHandler(m_currentTileType);
				}
			}
			break;
		case 2: //草原
		{
			m_font(U"建築する").drawAt(Vec2(win_x - 160, win_y - 200), Palette::Black);

			//クリック時にm_showConfirmをtrueにする
			auto handleBuildClick = [this](int type) {
				m_buttonSe.stop();
				m_buttonSe.play();

				//確認ダイアログを表示
				m_pendingBuildType = type;
				m_showConfirm = true;
				};

			//家を建てるボタンを追加
			if (SimpleGUI::Button(U"民家", Vec2(win_x - 300, win_y - 160))) { handleBuildClick(10); }

			//農場を建てるボタンを追加
			if (SimpleGUI::Button(U"農場", Vec2(win_x - 300, win_y - 110))) { handleBuildClick(6); }

			//牧場を建てるボタンを追加
			if (SimpleGUI::Button(U"牧場", Vec2(win_x - 300, win_y - 60))) { handleBuildClick(5); }

			//鉱山を建てるボタンを追加
			if (SimpleGUI::Button(U"鉱山", Vec2(win_x - 210, win_y - 160))) { handleBuildClick(4); }

			//精錬所を建てるボタンを追加
			if (SimpleGUI::Button(U"精錬所", Vec2(win_x - 210, win_y - 110))) { handleBuildClick(8); }

			//加工場を建てるボタンを追加
			if (SimpleGUI::Button(U"加工場", Vec2(win_x - 210, win_y - 60))) { handleBuildClick(12); }

			//交易所を建てるボタンを追加
			if (SimpleGUI::Button(U"交易所", Vec2(win_x - 120, win_y - 160))) { handleBuildClick(7); }

			break;
		}
		case 3:	//湖
			break;
		case 4:	//鉱山
			m_font(U"資源を得る").drawAt(Vec2(win_x - 160, win_y - 180), Palette::Black);
			if (SimpleGUI::Button(U"鉱石を獲得", Vec2(win_x - 230, win_y - 120)))
			{
				m_buttonSe.stop();
				m_buttonSe.play();

				if (m_resourceHandler)
				{
					m_resourceHandler(m_currentTileType);
				}
			}
			break;
		case 5:	//牧場
			m_font(U"資源を得る").drawAt(Vec2(win_x - 160, win_y - 180), Palette::Black);
			if (SimpleGUI::Button(U"羊毛を獲得", Vec2(win_x - 230, win_y - 120)))
			{
				m_buttonSe.stop();
				m_buttonSe.play();

				if (m_resourceHandler)
				{
					m_resourceHandler(m_currentTileType);
				}
			}
			break;
		case 6:	//農場
			m_font(U"資源を得る").drawAt(Vec2(win_x - 160, win_y - 180), Palette::Black);
			if (SimpleGUI::Button(U"食料を獲得", Vec2(win_x - 230, win_y - 120)))
			{
				m_buttonSe.stop();
				m_buttonSe.play();

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

			if (m_processHandler)
			{
				if (SimpleGUI::Button(U"精錬：鉱石→インゴット", Vec2(win_x - 290, win_y - 120)))
				{
					m_buttonSe.stop();
					m_buttonSe.play();

					m_processHandler(8);	//精錬所IDを渡す
				}
			}
			break;
		case 9:	//橋
			break;
		case 10:	//家1
		{
			m_font(U"アップグレード").drawAt(Vec2(win_x - 160, win_y - 200), Palette::Black);

			//クリック時にm_showConfirmをtrueにする
			auto handleBuildClick = [this](int type) {
				m_buttonSe.stop();
				m_buttonSe.play();

				//確認ダイアログを表示
				m_pendingBuildType = type;
				m_showConfirm = true;
				};

			//家を建てるボタンを追加
			if (SimpleGUI::Button(U"大きな民家", Vec2(win_x - 230, win_y - 120))) { handleBuildClick(11); }
			
			break;
		}
		case 11:	//家2
			break;
		case 12:	//加工場
			m_font(U"資源を加工する").drawAt(Vec2(win_x - 160, win_y - 200), Palette::Black);
			if (m_processHandler)
			{
				//原木→木材 (ID 1201)
				if (SimpleGUI::Button(U"加工：原木→木材", Vec2(win_x - 260, win_y - 160)))
				{
					m_buttonSe.stop();
					m_buttonSe.play();

					m_processHandler(1201);
				}
				//石材→レンガ (ID 1202)
				if (SimpleGUI::Button(U"加工：石材→レンガ", Vec2(win_x - 270, win_y - 110)))
				{
					m_buttonSe.stop();
					m_buttonSe.play();

					m_processHandler(1202);
				}
				//羊毛→布 (ID 1203)
				if (SimpleGUI::Button(U"加工：羊毛→布", Vec2(win_x - 250, win_y - 60)))
				{
					m_buttonSe.stop();
					m_buttonSe.play();

					m_processHandler(1203);
				}
			}
			break;
		}
	}

	//建築確認ダイアログの描画と処理
	if (m_showConfirm)
	{
		//画面中央の位置を計算
		const Vec2 center = Scene::Center();
		Vec2 currentPos = center - Vec2(0, 100);	//表示開始位置

		//「建築しますか？」の表示
		m_font(U"建築しますか？").drawAt(currentPos, Palette::White);
		currentPos.y += 40;	//次の行へ

		//必要資源の表示
		if (m_pBuildCosts && m_pBuildCosts->count(m_pendingBuildType))
		{
			const auto& costs = m_pBuildCosts->at(m_pendingBuildType);

			for (const auto& cost : costs)
			{
				//「資源名：量」の表記
				const String line = U"{}：{}"_fmt(ToString(cost.type), cost.amount);
				m_font(line).drawAt(currentPos, Palette::Yellow); // 資源が足りない場合の色分けは省略
				currentPos.y += 25;	//縦に並べる
			}
		}

		currentPos.y += 40;	//ボタン行へ

		//はい、いいえボタン
		const Vec2 yesPos = currentPos - Vec2(50, 0);	//中央から左に寄せる
		const Vec2 noPos = currentPos + Vec2(50, 0);	//中央から右に寄せる

		//「はい」ボタン
		if (SimpleGUI::Button(U"はい", yesPos))
		{
			m_buttonSe.stop(); m_buttonSe.play();

			//Gameクラスに建築を依頼
			if (m_buildHandler)
			{
				m_buildHandler(m_pendingBuildType);
			}
			//処理完了後ダイアログを非表示にする
			m_showConfirm = false;
			m_pendingBuildType = -1;
		}

		//「いいえ」ボタン
		if (SimpleGUI::Button(U"いいえ", noPos))
		{
			m_buttonSe.stop(); m_buttonSe.play();

			//ダイアログを非表示にする
			m_showConfirm = false;
			m_pendingBuildType = -1;
		}
	}
}
