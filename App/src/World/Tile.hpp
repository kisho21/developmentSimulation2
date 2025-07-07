#pragma once
#include <Siv3D.hpp>

class Tile
{
public:
	Tile();
	void Draw() const;

private:
	Quaternion m_rotate;

	Model m_bridgeModel;		//橋
	Model m_grassModel;			//草原
};
