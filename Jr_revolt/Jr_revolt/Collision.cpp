#include "Collision.h"

Collision* Collision::AABB = nullptr;

Collision::Collision()
{
	mPlayerX = 0.0f;
	mPlayerY = 0.0f;
	mEnemyX = 0.0f;
	mPlayerAttackFlag = false;
	mPlayerDamageFlag = false;
	mPlayerHitVecFlag = false;
	mEnemyDamageFlag = false;
	mMapMoveLeftFlag = false;
	mMapMoveRightFlag = false;
}

Collision::~Collision()
{
}
