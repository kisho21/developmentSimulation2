/*
開拓シミュレーション
永吉 紀翔
*/
#include <Siv3D.hpp>		//Siv3D v0.6.16
#include "App/src/Core/Game.hpp"

void Main()
{
	//Scene::SetResizeMode(ResizeMode::Keep);
	Window::Resize(1280, 720);				//ウィンドウサイズ
	//Window::Resize(800, 600);
	//Window::SetFullscreen(true);
	
	Game game;

	while (System::Update())
	{
		ClearPrint();		//毎フレームスクリーンを更新する

		if (!game.Update()) break;
		game.Draw();
	}
}
