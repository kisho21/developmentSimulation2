//#include "SceneChangeManager.hpp"
//
//void SceneChangeManager::Update()
//{
//	switch (m_managerState)
//	{
//	case ManagerState::Standby:
//		if (m_currentScene == SceneID::Title)
//		{
//			m_sceneTitle.Update();
//			//タイトルシーンからゲームシーンへの切り替え
//			if (m_sceneTitle.isRequestToChangeScene())
//			{
//				startFadeOut();
//			}
//		}
//		else if (m_currentScene == SceneID::Game)
//		{
//			m_sceneGame.Update();
//			//ゲームシーンからタイトルシーンへの切り替え
//			if (m_sceneGame.isRequestToChangeScene())
//			{
//				startFadeOut();
//			}
//		}
//		break;
//
//	case ManagerState::FadeOut:
//		m_alpha += m_fadeSpeed * Scene::DeltaTime();
//		if (m_alpha >= 1.0)
//		{
//			m_alpha = 1.0;
//			m_managerState = ManagerState::ChangeScene;
//		}
//		break;
//
//	case ManagerState::ChangeScene:
//		//シーンの切り替え
//		if (m_currentScene == SceneID::Title)
//		{
//			m_currentScene = SceneID::Game;
//			m_sceneGame.Init();		//新しいシーンの初期化
//		}
//		else if (m_currentScene == SceneID::Game)
//		{
//			m_currentScene = SceneID::Title;
//			m_sceneTitle.Init();
//		}
//		m_managerState = ManagerState::FadeIn;
//		break;
//
//	case ManagerState::FadeIn:
//		m_alpha -= m_fadeSpeed * Scene::DeltaTime();
//		if (m_alpha <= 0.0)
//		{
//			m_alpha = 0.0;
//			m_managerState = ManagerState::Standby;
//		}
//		break;
//	}
//}
//
//void SceneChangeManager::Draw() const
//{
//	//現在のシーンを描画
//	if (m_currentScene == SceneID::Title)
//	{
//		m_sceneTitle.Draw();
//	}
//	else if (m_currentScene == SceneID::Game)
//	{
//		m_sceneGame.Draw();
//	}
//
//	//フェードアニメーションの描画
//	if (m_managerState != ManagerState::Standby)
//	{
//		const s3d::ColorF fadeColor(0.0, 0.0, 0.0, m_alpha);
//		s3d::RectF(0, 0, Scene::Width(), Scene::Height()).draw(fadeColor);
//	}
//}
//
//void SceneChangeManager::startFadeOut()
//{
//	if (m_managerState == ManagerState::Standby)
//	{
//		m_managerState = ManagerState::FadeOut;
//	}
//}
