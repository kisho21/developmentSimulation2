#pragma once
#include <Siv3D.hpp>

class RayCaster
{
public:
	//画面上の2D座標から3D空間のレイを生成
	static Ray CreateRay(const BasicCamera3D& camera, const Vec2& screenPos);

	//レイが指定された平面と交差する点を計算
	static Optional<Float3> IntersectsPlane(const Ray& ray, const Plane& plane);
};
