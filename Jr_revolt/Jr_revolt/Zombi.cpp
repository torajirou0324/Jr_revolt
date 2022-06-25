#include "Zombi.h"
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
	if (mVecFlag)
	{
		mPosX--;
	}
	else
	{
		mPosX++;
	}
	if (Collision::GetMapMoveFlag)
	{
		mPosX = mPosX + Collision::GetMapX();
	}
	if (mPosX < Collision::GetMapX())
	{
		mVecFlag = false;
	}
	if (mPosX > 3840 + Collision::GetMapX3())
	{
		mVecFlag = true;
	}
	// �n�ʂɂ��Ă���Ƃ��W�����v��L���ɂ���
	if (mFallFlag)
	{
		mVelocity = -5.5f;
	}
	// �󒆂ɂ���Ƃ�
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
