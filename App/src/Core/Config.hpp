#pragma once

namespace Config
{
	inline constexpr double CamMoveSpeed = { 20.0f };
	inline constexpr double CamRotateSpeed = { 0.001f };
	inline constexpr double CamFOV = { 30_deg };
	inline constexpr Vec3 CamInitialPosition{ 10, 16, -32 };
	inline constexpr double CamZoomSpeed = { 1.0f };
}
