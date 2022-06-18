#pragma once
#include"SceneBase.h"

class Player;
class MapManager;

class TitleScene : public SceneBase
{
public:
	TitleScene();
	~TitleScene();

	TAG_SCENE Update()override;
	void Draw()override;

private:
	Player* m_pPlayer;
	MapManager* m_pMap;

	int GameNameImg;
	int mBackImg;
	int mExitImg;
	int mStartImg;
	int mArrowImg;
};