#include <DxLib.h>
#include "TitleScene.h"
#include "Input.h"
#include "Player.h"

TitleScene::TitleScene()
	: mBackImg(LoadGraph("data/BackGround/TitleImg.png"))
{
	mPlayer = new Player;
}

TitleScene::~TitleScene()
{
	delete mPlayer;
}

TAG_SCENE TitleScene::Update()
{
	mPlayer->Update();
	if (mPlayer->GetPosX() < 0) { mPlayer->SetPosX(0); }

	// プレイヤーのX座標が1920を超えたら次のシーン遷移の準備をする
	if (mPlayer->GetPosX() > 1920)
	{
		return TAG_SCENE::TAG_PLAY;
	}

	// シーンが切り替わらない情報を返す
	return TAG_SCENE::TAG_NONE;
}

void TitleScene::Draw()
{
	DrawGraph(0, 0, mBackImg, FALSE);
	mPlayer->Draw();
}