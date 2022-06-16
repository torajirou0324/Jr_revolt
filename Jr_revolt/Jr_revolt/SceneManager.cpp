#include <DxLib.h>
#include "SceneManager.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "Input.h"

SceneManager::SceneManager()
{
	CreateScene(TAG_SCENE::TAG_TITLE);
}

SceneManager::~SceneManager()
{
	if (mNowScene != nullptr) { delete mNowScene; }
}

void SceneManager::GameLoop()
{
	Input::GetInstance();
	while (!Input::IsPress(ESCAPE))
	{
		Input::Update();
		ClearDrawScreen();
		auto tag = mNowScene->Update();
		mNowScene->Draw();
		ScreenFlip();
		if (tag == TAG_SCENE::TAG_NONE)
		{
			continue;
		}
		ClearScene();
		CreateScene(tag);
	}
	Input::DeleteInstance();
}

void SceneManager::CreateScene(TAG_SCENE tag)
{
	switch (tag)
	{
	case TAG_SCENE::TAG_TITLE:
		mNowScene = new TitleScene;
		break;
	case TAG_SCENE::TAG_PLAY:
		mNowScene = new PlayScene;
		break;
	case TAG_SCENE::TAG_NONE:
		break;
	default:
		break;
	}
}

void SceneManager::ClearScene()
{
	if (mNowScene == nullptr)
	{

	}
	else
	{
		delete mNowScene;
		mNowScene = nullptr;
	}
}
