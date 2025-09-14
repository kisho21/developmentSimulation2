#include "SceneTitle.hpp"

SceneTitle::SceneTitle()
	: m_titleFont{ 50 }
	, m_messageFont{ 20 }
{
}

void SceneTitle::Init()
{
	m_requestChange = false;
	m_isKeyInputDetected = false;
}

void SceneTitle::Update()
{
	//キー入力でシーン切り替え
	if (KeySpace.down())
	{
		m_requestChange = true;
		m_isKeyInputDetected = true;
	}
}

void SceneTitle::Draw() const
{
	m_titleFont(U"タイトル画面").drawAt(s3d::Scene::Center());
	m_messageFont(U"スペースキーでゲームへ").drawAt(s3d::Scene::Center().movedBy(0, 50));


	// デバッグ表示
	if (m_requestChange)
	{
		m_messageFont(U"スペースキーが押されました！").draw(50, 50);
	}
}
