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

	// セッター
	void SetMapPosX(const float& _posX) { mMapPosX = _posX; }
private:
	ZombiManager* m_pZombi;

	float mMapPosX;
};