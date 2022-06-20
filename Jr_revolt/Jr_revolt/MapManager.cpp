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
	std::ifstream ifs(str);     // �t�@�C���ǂݎ���p�X�g���[��

	if (ifs.fail()) // �t�@�C���I�[�v���Ɏ��s�����炻���ŏI��
	{
		return;
	}

	std::string file = ""; // �f�[�^�ꎞ�ۊǗp�z��
	int numY = 0;
	while (std::getline(ifs, file))
	{
		int numX = 0;
		std::string tmp = "";
		std::istringstream i_stream(file);

		// ��؂蕶���������Ȃ�܂ŕ��������؂��Ă���
		while (std::getline(i_stream, tmp, ','))
		{
			// ��؂�ꂽ������tmp�ɓ���
			mData[numY][numX] = std::atoi(tmp.c_str());
			numX++;
		}
		numY++;
	}

	// ��������g�����ǂݍ���
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

bool MapManager::Collision(float px, int py)
{
	for (int j = 0; j < HEIGHT_MAX; j++)
	{
		for (int i = 0; i < WIDTH_MAX; i++)
		{
			auto num = mData[j][i];
			if (num == 3)
			{
				if (((j * WIDTH_SIZE + 3 > px + 40 && j * WIDTH_SIZE + 3 < px + 110) ||
					(px + 40 > j * WIDTH_SIZE + 3 && px + 40 < j * WIDTH_SIZE + WIDTH_SIZE - 3)) &&
					((i * HEIGHT_SIZE > y + 121 && i * HEIGHT_SIZE < y + 121 + 59) ||
						(y + 121 > i * HEIGHT_SIZE && y + 121 < i * HEIGHT_SIZE + (HEIGHT_SIZE / 6))))
				{
					y = i * HEIGHT_SIZE - 179;
					return true;
				}
				if (((j * WIDTH_SIZE > px + 40 && j * WIDTH_SIZE < px + 110) ||
					(px + 40 > j * WIDTH_SIZE && px + 40 < j * WIDTH_SIZE + 2)) &&
					((i * HEIGHT_SIZE + 10 > y + 121 && i * HEIGHT_SIZE + 10 < y + 121 + 59) ||
						(y + 121 > i * HEIGHT_SIZE && y + 121 < i * HEIGHT_SIZE + HEIGHT_SIZE)))
				{
					px = j * WIDTH_SIZE - 109;
					return true;
				}
				if (((j * WIDTH_SIZE + 158 > px + 40 && j * WIDTH_SIZE + 158 < px + 110) ||
					(px + 40 > j * WIDTH_SIZE + 158 && px + 40 < j * WIDTH_SIZE + 158 + 2)) &&
					((i * HEIGHT_SIZE + 10 > y + 121 && i * HEIGHT_SIZE + 10 < y + 91 + 59) ||
						(y + 91 > i * HEIGHT_SIZE && y + 91 < i * HEIGHT_SIZE + HEIGHT_SIZE)))
				{
					x = j * WIDTH_SIZE + 91;
					return true;
				}
			}
		}
	}
	return false;
}

void MapManager::Draw()
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
