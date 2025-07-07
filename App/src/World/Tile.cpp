#include "Tile.hpp"

Tile::Tile()
	: m_rotate{ Quaternion::RotateY(60_deg) }
	, m_bridgeModel{ U"image/bridge.obj" }
	, m_grassModel{ U"image/grass.obj" }
{
	Model::RegisterDiffuseTextures(m_bridgeModel, TextureDesc::MippedSRGB);		//テクスチャ
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

				m_grassModel.draw(Vec3(x, 0, z));
			}
		}
	}
}
