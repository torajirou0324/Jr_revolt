#pragma once
#include"SceneBase.h"

class Player;

class PlayScene : public SceneBase
{
public:
	PlayScene();
	~PlayScene();

	TAG_SCENE Update()override;
	void Draw()override;

private:
	Player* mPlayer;
};