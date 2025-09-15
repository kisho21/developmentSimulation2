#pragma once
#include <Siv3D.hpp>
#include "../Resource/Resource.hpp"

//画面に常時表示するUI
//人口、金など
class InfoUi
{
public:
	InfoUi();
	void Draw() const;

	//資源情報を設定する関数
	void setResources(const std::map<ResourceType, int>& resources);


private:
	Texture m_topUi;

	s3d::Font m_font;
	//プレイヤーの資源所持数を参照するメンバ変数
	const std::map<ResourceType, int>* m_playerResources = nullptr;
};
