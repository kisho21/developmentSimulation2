#include <random>
#include "Tile.hpp"
#include "Grid.hpp"

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

				//最初に住居を1つ、それ以外はランダム
				if (row == 14 && col == 14)
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
}

Optional<TileGrid> Tile::getGridPosFromWorldPos(const Vec3& worldPos) const
{
	//タイルの描画時に使用した座標変換の逆を計算します
	//worldPos.zからおおよその列（col）を計算
	const int col = static_cast<int>(std::round(worldPos.z / 0.866));

	//偶数/奇数行のオフセットを考慮してx座標を調整
	const double x_gap = (col % 2 == 1) ? 0.5 : 0.0;
	const int row = static_cast<int>(std::round(worldPos.x - x_gap));

	//計算したグリッド座標がマップの範囲内にあるかチェック
	if (col >= 0 && col < m_tileTypes.size() &&
		row >= 0 && row < m_tileTypes[0].size())
	{
		return TileGrid{ row, col };
	}

	return none; //範囲外の場合はnoneを返す
}
