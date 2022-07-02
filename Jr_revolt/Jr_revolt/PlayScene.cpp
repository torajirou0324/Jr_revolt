#include <DxLib.h>
#include "PlayScene.h"
#include "Player.h"
#include "EnemyManager.h"
#include "MapManager.h"
#include "Collision.h"

PlayScene::PlayScene()
	: mStatusImg(LoadGraph("data/BackGround/StatusImg.png"))
	, mConfigImg(LoadGraph("data/BackGround/Config.png"))
	, mLeftEndFlag(false)
	, mRightEndFlag(false)
{
	m_pPlayer = new Player(0, 810);
	m_pEnemyManager = new EnemyManager;
	MapManager::GetInstance();
	MapManager::Init(MapScene::MAP_1);
	SetFontSize(32);
}

PlayScene::~PlayScene()
{
	delete m_pPlayer;
	delete m_pEnemyManager;
	MapManager::DeleteInstance();
}

TAG_SCENE PlayScene::Update()
{
	m_pPlayer->Update();
	m_pEnemyManager->Update();

	// マップ移動判定
	MapMove();
	auto px = m_pPlayer->GetPosX();
	auto py = m_pPlayer->GetPosY();
	m_pPlayer->SetJumpFlag(MapManager::CollisionManager(px, py));

	return TAG_SCENE::TAG_NONE;
}

void PlayScene::Draw()
{
	MapManager::Draw();
	DrawGraph(0, 0, mStatusImg, FALSE);
	DrawGraph(1300, 10, mConfigImg, TRUE);
	DrawBox(20, 70, 250, 100, GetColor(0, 255, 0), TRUE);
	DrawBox(20, 70, 250, 100, GetColor(255, 255, 255), FALSE);
	DrawBox(20, 110, 180, 140, GetColor(241, 90, 34), TRUE);
	DrawBox(20, 110, 180, 140, GetColor(255, 255, 255), FALSE);
	DrawFormatString(30, 20, GetColor(255, 255, 255), "%s", m_pPlayer->GetPlayerName().c_str());
	m_pEnemyManager->Draw();
	m_pPlayer->Draw();
}

void PlayScene::MapMove()
{
	// 右端時のマップ移動
	if (m_pPlayer->GetPosX() > 1850)
	{
		if (MapManager::GetNowMap() == MapScene::MAP_1) { MapManager::Init(MapScene::MAP_2); }
		if (MapScene::MAP_4 == MapManager::GetNowMap()) { m_pPlayer->SetPosY(720); }
		m_pPlayer->SetPosX(0);
		mLeftEndFlag = false;
	}
	// 左端時のマップ移動
	if (m_pPlayer->GetPosX() < 0)
	{
		if (MapScene::MAP_1 == MapManager::GetNowMap()) { m_pPlayer->SetPosX(0); }
		else if (MapScene::MAP_2 == MapManager::GetNowMap()) { MapManager::Init(MapScene::MAP_1); m_pPlayer->SetPosX(1850); }
	}

	// 画面3分の2の右に移動時スクロール処理
	if (m_pPlayer->GetPosX() > 1200.0f && mRightEndFlag)
	{
		m_pPlayer->SetPosX(1200.0f);
		MapManager::MapXMove(m_pPlayer->GetSpeed());
		Collision::SetMapMoveRightFlag(true);
	}
	else
	{
		Collision::SetMapMoveRightFlag(false);
	}
	if (MapManager::GetMap3PosX() > 1)
	{
		mRightEndFlag = true;
	}
	else
	{
		mRightEndFlag = false;
	}

	// 画面3分の1の左移動時スクロール処理
	if (m_pPlayer->GetPosX() < 600.0f && mLeftEndFlag)
	{
		m_pPlayer->SetPosX(600.0f);
		MapManager::MapXMove(m_pPlayer->GetSpeed());
		Collision::SetMapMoveLeftFlag(true);
	}
	else
	{
	Collision::SetMapMoveLeftFlag(false);
	}
	if (MapManager::GetMapPosX() < -0.1f)
	{
		mLeftEndFlag = true;
	}
	else
	{
		mLeftEndFlag = false;
	}
}
