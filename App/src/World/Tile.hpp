#pragma once
#include <Siv3D.hpp>
#include "../Core/Config.hpp"

class Tile
{
public:
	Tile();
	void Draw() const;

	const std::vector<std::vector<int>>& getTileTypes() const { return m_tileTypes; }
	const Model& getModel(int tileType) const;
	void setTileModel(const GridIndex& index, const Model& newModel);

	//家モデルを取得する関数を追加
	const Model& getHouseModel() const { return m_house1Model; }

	//タイルタイプを更新する関数
	void updateTileType(const GridIndex& index, int newType);

private:
	Quaternion m_rotate;

	std::vector<std::vector<int>> m_tileTypes;	//タイルの種類を保持する2次元配列
	std::map<GridIndex, Model> m_replacedModels;

	Model m_grassModel;			//草原
	Model m_forestModel;		//森
	Model m_rockModel;			//岩
	Model m_lakeModel;			//湖

	Model m_bridgeModel;		//橋
	Model m_house1Model;		//民家レベル1
	Model m_house2Model;		//民家レベル2
	Model m_farmModel;			//農場
	Model m_mineModel;			//鉱山
	Model m_sheepModel;			//牧場
	Model m_smelterModel;		//精錬所
	Model m_tradeModel;			//交易所
	Model m_processingModel;	//加工場
};
