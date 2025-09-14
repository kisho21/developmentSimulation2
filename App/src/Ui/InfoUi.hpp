#pragma once
#include <Siv3D.hpp>

//画面に常時表示するUI
//人口、金など
class InfoUi
{
public:
	InfoUi();
	void Draw() const;

private:
	Texture m_topUi;
};
