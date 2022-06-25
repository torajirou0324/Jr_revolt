#include <fstream>
#include <sstream>
#include <string>
#include <DxLib.h>
#include "MapManager.h"
#include "Collision.h"

MapManager::MapManager(MapScene map)
{
	Init(map);
	// 文字列を使った読み込み
	const char job[] = "mapTip";
	for (int i = 1; i < 33; i++)
	{
		std::stringstream fname;
		fname << "data/MapTip/" << job << i << ".png";
		mMapTip[i] = LoadGraph(fname.str().c_str());
	}
	mMapTip[0] = 0;
}

MapManager::~MapManager()
{
}

bool MapManager::CollisionManager(int px, int py)
{
	for (int j = 0; j < HEIGHT_MAX; j++)
	{
		for (int i = 0; i < WIDTH_MAX; i++)
		{
			auto num = mData[j][i];
			if (num == 3 || num == 4 || num == 5 || num == 6 || num == 7 || num == 8 || num == 13 || num == 15)
			{
				if (MapCollision(px, py, i, j, mDataX)) { return true; }
			}
			num = mData2[j][i];
			if (num == 3 || num == 4 || num == 5 || num == 6 || num == 7 || num == 8 || num == 13 || num == 15)
			{
				if (MapCollision(px, py, i, j, mDataX2)) { return true; }
			}
			num = mData3[j][i];
			if (num == 3 || num == 4 || num == 5 || num == 6 || num == 7 || num == 8 || num == 13 || num == 15)
			{
				if (MapCollision(px, py, i, j, mDataX3)) { return true; }
			}
		}
	}
	return false;
}

bool MapManager::MapCollision(int px, int py, int i, int j, int MapPosX)
{
	if (((i * WIDTH_SIZE + MapPosX >= px + 40 && i * WIDTH_SIZE + MapPosX <= px + 110) ||
		(px + 40 >= i * WIDTH_SIZE + MapPosX && px + 40 <= i * WIDTH_SIZE + WIDTH_SIZE + MapPosX)) &&
		((j * HEIGHT_SIZE > py + 121 && j * HEIGHT_SIZE < py + 121 + 59) ||
			(py + 121 > j * HEIGHT_SIZE && py + 121 < j * HEIGHT_SIZE + (HEIGHT_SIZE / 6))))
	{
		return true;
	}
	else if (((i * WIDTH_SIZE + MapPosX > px + 40 && i * WIDTH_SIZE + MapPosX < px + 110) ||
		(px + 40 > i * WIDTH_SIZE + MapPosX && px + 40 < i * WIDTH_SIZE + 2 + MapPosX)) &&
		((j * HEIGHT_SIZE + 10 > py + 121 && j * HEIGHT_SIZE + 10 < py + 121 + 59) ||
			(py + 121 > j * HEIGHT_SIZE && py + 121 < j * HEIGHT_SIZE + HEIGHT_SIZE)))
	{
		return true;
	}
	else if (((i * WIDTH_SIZE + 158 + MapPosX > px + 40 && i * WIDTH_SIZE + 158 + MapPosX < px + 110) ||
		(px + 40 > i * WIDTH_SIZE + 158 + MapPosX && px + 40 < i * WIDTH_SIZE + 158 + 2 + MapPosX)) &&
		((j * HEIGHT_SIZE + 10 > py + 121 && j * HEIGHT_SIZE + 10 < py + 91 + 59) ||
			(py + 91 > j * HEIGHT_SIZE && py + 91 < j * HEIGHT_SIZE + HEIGHT_SIZE)))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void MapManager::Init(MapScene map)
{
	mDataX = 0;
	mDataX2 = 1920;
	mDataX3 = 3840;
	switch (map)
	{
	case MAP_1:
		mMapBackGroundImg = LoadGraph("data/BackGround/MapBackGround1.png");
		CreateMap("data/csv/map1.csv", "data/csv/map2.csv", "data/csv/map3.csv");
		mNowMap = MapScene::MAP_1;
		break;
	case MAP_2:
		mMapBackGroundImg = LoadGraph("data/BackGround/MapBackGround1.png");
		CreateMap("data/csv/map4.csv", "data/csv/map5.csv", "data/csv/map6.csv");
		mNowMap = MapScene::MAP_2;
		break;
	case MAP_3:
		break;
	case MAP_4:
		mMapBackGroundImg = LoadGraph("data/BackGround/MapBackGround4.png");
		CreateMap("data/csv/map10.csv", "data/csv/map11.csv", "data/csv/map12.csv");
		mNowMap = MapScene::MAP_4;
		break;
	case MAP_5:
		break;
	case MAP_6:
		break;
	default:
		break;
	}
}

void MapManager::CreateMap(std::string str, std::string str2, std::string str3)
{
	std::ifstream ifs(str);     // ファイル読み取り専用ストリーム
	std::ifstream ifs1(str2);     // ファイル読み取り専用ストリーム
	std::ifstream ifs2(str3);     // ファイル読み取り専用ストリーム

	std::string file = ""; // データ一時保管用配列
	int numY = 0;
	while (std::getline(ifs, file))
	{
		int numX = 0;
		std::string tmp = "";
		std::istringstream i_stream(file);

		// 区切り文字が無くなるまで文字列を区切っていく
		while (std::getline(i_stream, tmp, ','))
		{
			// 区切られた文字がtmpに入る
			mData[numY][numX] = std::atoi(tmp.c_str());
			numX++;
		}
		numY++;
	}

	numY = 0;
	while (std::getline(ifs1, file))
	{
		int numX = 0;
		std::string tmp = "";
		std::istringstream i_stream(file);

		// 区切り文字が無くなるまで文字列を区切っていく
		while (std::getline(i_stream, tmp, ','))
		{
			// 区切られた文字がtmpに入る
			mData2[numY][numX] = std::atoi(tmp.c_str());
			numX++;
		}
		numY++;
	}

	numY = 0;
	while (std::getline(ifs2, file))
	{
		int numX = 0;
		std::string tmp = "";
		std::istringstream i_stream(file);

		// 区切り文字が無くなるまで文字列を区切っていく
		while (std::getline(i_stream, tmp, ','))
		{
			// 区切られた文字がtmpに入る
			mData3[numY][numX] = std::atoi(tmp.c_str());
			numX++;
		}
		numY++;
	}
}

void MapManager::Update()
{
	Collision::MapUpdate(mDataX, mDataX3);
}

void MapManager::Draw()
{
	for (auto i = 0; i < 3.0f; i++)
	{
		DrawGraphF(mDataX, 180.0f, mMapBackGroundImg, TRUE);
		DrawGraphF(mDataX2, 180.0f, mMapBackGroundImg, TRUE);
		DrawGraphF(mDataX3, 180.0f, mMapBackGroundImg, TRUE);
	}
	for (auto j = 0; j < HEIGHT_MAX; j++)
	{
		for (auto i = 0; i < WIDTH_MAX; i++)
		{
			auto num = mData[j][i];
			auto num2 = mData2[j][i];
			auto num3 = mData3[j][i];
			DrawGraphF(i * 120 + mDataX, j * 90, mMapTip[num], TRUE);
			DrawGraphF(i * 120 + mDataX2, j * 90, mMapTip[num2], TRUE);
			DrawGraphF(i * 120 + mDataX3, j * 90, mMapTip[num3], TRUE);

		}
	}
}

void MapManager::MapXMove(float speed)
{
	mDataX -= speed;
	mDataX2 -= speed;
	mDataX3 -= speed;
}

MapScene MapManager::GetNowMap()
{
	return mNowMap;
}
