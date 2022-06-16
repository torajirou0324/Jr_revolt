#pragma once
#include "SceneBase.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void GameLoop();

	void CreateScene(TAG_SCENE tag);
	void ClearScene();
private:
	SceneBase* mNowScene;
};