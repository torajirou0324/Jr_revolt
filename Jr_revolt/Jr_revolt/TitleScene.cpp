#include <DxLib.h>
#include "TitleScene.h"
#include "Input.h"
#include "Player.h"
#include "MapManager.h"

TitleScene::TitleScene()
	: GameNameImg(LoadGraph("data/BackGround/GameName.png"))
	, mBackImg(LoadGraph("data/BackGround/TitleImg.png"))
	, mBackBlackImg(LoadGraph("data/BackGround/BackBlack.png"))
	, mExitImg(LoadGraph("data/BackGround/Exit.png"))
	, mStartImg(LoadGraph("data/BackGround/Start.png"))
	, mArrowImg(LoadGraph("data/BackGround/arrow.png"))
	, mAlphaNum(0)
	, mStartFlag(false)
{
	m_pPlayer = new Player(810,720);
	m_pMap = new MapManager("data/csv/map0.csv");
}

TitleScene::~TitleScene()
{
	delete m_pPlayer;
	delete m_pMap;
}

TAG_SCENE TitleScene::Update()
{
	if (!mStartFlag)
	{
		m_pPlayer->Update();
	}

	// �v���C���[��X���W��1920�𒴂����玟�̃V�[���J�ڂ̏���������
	if (m_pPlayer->GetPosX() > 1920)
	{
		mStartFlag = true;
	}
	// ���̃V�[���֍s���Ƃ���ʂ��Ó]������
	if (mStartFlag)
	{
		mAlphaNum++;
		if (mAlphaNum == 255)
		{
			return TAG_SCENE::TAG_PLAY;
		}
	}
	
	// �Q�[���I���������Ԃ�
	if (m_pPlayer->GetPosX() < -150) { return TAG_SCENE::TAG_ESCAPE; }

	// �V�[�����؂�ւ��Ȃ�����Ԃ�
	return TAG_SCENE::TAG_NONE;
}

void TitleScene::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	DrawGraph(0, 0, mBackImg, FALSE);
	m_pMap->Draw();
	DrawGraph(100, 600, mExitImg, TRUE);
	DrawTurnGraph(20, 700, mArrowImg, TRUE);
	DrawGraph(1500, 600, mStartImg, TRUE);
	DrawGraph(1600, 700, mArrowImg, TRUE);
	DrawGraph(300, 300, GameNameImg, TRUE);
	m_pPlayer->Draw();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, mAlphaNum);
	DrawGraph(0, 0, mBackBlackImg, FALSE);
}