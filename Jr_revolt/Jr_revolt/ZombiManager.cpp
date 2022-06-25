#include <iostream>
#include <fstream>
#include <sstream>
#include <DxLib.h>
#include "ZombiManager.h"
#include "Zombi.h"

ZombiManager::ZombiManager()
{
	// •¶š—ñ‚ğg‚Á‚½“Ç‚İ‚İ
	const char job[] = "zonbi_idou";
	for (int i = 0; i < 6; i++)
	{
		std::stringstream fname;
		fname << "data/Enemy/Zombi/" << job << 0 << i << ".png";
		mZombiMoveImg[i] = LoadGraph(fname.str().c_str());
	}
	const char job2[] = "zonbi_kougeki";
	for (int i = 0; i < 4; i++)
	{
		std::stringstream fname;
		fname << "data/Enemy/Zombi/" << job2 << 0 << i << ".png";
		mZombiAttackImg[i] = LoadGraph(fname.str().c_str());
	}
	const char job3[] = "zonbi_taiki";
	for (int i = 0; i < 3; i++)
	{
		std::stringstream fname;
		fname << "data/Enemy/Zombi/" << job3 << 0 << i << ".png";
		mZombiImg[i] = LoadGraph(fname.str().c_str());
	}

	m_pZombi.emplace_back(new Zombi(1200, 810));
}

ZombiManager::~ZombiManager()
{
	if (!m_pZombi.empty())
	{
		for (auto it : m_pZombi)
		{
			delete it;
			it = nullptr;
		}
		m_pZombi.clear();
	}
}

void ZombiManager::Update()
{
	for (auto it : m_pZombi)
	{
		it->Update();
	}
}

void ZombiManager::Draw()
{
	for (auto it: m_pZombi)
	{
		if (it->GetVecFlag())
		{
			DrawGraphF(it->GetPosX(), it->GetPosY(), mZombiImg[it->GetImgNum()], TRUE);
		}
		else
		{
			DrawTurnGraphF(it->GetPosX(), it->GetPosY(), mZombiImg[it->GetImgNum()], TRUE);
		}
		DrawFormatString(500, 20, GetColor(255, 255, 255), "%d", it->GetPosX());
	}
}
