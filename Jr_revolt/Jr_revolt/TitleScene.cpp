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

	// �v���C���[��X���W��1920�𒴂����玟�̃V�[���J�ڂ̏���������
	if (mPlayer->GetPosX() > 1920)
	{
		return TAG_SCENE::TAG_PLAY;
	}

	// �V�[�����؂�ւ��Ȃ�����Ԃ�
	return TAG_SCENE::TAG_NONE;
}

void TitleScene::Draw()
{
	DrawGraph(0, 0, mBackImg, FALSE);
	mPlayer->Draw();
}