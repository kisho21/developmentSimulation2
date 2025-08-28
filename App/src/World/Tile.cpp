#include <random>
#include "Tile.hpp"

Tile::Tile()
	: m_rotate{ Quaternion::RotateY(60_deg) }
	, m_bridgeModel{ U"image/bridge.obj" }
	, m_grassModel{ U"image/grass.obj" }
	, m_house1Model{ U"image/building-house.obj" }
	, m_house2Model{ U"image/building-village.obj" }
	, m_farmModel{ U"image/building-farm.obj" }
	, m_mineModel{ U"image/building-mine.obj" }
	, m_sheepModel{ U"image/building-sheep.obj" }
	, m_smelterModel{ U"image/building-smelter.obj" }
	, m_tradeModel{ U"image/building-market.obj" }
	, m_processingModel{ U"image/building-mill.obj" }
	, m_forestModel{ U"image/grass-forest.obj" }
	, m_rockModel{ U"image/grass-hill.obj" }
	, m_lakeModel{ U"image/water.obj" }
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
		//草原タイルの敷き詰め
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

				//ランダム生成したいタイル
				switch (tileType) {
				case 0:
					m_grassModel.draw(Vec3(x, 0, z));
					break;
				case 1:
					m_forestModel.draw(Vec3(x, 0, z));
					break;
				case 2:
					m_rockModel.draw(Vec3(x, 0, z));
					break;
				case 3:
					m_lakeModel.draw(Vec3(x, 0, z));
					break;
				}
			}
		}
	}
}
