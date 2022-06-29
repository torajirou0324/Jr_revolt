#include "Zombi.h"
#include "MapManager.h"
#include "Collision.h"

Zombi::Zombi(int posX, int posY)
{
	mPosX = posX;
	mPosY = posY;
	mImgNum = 0;
	mCount = 0;
	mVelocity = 0.0f;
	mFallFlag = true;
	mVecFlag = true;
	mMoveFlag = true;
	mAttackFlag = false;
}

Zombi::~Zombi()
{

}

void Zombi::Update()
{
	Collision::PlayerCollision(mPosX, mPosY, 90, 180);
	if (Collision::GetAttackFlag())
	{
		if (Collision::EnemyCollision(mPosX, mPosY, 90, 180))
		{
			if (Collision::GetPlayerX() < mPosX)
			{
				mPosX += 20.0f;
			}
			else
			{
				mPosX -= 20.0f;
			}
			mVelocity = -3.5f;
			mFallFlag = false;
		}
	}
	if (Collision::GetPlayerDamageFlag())
	{

	}
	else
	{
		if (Collision::GetMapMoveLeftFlag())
		{
			if (mVecFlag)
			{
				mPosX += 0.5f;
			}
			else
			{
				mPosX += 2.5f;
			}
		}
		if (Collision::GetMapMoveRightFlag())
		{
			if (mVecFlag)
			{
				mPosX -= 2.5f;
			}
			else
			{
				mPosX -= 0.5f;
			}
		}
		if (!Collision::GetMapMoveLeftFlag() && !Collision::GetMapMoveRightFlag())
		{
			if (mVecFlag)
			{
				mPosX--;
			}
			else
			{
				mPosX++;
			}
		}
	}

	auto MapFrontX = MapManager::GetMapPosX();
	if (mPosX < MapFrontX)
	{
		mPosX = MapFrontX;
		mVecFlag = false;
	}
	MapFrontX = MapManager::GetMap3PosX();
	if (mPosX > MapFrontX + 1920.0f)
	{
		mPosX = MapFrontX + 1920.0f;
		mVecFlag = true;
	}
	mFallFlag = MapManager::CollisionManager(mPosX, mPosY);
	// ‹ó’†‚É‚¢‚é‚Æ‚«
	if (!mFallFlag)
	{
		mVelocity += 0.1f;
		mPosY += mVelocity;
		if (mVelocity > 6.0f)
		{
			mVelocity = 6.0f;
		}
	}

	mCount++;
	if (mCount > 20)
	{
		mImgNum++;
		if (mImgNum > 5 && mMoveFlag)
		{
			mImgNum = 0;
		}
		mCount = 0;
	}
}
