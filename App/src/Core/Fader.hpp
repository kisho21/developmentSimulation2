#pragma once
#include <Siv3D.hpp>
#include "Config.hpp"

class Fader
{
public:
	Fader() = default;

	void Update();
	void Draw() const;

	//フェードを開始
	void startFadeOut() { m_state = FadeState::FadeOut; }
	void startFadeIn() { m_state = FadeState::FadeIn; }
	//フェードが完了したかどうか
	bool isFinished() const { return m_state == FadeState::Non; }
	double getAlpha() const { return m_alpha; }

private:
	FadeState m_state = FadeState::Non;
	double m_alpha = 0.0;
	const double m_fadeSpeed = 1.0; // 1.0秒でフェードが完了する速度
};
