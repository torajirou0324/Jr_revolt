#include <fstream>
#include <sstream>
#include <string>
#include <DxLib.h>
#include "MapManager.h"

MapManager::MapManager()
{
	for (int j = 0; j < 12; j++)
	{
		for (int i = 0; i < 16; i++)
		{
			mData[j][i] = 0;
		}
	}
}

MapManager::MapManager(std::string str)
{
	std::ifstream ifs(str);     // ファイル読み取り専用ストリーム

	if (ifs.fail()) // ファイルオープンに失敗したらそこで終了
	{
		return;
	}

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

	// 文字列を使った読み込み
	const char job[] = "mapTip";
	for (int i = 1; i < 31; i++)
	{
		std::stringstream fname;
		fname << "data/MapTip/" << job << i << ".png";
		mMapTip[i] = LoadGraph(fname.str().c_str());
	}
	mMapTip[0] = 0;
}

MapManager::MapManager(std::string str, std::string str1, std::string str2)
	: mDataX(0)
	, mDataX2(1920)
	, mDataX3(3840)
{
	std::ifstream ifs(str);     // ファイル読み取り専用ストリーム
	std::ifstream ifs1(str1);     // ファイル読み取り専用ストリーム
	std::ifstream ifs2(str2);     // ファイル読み取り専用ストリーム

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

	// 文字列を使った読み込み
	const char job[] = "mapTip";
	for (int i = 1; i < 31; i++)
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
			auto num2 = mData2[j][i];
			auto num3 = mData3[j][i];
			if (num == 3 || num == 17 || num == 29 || num2 == 3 || num2 == 17 || num2 == 29 || num3 == 3 || num3 == 17 || num3 == 29)
			{
				if (Collision(px, py, i, j, mDataX)) { return true; }
				if (Collision(px, py, i, j, mDataX2)) { return true; }
				if (Collision(px, py, i, j, mDataX3)) { return true; }
			}
		}
	}
	return false;
}

bool MapManager::Collision(int px, int py, int i, int j, int MapPosX)
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

void MapManager::Draw()
{
	for (int j = 0; j < HEIGHT_MAX; j++)
	{
		for (int i = 0; i < WIDTH_MAX; i++)
		{
			auto num = mData[j][i];
			DrawGraph(i * 120 + mDataX, j * 90, mMapTip[num], TRUE);
			num = mData2[j][i];
			DrawGraph(i * 120 + mDataX2, j * 90, mMapTip[num], TRUE);
			num = mData3[j][i];
			DrawGraph(i * 120 + mDataX3, j * 90, mMapTip[num], TRUE);
		}
	}
}

void MapManager::MapXAdd()
{
	mDataX++;
	mDataX2++;
	mDataX3++;
}

void MapManager::MapXSub()
{
	mDataX--;
	mDataX2--;
	mDataX3--;
}
