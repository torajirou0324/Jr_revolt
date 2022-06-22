#pragma once
#include <vector>

enum EnemyName
{
	ZOMBI,
	COBOLT,
	KNIGHT
};

class Enemy;

class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();

	void Update();
	void Draw();
private:
	Enemy* m_pEnemy;
};