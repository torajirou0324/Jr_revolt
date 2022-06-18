#include "PlayScene.h"
#include "Player.h"


PlayScene::PlayScene()
{
	mPlayer = new Player;
}

PlayScene::~PlayScene()
{
	delete mPlayer;
}

TAG_SCENE PlayScene::Update()
{
	mPlayer->Update();
	return TAG_SCENE::TAG_NONE;
}

void PlayScene::Draw()
{
	mPlayer->Draw();
}
