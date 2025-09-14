#include "RayCaster.hpp"

s3d::Ray RayCaster::CreateRay(const s3d::BasicCamera3D& camera, const s3d::Vec2& screenPos)
{
	return camera.screenToRay(screenPos);
}

s3d::Optional<s3d::Vec3> RayCaster::IntersectsPlane(const s3d::Ray& ray, const s3d::Plane& plane)
{
	return s3d::Optional<s3d::Vec3>(ray.intersects(plane));
}
