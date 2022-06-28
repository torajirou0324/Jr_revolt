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
	mMapMoveLeftFlag = false;
	mMapMoveRightFlag = false;
}

Collision::~Collision()
{
}
