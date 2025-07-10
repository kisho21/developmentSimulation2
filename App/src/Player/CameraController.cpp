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
	//ホイールボタン
	bool isMiddleDrag = MouseM.pressed();
	Vec2 mouseMiddleDelta = isMiddleDrag ? PlayerInput::mouseDelta() : Vec2{ 0, 0 };

	if (Abs(mouseMiddleDelta.x) < 0.01) mouseMiddleDelta.x = 0.0;
	if (Abs(mouseMiddleDelta.y) < 0.01) mouseMiddleDelta.y = 0.0;

	m_yaw += mouseMiddleDelta.x * Config::CamRotateSpeed;
	m_pitch += mouseMiddleDelta.y * Config::CamRotateSpeed;
	m_pitch = Clamp(m_pitch, -PitchLimit, PitchLimit);

	if (isMiddleDrag) {
		Cursor::RequestStyle(CursorStyle::Default);
	}

	//右クリック
	bool isRightDrag = MouseR.pressed();
	Vec2 mouseRightDelta = isRightDrag ? PlayerInput::mouseDelta() : Vec2{ 0, 0 };

	if (Abs(mouseRightDelta.x) < 0.01) mouseRightDelta.x = 0.0;
	if (Abs(mouseRightDelta.y) < 0.01) mouseRightDelta.y = 0.0;
	
	Vec3 moveFlat{ -mouseRightDelta.x, 0, mouseRightDelta.y };
	
	if (moveFlat.lengthSq() > 0.0) {
		m_eye += moveFlat.normalized() * (Config::CamMoveSpeed * deltaTime);
	}

	//ホイールスクロール


	//Vec3 move{};
	//if (PlayerInput::KeyForward()) move += forward;				//移動量
	//if (PlayerInput::KeyBackward()) move -= forward;
	//if (PlayerInput::KeyLeft()) move += right;
	//if (PlayerInput::KeyRight()) move -= right;
	//if (PlayerInput::KeyUp()) move += up;
	//if (PlayerInput::KeyDown()) move -= up;

	//if (move.lengthSq() > 0.0) {
	//	m_eye += move.normalized() * (Config::CamMoveSpeed * deltaTime);
	//}
	const double cp = Cos(m_pitch), sp = Sin(m_pitch);
	const double cy = Cos(m_yaw), sy = Sin(m_yaw);

	const Vec3 forward{ cy * cp, sp, sy * cp };
	const Vec3 right = forward.cross({ 0, 1, 0 }).normalized();
	const Vec3 up = right.cross(forward).normalized();

	m_cam.setView(m_eye, m_eye + forward, up);
}
