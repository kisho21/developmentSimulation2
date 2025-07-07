#pragma once
#include <Siv3D.hpp>
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
