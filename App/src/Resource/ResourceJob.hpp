#pragma once
#include <Siv3D.hpp>
#include "Resource.hpp"

//資源獲得タスクの情報を保持する構造体
struct ResourceJob
{
	//獲得する資源のタイプと量
	std::vector<TileResource> resources;

	//タスク開始からの経過時間
	double elapsedTime = 0.0;

	//タスク完了までに必要な時間
	double requiredTime;
};
