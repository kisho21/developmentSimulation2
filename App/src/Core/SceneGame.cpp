//#include "SceneGame.hpp"
//
//void SceneGame::Init()
//{
//	m_requestChange = false;
//}
//
//void SceneGame::Update()
//{
//	//キー入力でシーン切り替え
//	if (PlayerInput::KeyUp())
//	{
//		m_requestChange = true;
//	}
//}
//
//void SceneGame::Draw() const
//{
//	s3d::Font(50)(U"タイトル画面").drawAt(Scene::Center());
//	s3d::Font(20)(U"スペースキーでゲームへ").drawAt(Scene::Center().movedBy(0, 50));
//}
