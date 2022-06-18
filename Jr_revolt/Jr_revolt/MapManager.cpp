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

MapManager::~MapManager()
{
}

void MapManager::Draw()
{
	for (int j = 0; j < 12; j++)
	{
		for (int i = 0; i < 16; i++)
		{
			auto num = mData[j][i];
			DrawGraph(i * 120, j * 90, mMapTip[num], TRUE);
		}
	}
}
