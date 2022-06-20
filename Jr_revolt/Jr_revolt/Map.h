#pragma once
#define WIDTH_MAX 16
#define HEIGHT_MAX 12
#define WIDTH_SIZE 120
#define HEIGHT_SIZE 90
#include <string>

class Map
{
public:
	Map();
	Map(std::string str);
	~Map();

	bool Collision(float px, float py);
	void Draw();
private:
	int mData[HEIGHT_MAX][WIDTH_MAX];
	int mMapTip[31];
};