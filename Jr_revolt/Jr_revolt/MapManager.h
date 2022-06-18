#pragma once
#include <string>

class MapManager
{
public:
	MapManager();
	MapManager(std::string str);
	~MapManager();

	void Draw();
private:
	int mData[12][16];
	int mMapTip[31];
};