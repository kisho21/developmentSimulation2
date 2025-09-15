#pragma once
#include <Siv3D.hpp>

//class CameraController
//{
//public:
//	// コンストラクタにカメラの参照を渡す
//	CameraController(s3d::DebugCamera3D& cam);
//
//	// カメラの視点を設定する
//	void setView(const s3d::Vec3& eyePosition, const s3d::Vec3& lookAt);
//
//private:
//	s3d::DebugCamera3D& m_cam;
//};








#include "../Core/Config.hpp"
#include "PlayerInput.hpp"

class CameraController
{
public:
	explicit CameraController(BasicCamera3D& cam);
	void Update(double deltaTime);

private:
	BasicCamera3D& m_cam;
	Vec3 m_eye;				//カメラの場所
	double m_yaw;			//横回転
	double m_pitch;			//上下の傾き、上限を設ける
	static constexpr double PitchLimit{ 80_deg };	//上下80度まで
};
