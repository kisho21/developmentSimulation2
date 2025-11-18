#pragma once
#include <Siv3D.hpp>
#include <functional>			//std::functionを使うため追加
#include "../World/Tile.hpp"	//TileTypeを使うためインクルード
#include "../Resource/Build.hpp"

// 建築UI
class ArchitectUi
{
public:
	ArchitectUi();
	void Draw();

	//UIの表示を制御する関数
	void show(int tileType);
	void hide();

	//建築ハンドラ
	void setBuildHandler(std::function<void(int)> handler) { m_buildHandler = handler; }
	//資源獲得ハンドラ
	void setResourceHandler(std::function<void(int)> handler) { m_resourceHandler = handler; }
	//資源加工/精錬ハンドラの型定義
	using ProcessHandler = std::function<void(int)>;
	//ハンドラを設定する関数
	void setProcessHandler(ProcessHandler handler);
	//建築コスト情報を設定する関数
	void setBuildCosts(const std::map<int, std::vector<BuildCost>>* costs) { m_pBuildCosts = costs; }

private:
	Texture m_botUi;
	bool m_isVisible = false;
	int m_currentTileType = -1;
	s3d::Font m_font;

	Audio m_buttonSe;

	std::function<void(int)> m_buildHandler;
	std::function<void(int)> m_resourceHandler;

	//資源加工・精錬ハンドラ
	ProcessHandler m_processHandler;

	//建築コストを保持するポインタ
	const std::map<int, std::vector<BuildCost>>* m_pBuildCosts = nullptr;

	//建築確認ダイアログの状態管理
	bool m_showConfirm = false;			//確認ダイアログ表示フラグ
	int m_pendingBuildType = -1;		//建築開始を待っているタイルタイプID
};
