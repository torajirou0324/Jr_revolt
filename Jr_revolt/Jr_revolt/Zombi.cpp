#include "Zombi.h"
#include "Collision.h"

Zombi::Zombi(int posX, int posY)
{
	mPosX = posX;
	mPosY = posY;
	mImgNum = 0;
	mCount = 0;
	mMapPosX = 0;
	mVelocity = 0.0f;
	mFallFlag = true;
	mVecFlag = true;
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
				mPosX += 10;
			}
			else
			{
				mPosX -= 10;
			}
			mVelocity = -3.5f;
			mFallFlag = false;
		}
	}
	else
	{
		if (Collision::GetMapMoveLeftFlag())
		{
			if (mVecFlag)
			{
				mPosX -= 1.5;
			}
			else
			{
				mPosX += 1.5;
			}
		}
		else if (Collision::GetMapMoveRightFlag())
		{
			if (mVecFlag)
			{

			}
			else
			{

			}
		}
		else if (mVecFlag)
		{
			mPosX--;
		}
		else
		{
			mPosX++;
		}
	}
	if (mPosX < mMapPosX)
	{
		mPosX = mMapPosX;
		mVecFlag = false;
	}
	if (mPosX > mMapPosX + 3760)
	{
		mPosX = mMapPosX + 3760;
		mVecFlag = true;
	}
	// 地面についているときジャンプを有効にする
	if (mFallFlag)
	{
		mVelocity = -5.5f;
	}
	// 空中にいるとき
	if (!mFallFlag)
	{
		mVelocity += 0.1f;
		mPosY += mVelocity;
		if (mVelocity > 6.0f)
		{
			mVelocity = 6.0f;
		}
	}
}
