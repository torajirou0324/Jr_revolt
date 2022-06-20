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
	MapManager(std::string str, std::string str1, std::string str2);
	~MapManager();

	bool CollisionManager(float px, float py);
	bool Collision(float px, float py,int i,int j,int MapPosX);
	void Draw();

	// セッター
	void SetPosX(const int& _x) { mDataX = _x; }
	void SetPosX2(const int& _x) { mDataX2 = _x; }
	void SetPosX3(const int& _x) { mDataX3 = _x; }

	// ゲッター
	const int& GetPosX() const { return mDataX; }
	const int& GetPosX2() const { return mDataX2; }
	const int& GetPosX3() const { return mDataX3; }
private:
	int mData[HEIGHT_MAX][WIDTH_MAX];
	int mData2[HEIGHT_MAX][WIDTH_MAX];
	int mData3[HEIGHT_MAX][WIDTH_MAX];
	int mDataX;
	int mDataX2;
	int mDataX3;
	int mMapTip[31];
};