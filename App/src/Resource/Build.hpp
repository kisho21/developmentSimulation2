#pragma once
#include <Siv3D.hpp>
#include "Resource.hpp"

// 建築コストを定義する構造体
struct BuildCost
{
	ResourceType type;
	int amount;
};
