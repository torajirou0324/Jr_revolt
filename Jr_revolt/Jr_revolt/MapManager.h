#pragma once
#define WIDTH_MAX 16
#define HEIGHT_MAX 12
#define WIDTH_SIZE 120
#define HEIGHT_SIZE 90

#include <string>

class MapManager
{
public:
	MapManager();
	MapManager(std::string str);
	~MapManager();

	bool Collision(float px, int py);
	void Draw();
private:
	int mData[12][16];
	int mMapTip[31];
};