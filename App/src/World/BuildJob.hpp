#pragma once
#include <Siv3D.hpp>
#include "../World/Tile.hpp" // GridIndex を使うため

//建築タスクの情報を保持する構造体
struct BuildJob
{
	GridIndex index;
	double elapsedTime = 0.0;
	double requiredTime = 0.0;
	int tileType;
};
