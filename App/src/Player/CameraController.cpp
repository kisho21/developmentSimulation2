#include "CameraController.hpp"

//CameraController::CameraController(s3d::DebugCamera3D& cam)
//	: m_cam(cam)
//{
//}
//
//void CameraController::setView(const s3d::Vec3& eyePosition, const s3d::Vec3& lookAt)
//{
//	m_cam.setView(eyePosition, lookAt, s3d::Vec3::UnitY());
//}









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
	const double cp = Cos(m_pitch), sp = Sin(m_pitch);
	const double cy = Cos(m_yaw), sy = Sin(m_yaw);

	const Vec3 forward{ cy * cp, sp, sy * cp };
	const Vec3 right = forward.cross({ 0, 1, 0 }).normalized();
	const Vec3 up = right.cross(forward).normalized();

	//右クリック
	bool isRightDrag = MouseR.pressed();
	Vec2 mouseRightDelta = isRightDrag ? PlayerInput::mouseDelta() : Vec2{ 0, 0 };

	if (Abs(mouseRightDelta.x) < 0.01) mouseRightDelta.x = 0.0;
	if (Abs(mouseRightDelta.y) < 0.01) mouseRightDelta.y = 0.0;

	m_yaw += mouseRightDelta.x * Config::CamRotateSpeed;
	m_pitch += mouseRightDelta.y * Config::CamRotateSpeed;
	m_pitch = Clamp(m_pitch, -PitchLimit, PitchLimit);

	if (isRightDrag) {
		Cursor::RequestStyle(CursorStyle::Default);
	}

	//マウスホイール
	bool isMiddleDrag = MouseM.pressed();
	Vec2 mouseMiddleDelta = isMiddleDrag ? PlayerInput::mouseDelta() : Vec2{ 0, 0 };

	if (Abs(mouseMiddleDelta.x) < 0.01) mouseMiddleDelta.x = 0.0;
	if (Abs(mouseMiddleDelta.y) < 0.01) mouseMiddleDelta.y = 0.0;
	
	Vec3 moveFlat{ -mouseMiddleDelta.x, 0, mouseMiddleDelta.y };
	
	if (moveFlat.lengthSq() > 0.0) {
		m_eye += moveFlat.normalized() * (Config::CamMoveSpeed * deltaTime);
	}
	
	//ホイールスクロール
	double wheelScrollDelta = Mouse::Wheel();
	const Vec3 viewDir = (m_cam.getLookAtVector() - m_eye).normalized();

	if (Abs(wheelScrollDelta) > 0.01)
	{
		m_eye += forward * -wheelScrollDelta * Config::CamZoomSpeed;
	}
	
	m_cam.setView(m_eye, m_eye + forward, up);
	if (m_eye.y < 10) { m_eye.y = 10; }
}
