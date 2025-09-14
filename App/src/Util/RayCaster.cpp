#include "RayCaster.hpp"

Ray RayCaster::CreateRay(const BasicCamera3D& camera, const Vec2& screenPos)
{
	return camera.screenToRay(screenPos);
}

Optional<Float3> RayCaster::IntersectsPlane(const Ray& ray, const Plane& plane)
{
	return Optional<Float3>(ray.intersectsAt(plane));
}
