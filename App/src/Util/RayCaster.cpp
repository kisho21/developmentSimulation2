//#include "RayCaster.hpp"
//
//RayCaster::RayCaster(const BasicCamera3D& cam)
//	//: m_cam{ cam }
//{
//}
//
//std::optional<GridIndex> RayCaster::Raycast(const Tile& tile) const
//{
//	// カメラとマウスカーソル位置からレイを生成
//	const Ray ray = GlobalCamera3D().screenToRay(Cursor::PosF());
//
//	const Plane groundPlane{ 0, 1, 0, 0 }; // y=0 の平面
//
//	if (const auto hitPos = ray.intersectsAt(groundPlane))
//	{
//		// レイと地面の交差点を取得
//		Vec3 hit3D = hitPos.value();
//
//		// 地面の交差座標から六角形グリッドの座標を逆算する
//		int col = static_cast<int>(Math::Round(hit3D.z / 0.866));
//		double x_offset = (col % 2 == 1) ? 0.5 : 0;
//		int row = static_cast<int>(Math::Round(hit3D.x - x_offset));
//
//		// 計算されたインデックスが範囲内にあるか確認
//		const auto& tileTypes = tile.getTileTypes();
//		if (col >= 0 && col < tileTypes.size() && row >= 0 && row < tileTypes[0].size())
//		{
//			return GridIndex{ row, col };
//		}
//	}
//
//	return std::nullopt;
//}
