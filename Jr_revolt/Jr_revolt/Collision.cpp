#include "Collision.h"

Collision* Collision::AABB = nullptr;

Collision::Collision()
{
	mPlayerX = 0;
	mPlayerY = 0;
	mPlayerAttackFlag = false;
	mPlayerDamageFlag = false;
	mEnemyDamageFlag = false;
}

Collision::~Collision()
{
}
