#include <DxLib.h>
#include "PlayScene.h"
#include "Player.h"
#include "MapManager.h"

PlayScene::PlayScene()
	: img(LoadGraph("data/Enemy/Knight/Knight0.png"))
	, mStatusImg(LoadGraph("data/BackGround/StatusImg.png"))
{
	mPlayer = new Player(0, 810);
	mMap = new MapManager("data/csv/map1.csv");
}

PlayScene::~PlayScene()
{
	delete mPlayer;
	delete mMap;
}

TAG_SCENE PlayScene::Update()
{
	mPlayer->Update();
	return TAG_SCENE::TAG_NONE;
}

void PlayScene::Draw()
{
	mMap->Draw();
	DrawGraph(0, 0, mStatusImg, FALSE);
	DrawGraph(1000, 810, img, TRUE);
	mPlayer->Draw();
}
