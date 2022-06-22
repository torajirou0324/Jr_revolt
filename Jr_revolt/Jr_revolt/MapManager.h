#pragma once
#define WIDTH_MAX 16
#define HEIGHT_MAX 12
#define WIDTH_SIZE 120
#define HEIGHT_SIZE 90

// マップシーンの番号
enum MapScene
{
	MAP_1,
	MAP_2,
	MAP_3,
	MAP_4,
	MAP_5,
	MAP_6
};

class MapManager
{
public:
	MapManager(MapScene map);
	~MapManager();

	bool CollisionManager(int px, int py);
	bool Collision(int px, int py,int i,int j,int MapPosX);
	void Init(MapScene map);
	void CreateMap(std::string str, std::string str2, std::string str3);
	void Draw();
	void MapXMove(float speed);
	MapScene GetNowMap();
	// セッター

	// ゲッター
	const int& GetPosX() const { return mDataX; }
	const int& GetPosX3() const { return mDataX3; }
private:
	MapScene mNowMap;

	int mData[HEIGHT_MAX][WIDTH_MAX];
	int mData2[HEIGHT_MAX][WIDTH_MAX];
	int mData3[HEIGHT_MAX][WIDTH_MAX];
	int mMapTip[33];
	int mMapBackGroundImg;

	float mDataX;
	float mDataX2;
	float mDataX3;
};