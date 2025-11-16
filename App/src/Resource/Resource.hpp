#pragma once
#include <Siv3D.hpp>

// 資源の種類を列挙型で定義
enum class ResourceType
{
	Wood,	//森
	Stone,	//岩
	Ore,	//鉱山
	Wool,	//牧場
	Food,	//農場

	Timber,	//加工場
	Breck,	//加工場
	Ingot,	//精錬所
	Cloth	//加工場
};

//ResourceTypeを文字列に変換する関数
inline String ToString(ResourceType type)
{
	switch (type)
	{
	case ResourceType::Wood: return U"原木";
	case ResourceType::Stone: return U"石材";
	case ResourceType::Ore: return U"鉱石";
	case ResourceType::Wool: return U"羊毛";
	case ResourceType::Food: return U"食料";
	case ResourceType::Timber: return U"木材";
	case ResourceType::Breck: return U"レンガ";
	case ResourceType::Ingot: return U"インゴット";
	case ResourceType::Cloth: return U"布";
	}
	return U"不明";
}

//各タイルタイプと対応する資源量を定義する構造体
struct TileResource
{
	ResourceType type;
	int amount;
};

class Resource
{
public:
	// タイルタイプごとの資源情報を取得
	static const std::vector<TileResource>& getResources(int tileType);

private:
	// 各タイルタイプが持つ資源を定義
	// staticなメンバ変数として、初期化時に設定
	static const std::map<int, std::vector<TileResource>> m_tileResources;
};
