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
	Player* mPlayer;
	MapManager* mMap;

	int mStatusImg;
	int img;
};