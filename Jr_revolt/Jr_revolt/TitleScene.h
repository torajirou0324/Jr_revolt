#pragma once
#include"SceneBase.h"

class Player;

class TitleScene : public SceneBase
{
public:
	TitleScene();
	~TitleScene();

	TAG_SCENE Update()override;
	void Draw()override;

private:
	Player* mPlayer;

	int mBackImg;
};