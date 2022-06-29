#include "MapManager.h"

MapManager* MapManager::m_pMap = nullptr;

MapManager::MapManager()
{
	mNowMap = MapScene::MAP_1;

	mDataX = 0.0f;
	mDataX2 = 1920.0f;
	mDataX3 = 3840.0f;

	// •¶š—ñ‚ğg‚Á‚½“Ç‚İ‚İ
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
