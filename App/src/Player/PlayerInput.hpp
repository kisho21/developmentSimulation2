#pragma once
#include <Siv3D.hpp>

struct PlayerInput
{
	static Vec2 mouseDelta() { return Cursor::DeltaF(); }
	//static bool KeyForward() { return KeyW.pressed(); }
	//static bool KeyBackward() { return KeyS.pressed(); }
	//static bool KeyLeft() { return KeyA.pressed(); }
	//static bool KeyRight() { return KeyD.pressed(); }
	//static bool KeyUp() { return KeySpace.pressed(); }
	//static bool KeyDown() { return KeyShift.pressed(); }
};

