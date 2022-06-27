#pragma once
#include"SceneBase.h"

class Player;
class EnemyManager;
class MapManager;

class PlayScene : public SceneBase
{
public:
	PlayScene();
	~PlayScene();

	TAG_SCENE Update()override;
	void Draw()override;
	void MapMove();

private:
	Player* m_pPlayer;
	EnemyManager* m_pEnemyManager;
	MapManager* m_pMap;

	int mStatusImg;

	bool mLeftEndFlag;
	bool mRightEndFlag;
};