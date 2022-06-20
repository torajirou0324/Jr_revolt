#pragma once
#include"SceneBase.h"

class Player;
class Map;

class TitleScene : public SceneBase
{
public:
	TitleScene();
	~TitleScene();

	TAG_SCENE Update()override;
	void Draw()override;

private:
	Player* m_pPlayer;
	Map* m_pMap;

	int GameNameImg;
	int mBackImg;
	int mBackBlackImg;
	int mExitImg;
	int mStartImg;
	int mArrowImg;
	int mAlphaNum;

	bool mStartFlag;
};