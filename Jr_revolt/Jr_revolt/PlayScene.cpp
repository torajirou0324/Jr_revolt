#include <DxLib.h>
#include "PlayScene.h"
#include "Player.h"
#include "MapManager.h"

PlayScene::PlayScene()
	: img(LoadGraph("data/Enemy/Knight/Knight0.png"))
	, mStatusImg(LoadGraph("data/BackGround/StatusImg.png"))
{
	m_pPlayer = new Player(0, 810);
	m_pMap = new MapManager("data/csv/map1.csv", "data/csv/map2.csv", "data/csv/map2.csv");
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
	auto px = m_pPlayer->GetPosX();
	auto py = m_pPlayer->GetPosY();
	if (m_pPlayer->GetPosX() > 640)
	{
		m_pPlayer->SetPosX(640);
		if(m_pMap->GetPosX3() > 0)
		{
			auto num = m_pMap->GetPosX();
			num--;
			m_pMap->SetPosX(num);
			num = m_pMap->GetPosX2();
			num--;
			m_pMap->SetPosX2(num);
			num = m_pMap->GetPosX3();
			num--;
			m_pMap->SetPosX3(num);
		}
	}
	if (m_pPlayer->GetPosX() < 0)
	{
		m_pPlayer->SetPosX(0);
		if (m_pMap->GetPosX() < 0)
		{
			auto num = m_pMap->GetPosX();
			num++;
			m_pMap->SetPosX(num);
			num = m_pMap->GetPosX2();
			num++;
			m_pMap->SetPosX2(num);
			num = m_pMap->GetPosX3();
			num++;
			m_pMap->SetPosX3(num);
		}
	}
	m_pPlayer->SetJumpFlag(m_pMap->CollisionManager(px, py));

	return TAG_SCENE::TAG_NONE;
}

void PlayScene::Draw()
{
	m_pMap->Draw();
	DrawGraph(0, 0, mStatusImg, FALSE);
	DrawGraph(1000, 810, img, TRUE);
	DrawFormatString(20, 10, GetColor(255, 255, 255), "%s", m_pPlayer->GetPlayerName().c_str());
	m_pPlayer->Draw();
}
