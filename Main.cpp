/*
開拓シミュレーション
永吉 紀翔
*/
#include <Siv3D.hpp>		//Siv3D v0.6.16
#include "App/src/Core/Game.hpp"

void Main()
{
	Window::Resize(1280, 720);				//ウィンドウサイズ

	Game game;

	while (System::Update())
	{
		ClearPrint();		//毎フレームスクリーンを更新する

		if (!game.Update()) break;
		game.Draw();
	}
}
