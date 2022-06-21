#pragma once
#include"SceneBase.h"

class Player;
class MapManager;

class PlayScene : public SceneBase
{
public:
	PlayScene();
	~PlayScene();

	TAG_SCENE Update()override;
	void Draw()override;

private:
	Player* m_pPlayer;
	MapManager* m_pMap;

	int mStatusImg;

	bool mLeftEndFlag;
	bool mRightEndFlag;
};