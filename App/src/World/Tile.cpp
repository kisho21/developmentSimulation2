#include <random>
#include "Tile.hpp"

Tile::Tile()
	: m_rotate{ Quaternion::RotateY(60_deg) }
	, m_bridgeModel{ U"image/model/bridge.obj" }
	, m_grassModel{ U"image/model/grass.obj" }
	, m_house1Model{ U"image/model/building-house.obj" }
	, m_house2Model{ U"image/model/building-village.obj" }
	, m_farmModel{ U"image/model/building-farm.obj" }
	, m_mineModel{ U"image/model/building-mine.obj" }
	, m_sheepModel{ U"image/model/building-sheep.obj" }
	, m_smelterModel{ U"image/model/building-smelter.obj" }
	, m_tradeModel{ U"image/model/building-market.obj" }
	, m_processingModel{ U"image/model/building-mill.obj" }
	, m_forestModel{ U"image/model/grass-forest.obj" }
	, m_rockModel{ U"image/model/grass-hill.obj" }
	, m_lakeModel{ U"image/model/water.obj" }
{
	Model::RegisterDiffuseTextures(m_bridgeModel, TextureDesc::MippedSRGB);		//テクスチャ
	m_tileTypes.resize(30, std::vector<int>(30));	//初期化　30*30想定

	//乱数を生成
	std::random_device seed_gen;
	std::mt19937 engine(seed_gen());
	std::uniform_int_distribution<> dist(0, 3);		//0～3の4種類

	//ランダムなタイルを配置
	for (int col = 0; col < 30; col++) {
		for (int row = 0; row < 30; row++) {
			m_tileTypes[col][row] = dist(engine);
		}
	}
}

void Tile::Draw() const
{
	//3D描画
	{
		//タイルの敷き詰め
		for (int col = 0; col < 30; col++) {		//z
			for (int row = 0; row < 30; row++) {	//x

				double x_gap = 0;
				if (col % 2 == 1) {
					x_gap = 0.5;
				}

				double x = row + x_gap;
				double z = 0.866 * col;

				//タイルの種類を取得
				int tileType = m_tileTypes[col][row];

				//モデルが置き換えられたかチェック
				if (m_replacedModels.count({ row, col }))
				{
					m_replacedModels.at({ row, col }).draw(Vec3(x, 0, z));
				}
				//最初に住居を1つ、それ以外はランダム
				else if (row == 14 && col == 14)
				{
					m_house1Model.draw(Vec3(x, 0, z));
				}
				else if (row >= 14 && row <= 15 && col >= 14 && col <= 15)
				{
					m_grassModel.draw(Vec3(x, 0, z));
				}
				else
				{
					//ランダム生成したいタイル
					switch (tileType) {
					case 0:
						m_forestModel.draw(Vec3(x, 0, z));
						break;
					case 1:
						m_rockModel.draw(Vec3(x, 0, z));
						break;
					case 2:
						m_grassModel.draw(Vec3(x, 0, z));
						break;
					case 3:
						m_lakeModel.draw(Vec3(x, 0, z));
						break;
					}
				}
			}
		}
	}
}

const Model& Tile::getModel(int tileType) const
{
	switch (tileType)
	{
	case 0: return m_forestModel;
	case 1: return m_rockModel;
	case 2: return m_grassModel;
	case 3: return m_lakeModel;
	case 4: return m_mineModel;
	case 5: return m_sheepModel;
	case 6: return m_farmModel;
	case 7: return m_tradeModel;
	case 8: return m_smelterModel;
	case 9: return m_bridgeModel;
	case 10: return m_house1Model;
	case 11: return m_house2Model;
	case 12: return m_processingModel;
	}
	// エラーを避けるためのフォールバック
	return m_grassModel;
}

void Tile::setTileModel(const GridIndex& index, const Model& newModel)
{
	m_replacedModels[index] = newModel;
}

void Tile::updateTileType(const GridIndex& index, int newType)
{
	m_tileTypes[index.col][index.row] = newType;
}
