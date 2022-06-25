#include <DxLib.h>
#include "SceneManager.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "Input.h"
#include "Collision.h"

SceneManager::SceneManager()
{
	CreateScene(TAG_SCENE::TAG_TITLE);
	GameLoop();
}

SceneManager::~SceneManager()
{
	if (mNowScene != nullptr) { delete mNowScene; }
}

void SceneManager::GameLoop()
{
	Input::GetInstance();
	Collision::GetInstance();
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
		if (tag == TAG_SCENE::TAG_ESCAPE) { break; }
		ClearScene();
		CreateScene(tag);
	}
	Input::DeleteInstance();
	Collision::DeleteInstance();
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
	case TAG_SCENE::TAG_CLEAR:
		break;
	case TAG_SCENE::TAG_OVER:
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
