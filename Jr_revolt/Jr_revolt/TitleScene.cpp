#include <fstream>
#include <DxLib.h>
#include "TitleScene.h"
#include "Input.h"
#include "Player.h"
#include "Map.h"

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
	m_pMap = new Map("data/csv/map0.csv");
}

TitleScene::~TitleScene()
{
	delete m_pPlayer;
	delete m_pMap;
}

TAG_SCENE TitleScene::Update()
{
	// プレイヤーのX座標が1920を超えたら次のシーン遷移の準備をする
	if (m_pPlayer->GetPosX() > 1890.0f)
	{
		mStartFlag = true;
	}

	// 次のシーンへ行くとき画面を暗転させる
	if (mStartFlag)
	{
		mAlphaNum++;
		if (mAlphaNum == 255)
		{
			SetFontSize(32);
			char string[10];
			DrawString(700, 500, "名前を決めろ（半角英字で10桁）", GetColor(255, 255, 255), 0U);
			KeyInputString(700, 540, 10, string, TRUE);
			std::ofstream ofs("data/txt/PlayerName.txt");
			ofs << string;
			return TAG_SCENE::TAG_PLAY;
		}
	}
	else
	{
		m_pPlayer->Update();
		auto px = m_pPlayer->GetPosX();
		auto py = m_pPlayer->GetPosY();
		m_pPlayer->SetJumpFlag(m_pMap->Collision(px, py));
	}
	
	// ゲーム終了する情報を返す
	if (m_pPlayer->GetPosX() < -120.0f) { return TAG_SCENE::TAG_ESCAPE; }

	// シーンが切り替わらない情報を返す
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