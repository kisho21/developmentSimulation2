#include "TileExplanation.hpp"

//タイルタイプごとの名前（Tile.cppのID順に合わせる）
const s3d::Array<s3d::String> TileExplanation::s_TileNames =
{
	U"森林",
	U"岩山",
	U"草原",
	U"湖",
	U"鉱山",
	U"牧場",
	U"農場",
	U"交易所",
	U"精錬所",
	U"橋",
	U"民家1",
	U"民家2",
	U"加工場"
};

//タイルタイプごとの短い説明
const s3d::Array<s3d::String> TileExplanation::s_TileDescriptions =
{
	U"立派な木々が生えている。",
	U"手ごろな岩石が転がっている。",
	U"何かを建てるにはちょうどいい。",
	U"橋を架ければ渡れそうだ。",
	U"良質な鉱石が採れるだろう。",
	U"羊が元気に走り回っている。",
	U"食料をまかなう重要な施設。",
	U"物流の中心地点。",
	U"溶鉱炉が煮えたぎっている。",
	U"泳げなくとも対岸へ渡れる。",
	U"少数が暮らせる小さな家。",
	U"大人数が住める大きな家。",
	U"資源を有効活用できる。"
};

s3d::Array<s3d::String> TileExplanation::getExplanation(int tileType)
{
	s3d::Array<s3d::String> lines;

	//タイルの種類
	if (tileType >= 0 && tileType < s_TileNames.size())
	{
		lines.push_back(s_TileNames[tileType]);
	}
	else
	{
		lines.push_back(U"不明なタイル");
	}

	//タイルの短い説明
	if (tileType >= 0 && tileType < s_TileDescriptions.size())
	{
		lines.push_back(s_TileDescriptions[tileType]);
	}
	else
	{
		lines.push_back(U"説明文がありません。");
	}

	//獲得できる資源
	const auto& resources = Resource::getResources(tileType);
	s3d::String resourceLine = U"入手：";

	if (resources.empty())
	{
		resourceLine += U"なし";
	}
	else
	{
		s3d::Array<s3d::String> resourceNames;
		for (const auto& res : resources)
		{
			resourceNames.push_back(ToString(res.type));
		}
		resourceLine += resourceNames.join(U"、");
	}
	lines.push_back(resourceLine);

	return lines;
}
