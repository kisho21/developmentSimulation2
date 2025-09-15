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

	void setBuildHandler(std::function<void(int)> handler) { m_buildHandler = handler; }

private:
	Texture m_botUi;
	bool m_isVisible = false;
	int m_currentTileType = -1;
	s3d::Font m_font;
	std::function<void(int)> m_buildHandler;
};
