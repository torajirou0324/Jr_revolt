#include "EnemyManager.h"
#include "ZombiManager.h"

EnemyManager::EnemyManager()
{
	m_pZombi = new ZombiManager;
}

EnemyManager::~EnemyManager()
{
	delete m_pZombi;
}

void EnemyManager::Update()
{
	m_pZombi->Update();
}

void EnemyManager::Draw()
{
	m_pZombi->Draw();
}
