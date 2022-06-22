#include <fstream>
#include <sstream>
#include <string>
#include <DxLib.h>
#include "Map.h"

Map::Map()
{
}

Map::Map(std::string str)
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
	for (int i = 1; i < 33; i++)
	{
		std::stringstream fname;
		fname << "data/MapTip/" << job << i << ".png";
		mMapTip[i] = LoadGraph(fname.str().c_str());
	}
	mMapTip[0] = 0;
}

Map::~Map()
{
	for (int i = 0; i < 31; i++)
	{
		DeleteGraph(mMapTip[i]);
	}
}

bool Map::Collision(float px, float py)
{
	for (int j = 0; j < HEIGHT_MAX; j++)
	{
		for (int i = 0; i < WIDTH_MAX; i++)
		{
			auto num = mData[j][i];
			if (num == 31 || num == 17 || num == 29)
			{
				if (((i * WIDTH_SIZE + 3 > px + 40 && i * WIDTH_SIZE + 3 < px + 110) ||
					(px + 40 > i * WIDTH_SIZE + 3 && px + 40 < i * WIDTH_SIZE + WIDTH_SIZE - 3)) &&
					((j * HEIGHT_SIZE > py + 121 && j * HEIGHT_SIZE < py + 121 + 59) ||
						(py + 121 > j * HEIGHT_SIZE && py + 121 < j * HEIGHT_SIZE + (HEIGHT_SIZE / 6))))
				{
					//py = i * HEIGHT_SIZE - 179;
					return true;
				}
				if (((i * WIDTH_SIZE > px + 40 && i * WIDTH_SIZE < px + 110) ||
					(px + 40 > i * WIDTH_SIZE && px + 40 < i * WIDTH_SIZE + 2)) &&
					((j * HEIGHT_SIZE + 10 > py + 121 && j * HEIGHT_SIZE + 10 < py + 121 + 59) ||
						(py + 121 > j * HEIGHT_SIZE && py + 121 < j * HEIGHT_SIZE + HEIGHT_SIZE)))
				{
					//px = j * WIDTH_SIZE - 109;
					return true;
				}
				if (((i * WIDTH_SIZE + 158 > px + 40 && i * WIDTH_SIZE + 158 < px + 110) ||
					(px + 40 > i * WIDTH_SIZE + 158 && px + 40 < i * WIDTH_SIZE + 158 + 2)) &&
					((j * HEIGHT_SIZE + 10 > py + 121 && j * HEIGHT_SIZE + 10 < py + 91 + 59) ||
						(py + 91 > j * HEIGHT_SIZE && py + 91 < j * HEIGHT_SIZE + HEIGHT_SIZE)))
				{
					//px = j * WIDTH_SIZE + 91;
					return true;
				}
			}
		}
	}
	return false;
}

void Map::Draw()
{
	for (int j = 0; j < HEIGHT_MAX; j++)
	{
		for (int i = 0; i < WIDTH_MAX; i++)
		{
			auto num = mData[j][i];
			DrawGraph(i * 120, j * 90, mMapTip[num], TRUE);
		}
	}
}
