#pragma once
#include <vector>

enum EnemyName
{
	ZOMBI,
	COBOLT,
	KNIGHT
};

class ZombiManager;

class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();

	void Update();
	void Draw();
private:
	ZombiManager* m_pZombi;
};