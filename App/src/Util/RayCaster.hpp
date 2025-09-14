#pragma once
#include <Siv3D.hpp>

class RayCaster
{
public:
	//画面上の2D座標から3D空間のレイを生成
	static s3d::Ray CreateRay(const s3d::BasicCamera3D& camera, const s3d::Vec2& screenPos);

	//レイが指定された平面と交差する点を計算
	static s3d::Optional<s3d::Vec3> IntersectsPlane(const s3d::Ray& ray, const s3d::Plane& plane);
};
