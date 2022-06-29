#pragma once
#define WIDTH_MAX 16
#define HEIGHT_MAX 12
#define WIDTH_SIZE 120
#define HEIGHT_SIZE 90
#include <fstream>
#include <sstream>
#include <string>
#include <DxLib.h>

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
	static MapManager* m_pMap;

	int mData[HEIGHT_MAX][WIDTH_MAX];
	int mData2[HEIGHT_MAX][WIDTH_MAX];
	int mData3[HEIGHT_MAX][WIDTH_MAX];
	int mMapTip[33];
	int mMapBackGroundImg;

	float mDataX;
	float mDataX2;
	float mDataX3;

	MapScene mNowMap;
public:
	// コピー禁止
	MapManager(const MapManager&) = delete;
	MapManager& operator=(const MapManager&) = delete;

	MapManager();
	~MapManager();

	static void GetInstance()
	{
		if (m_pMap == nullptr)
		{
			m_pMap = new MapManager;
		}
	}

	static void DeleteInstance()
	{
		if (m_pMap != nullptr)
		{
			delete m_pMap;
			m_pMap = nullptr;
		}
	}

	static bool CollisionManager(int px, int py)
	{
		for (int j = 0; j < HEIGHT_MAX; j++)
		{
			for (int i = 0; i < WIDTH_MAX; i++)
			{
				auto num = m_pMap->mData[j][i];
				if (num == 3 || num == 4 || num == 5 || num == 6 || num == 7 || num == 8 || num == 13 || num == 15)
				{
					if (MapCollision(px, py, i, j, m_pMap->mDataX)) { return true; }
				}
				num = m_pMap->mData2[j][i];
				if (num == 3 || num == 4 || num == 5 || num == 6 || num == 7 || num == 8 || num == 13 || num == 15)
				{
					if (MapCollision(px, py, i, j, m_pMap->mDataX2)) { return true; }
				}
				num = m_pMap->mData3[j][i];
				if (num == 3 || num == 4 || num == 5 || num == 6 || num == 7 || num == 8 || num == 13 || num == 15)
				{
					if (MapCollision(px, py, i, j, m_pMap->mDataX3)) { return true; }
				}
			}
		}
		return false;
	}
	static bool MapCollision(int px, int py, int i, int j, int MapPosX)
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
	static void Init(MapScene map)
	{
		m_pMap->mDataX = 0.0f;
		m_pMap->mDataX2 = 1920.0f;
		m_pMap->mDataX3 = 3840.0f;
		switch (map)
		{
		case MAP_1:
			m_pMap->mMapBackGroundImg = LoadGraph("data/BackGround/MapBackGround1.png");
			m_pMap->CreateMap("data/csv/map1.csv", "data/csv/map2.csv", "data/csv/map3.csv");
			if(MapScene::MAP_2 == m_pMap->mNowMap || MapScene::MAP_4 == m_pMap->mNowMap)
			{
				m_pMap->mDataX = -3840.0f;
				m_pMap->mDataX2 = -1920.0f;
				m_pMap->mDataX3 = 0.0f;
			}
			m_pMap->mNowMap = MapScene::MAP_1;
			break;
		case MAP_2:
			m_pMap->mMapBackGroundImg = LoadGraph("data/BackGround/MapBackGround1.png");
			m_pMap->CreateMap("data/csv/map4.csv", "data/csv/map5.csv", "data/csv/map6.csv");
			if(MapScene::MAP_1 == m_pMap->mNowMap)
			{
				m_pMap->mDataX = 0.0f;
				m_pMap->mDataX2 = 1920.0f;
				m_pMap->mDataX3 = 3840.0f;
			}
			m_pMap->mNowMap = MapScene::MAP_2;
			break;
		case MAP_3:
			break;
		case MAP_4:
			m_pMap->mMapBackGroundImg = LoadGraph("data/BackGround/MapBackGround4.png");
			m_pMap->CreateMap("data/csv/map10.csv", "data/csv/map11.csv", "data/csv/map12.csv");
			if (MapScene::MAP_1 == m_pMap->mNowMap)
			{
				m_pMap->mDataX = 0.0f;
				m_pMap->mDataX2 = 1920.0f;
				m_pMap->mDataX3 = 3840.0f;
			}
			m_pMap->mNowMap = MapScene::MAP_4;
			break;
		case MAP_5:
			break;
		case MAP_6:
			break;
		default:
			break;
		}
	}
	static void CreateMap(std::string str, std::string str2, std::string str3)
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
				m_pMap->mData[numY][numX] = std::atoi(tmp.c_str());
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
				m_pMap->mData2[numY][numX] = std::atoi(tmp.c_str());
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
				m_pMap->mData3[numY][numX] = std::atoi(tmp.c_str());
				numX++;
			}
			numY++;
		}
	}
	static void Draw()
	{
		for (auto i = 0; i < 3.0f; i++)
		{
			DrawGraphF(m_pMap->mDataX, 180.0f, m_pMap->mMapBackGroundImg, TRUE);
			DrawGraphF(m_pMap->mDataX2, 180.0f, m_pMap->mMapBackGroundImg, TRUE);
			DrawGraphF(m_pMap->mDataX3, 180.0f, m_pMap->mMapBackGroundImg, TRUE);
		}
		for (auto j = 0; j < HEIGHT_MAX; j++)
		{
			for (auto i = 0; i < WIDTH_MAX; i++)
			{
				auto num = m_pMap->mData[j][i];
				auto num2 = m_pMap->mData2[j][i];
				auto num3 = m_pMap->mData3[j][i];
				DrawGraphF(i * 120 + m_pMap->mDataX, j * 90, m_pMap->mMapTip[num], TRUE);
				DrawGraphF(i * 120 + m_pMap->mDataX2, j * 90, m_pMap->mMapTip[num2], TRUE);
				DrawGraphF(i * 120 + m_pMap->mDataX3, j * 90, m_pMap->mMapTip[num3], TRUE);

			}
		}
		DrawFormatString(500, 1000, GetColor(255, 255, 255), "%f", m_pMap->mDataX);
	}
	static void MapXMove(float speed)
	{
		m_pMap->mDataX -= speed;
		m_pMap->mDataX2 -= speed;
		m_pMap->mDataX3 -= speed;
	}
	static MapScene GetNowMap()
	{
		return m_pMap->mNowMap;
	}
	// セッター

	// ゲッター
	const static int& GetMapPosX() { return m_pMap->mDataX; }
	const static int& GetMap3PosX() { return m_pMap->mDataX3; }
};