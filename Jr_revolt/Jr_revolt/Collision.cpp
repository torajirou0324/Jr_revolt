#include "Collision.h"

Collision* Collision::AABB = nullptr;

Collision::Collision()
{
	mPlayerX = 0;
	mPlayerY = 0;
	mMapX = 0;
	mMapX3 = 0;
	mPlayerAttackFlag = false;
	mPlayerDamageFlag = false;
	mEnemyDamageFlag = false;
	mMapMoveFlag = false;
}

Collision::~Collision()
{
}
