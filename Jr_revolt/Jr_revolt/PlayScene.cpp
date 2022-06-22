#include <DxLib.h>
#include "PlayScene.h"
#include "Player.h"
#include "MapManager.h"

PlayScene::PlayScene()
	: mStatusImg(LoadGraph("data/BackGround/StatusImg.png"))
	, mLeftEndFlag(false)
	, mRightEndFlag(false)
{
	m_pPlayer = new Player(0, 810);
	m_pMap = new MapManager(MapScene::MAP_1);
	SetFontSize(32);
}

PlayScene::~PlayScene()
{
	delete m_pPlayer;
	delete m_pMap;
}

TAG_SCENE PlayScene::Update()
{
	m_pPlayer->Update();

	if (m_pPlayer->GetPosX() > 1850)
	{
		m_pMap->Init(MapScene::MAP_2);
		if (MapScene::MAP_4 == m_pMap->GetNowMap()) { m_pPlayer->SetPosY(720); }
		m_pPlayer->SetPosX(0);
		mLeftEndFlag = false;
	}
	if (m_pPlayer->GetPosX() < 0)
	{
		if(MapScene::MAP_1 == m_pMap->GetNowMap()){ m_pPlayer->SetPosX(0); }
		else {  }
	}
	if (m_pPlayer->GetPosX() > 1200 && mRightEndFlag)
	{
		m_pPlayer->SetPosX(1200);
		if(m_pMap->GetPosX3() > 0)
		{
			m_pMap->MapXMove(m_pPlayer->GetSpeed());
		}
		else
		{
			mRightEndFlag = false;
		}
	}
	if (m_pMap->GetPosX3() > 1)
	{
		mRightEndFlag = true;
	}
	if (m_pPlayer->GetPosX() < 600 && mLeftEndFlag)
	{
		m_pPlayer->SetPosX(600);
		if (m_pMap->GetPosX() < 0)
		{
			m_pMap->MapXMove(m_pPlayer->GetSpeed());
		}
		else
		{
			mLeftEndFlag = false;
		}
	}
	if (m_pMap->GetPosX() < -1)
	{
		mLeftEndFlag = true;

	}
	auto px = m_pPlayer->GetPosX();
	auto py = m_pPlayer->GetPosY();
	m_pPlayer->SetJumpFlag(m_pMap->CollisionManager(px, py));

	return TAG_SCENE::TAG_NONE;
}

void PlayScene::Draw()
{
	m_pMap->Draw();
	DrawGraph(0, 0, mStatusImg, FALSE);
	DrawFormatString(20, 10, GetColor(255, 255, 255), "%s", m_pPlayer->GetPlayerName().c_str());
	m_pPlayer->Draw();
}
