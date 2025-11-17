#pragma once
#include <Siv3D.hpp>
#include <functional>			//std::functionを使うため追加
#include "../World/Tile.hpp"	//TileTypeを使うためインクルード

// 建築UI
class ArchitectUi
{
public:
	ArchitectUi();
	void Draw() const;

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

private:
	Texture m_botUi;
	bool m_isVisible = false;
	int m_currentTileType = -1;
	s3d::Font m_font;
	std::function<void(int)> m_buildHandler;
	std::function<void(int)> m_resourceHandler;
	ProcessHandler m_processHandler;	//資源加工/精錬ハンドラ
};
