#include <DxLib.h>
#include "PlayScene.h"
#include "Player.h"
#include "EnemyManager.h"
#include "MapManager.h"
#include "Collision.h"

PlayScene::PlayScene()
	: mStatusImg(LoadGraph("data/BackGround/StatusImg.png"))
	, mLeftEndFlag(false)
	, mRightEndFlag(false)
{
	m_pPlayer = new Player(0, 810);
	m_pEnemyManager = new EnemyManager;
	m_pMap = new MapManager(MapScene::MAP_1);
	SetFontSize(32);
}

PlayScene::~PlayScene()
{
	delete m_pPlayer;
	delete m_pEnemyManager;
	delete m_pMap;
}

TAG_SCENE PlayScene::Update()
{
	m_pPlayer->Update();
	m_pEnemyManager->SetMapPosX(m_pMap->GetPosX());
	m_pEnemyManager->Update();

	// �}�b�v�ړ�����
	MapMove();
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
	m_pEnemyManager->Draw();
	m_pPlayer->Draw();
}

void PlayScene::MapMove()
{
	// �E�[���̃}�b�v�ړ�
	if (m_pPlayer->GetPosX() > 1850)
	{
		if (m_pMap->GetNowMap() == MapScene::MAP_1) { m_pMap->Init(MapScene::MAP_2); }
		if (MapScene::MAP_4 == m_pMap->GetNowMap()) { m_pPlayer->SetPosY(720); }
		m_pPlayer->SetPosX(0);
		mLeftEndFlag = false;
	}
	// ���[���̃}�b�v�ړ�
	if (m_pPlayer->GetPosX() < 0)
	{
		if (MapScene::MAP_1 == m_pMap->GetNowMap()) { m_pPlayer->SetPosX(0); }
		else {}
	}

	// ���3����2�̉E�Ɉړ����X�N���[������
	if (m_pPlayer->GetPosX() > 1200.0f && mRightEndFlag)
	{
		m_pPlayer->SetPosX(1200.0f);
		m_pMap->MapXMove(m_pPlayer->GetSpeed());
		Collision::SetMapMoveRightFlag(true);
	}
	else
	{
		Collision::SetMapMoveRightFlag(false);
	}
	if (m_pMap->GetPosX3() > 1)
	{
		mRightEndFlag = true;
	}
	else
	{
		mRightEndFlag = false;
	}

	// ���3����1�̍��ړ����X�N���[������
	if (m_pPlayer->GetPosX() < 600.0f && mLeftEndFlag)
	{
		m_pPlayer->SetPosX(600.0f);
		m_pMap->MapXMove(m_pPlayer->GetSpeed());
		Collision::SetMapMoveLeftFlag(true);
	}
	else
	{
	Collision::SetMapMoveLeftFlag(false);
	}
	if (m_pMap->GetPosX() < -0.1f)
	{
		mLeftEndFlag = true;
	}
	else
	{
		mLeftEndFlag = false;
	}
}
