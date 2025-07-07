#include "CameraController.h"

CameraController::CameraController(BasicCamera3D& cam)
	: m_cam{ cam }
	, m_eye{ cam.getEyePosition() }
	, m_yaw{ 0.0 }
	, m_pitch{ 0.0 }
{
	const Vec3 viewDir = (Vec3{ 0, 0, 0 } - m_eye).normalized();
	m_yaw = Atan2(viewDir.z, viewDir.x);
	m_pitch = Asin(viewDir.y);
}

void CameraController::Update(double deltaTime)
{
	bool isLeftDrag = MouseL.pressed();
	Vec2 mouseDelta = isLeftDrag ? PlayerInput::mouseDelta() : Vec2{ 0,0 };

	if (Abs(mouseDelta.x) < 0.01) mouseDelta.x = 0.0;
	if (Abs(mouseDelta.y) < 0.01) mouseDelta.y = 0.0;

	m_yaw += mouseDelta.x * Config::CamRotateSpeed;
	m_pitch += mouseDelta.y * Config::CamRotateSpeed;
	m_pitch = Clamp(m_pitch, -PitchLimit, PitchLimit);

	if (isLeftDrag) {
		Cursor::RequestStyle(CursorStyle::Default);
	}

	const double cp = Cos(m_pitch), sp = Sin(m_pitch);
	const double cy = Cos(m_yaw), sy = Sin(m_yaw);

	const Vec3 forward{ cy * cp, sp, sy * cp };
	const Vec3 right = forward.cross({ 0, 1, 0 }).normalized();
	const Vec3 up = right.cross(forward).normalized();

	Vec3 move{};
	if (PlayerInput::KeyForward()) move += forward;				//移動量
	if (PlayerInput::KeyBackward()) move -= forward;
	if (PlayerInput::KeyLeft()) move += right;
	if (PlayerInput::KeyRight()) move -= right;
	if (PlayerInput::KeyUp()) move += up;
	if (PlayerInput::KeyDown()) move -= up;

	if (move.lengthSq() > 0.0) {
		m_eye += move.normalized() * (Config::CamMoveSpeed * deltaTime);
	}

	m_cam.setView(m_eye, m_eye + forward, up);
}
