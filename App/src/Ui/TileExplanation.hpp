#pragma once
#include <Siv3D.hpp>
#include "../Resource/Resource.hpp"

class TileExplanation
{
public:
	//タイルタイプを受け取り、説明文を格納した配列を返す
	static s3d::Array<s3d::String> getExplanation(int tileType);

private:
	//タイルタイプごとの名前、説明と入手資源を設定
	static const s3d::Array<s3d::String> s_TileNames;
	static const s3d::Array<s3d::String> s_TileDescriptions;
};
