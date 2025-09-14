#include "Fader.hpp"

void Fader::Update()
{
	if (m_state == FadeState::Non)
	{
		return;
	}

	if (m_state == FadeState::FadeOut)
	{
		m_alpha += m_fadeSpeed * Scene::DeltaTime();
		m_alpha = s3d::Min(m_alpha, 1.0);

		if (m_alpha >= 1.0)
		{
			m_state = FadeState::Non;
		}
	}
	else if (m_state == FadeState::FadeIn)
	{
		m_alpha -= m_fadeSpeed * Scene::DeltaTime();
		m_alpha = s3d::Max(m_alpha, 0.0);

		if (m_alpha <= 0.0)
		{
			m_state = FadeState::Non;
		}
	}
}

void Fader::Draw() const
{
	if (m_state == FadeState::Non)
	{
		return;
	}

	//ColorF(R, G, B, A) でアルファ値を指定して描画
	const s3d::ColorF fadeColor(0.0, 0.0, 0.0, m_alpha);
	//RectF(x, y, width, height) で画面全体を指定
	s3d::RectF(0, 0, Scene::Width(), Scene::Height()).draw(fadeColor);
}
