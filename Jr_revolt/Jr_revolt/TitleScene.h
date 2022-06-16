#pragma once
#include"SceneBase.h"

class TitleScene : public SceneBase
{
public:
	TitleScene();
	~TitleScene();

	TAG_SCENE Update()override;
	void Draw()override;
};