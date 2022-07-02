#include "Zombi.h"
#include "MapManager.h"
#include "Collision.h"

Zombi::Zombi(int posX, int posY)
{
	state = IDLE;
	mPosX = posX;
	mPosY = posY;
	mImgNum = 0;
	mCount = 0;
	mVelocity = 0.0f;
	mFallFlag = true;
	mVecFlag = true;
	mMoveFlag = true;
	mAttackFlag = false;
	mDamageFlag = false;
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
			mVelocity = -5.5f;
			mFallFlag = false;
			mDamageFlag = true;
			state = IDLE;
		}
	}
	else if(mFallFlag)
	{
		mDamageFlag = false;
	}

	switch (state)
	{
	case Zombi::IDLE:
		Idle();
		break;
	case Zombi::MOVE:
		Move();
		break;
	case Zombi::ATTACK:
		Attack();
		break;
	default:
		break;
	}

	auto MapFrontX = MapManager::GetMapPosX();
	if (mPosX < MapFrontX)
	{
		mPosX = MapFrontX;
		mVecFlag = false;
	}
	MapFrontX = MapManager::GetMap3PosX();
	if (mPosX > MapFrontX + 1850.0f)
	{
		mPosX = MapFrontX + 1850.0f;
		mVecFlag = true;
	}
	mFallFlag = MapManager::CollisionManager(mPosX, mPosY);
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

void Zombi::StateManager()
{
	// ステート処理
	if (!mVecFlag)
	{
		if (mPosX + 90 + 90 > Collision::GetPlayerX() && mPosX + 90 < Collision::GetPlayerX())
		{
			state = ATTACK;
		}
		if (mPosX + 90 + 400 < Collision::GetPlayerX() && mPosX + 90 + 90 < Collision::GetPlayerX())
		{
			state = MOVE;
		}
		else if(mPosX < Collision::GetPlayerX())
		{
			state = IDLE;
		}
	}
	else
	{
		if (mPosX - 100 > Collision::GetPlayerX() && mPosX < Collision::GetPlayerX())
		{
			state = ATTACK;
		}
		if (mPosX - 400 < Collision::GetPlayerX() && mPosX - 100 > Collision::GetPlayerX())
		{
			state = MOVE;
		}
		else if(mPosX - 100 > Collision::GetPlayerX())
		{
			state = IDLE;
		}
	}
}

void Zombi::Idle()
{
	mCount++;
	if (mCount > 20)
	{
		mImgNum++;
		if (mImgNum > 2 && mMoveFlag)
		{
			mImgNum = 0;
		}
		mCount = 0;
	}
	mMoveFlag = false;
	mAttackFlag = false;
	StateManager();
}

void Zombi::Move()
{
	// ステート処理
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
	mMoveFlag = true;
	mAttackFlag = false;
	StateManager();
}

void Zombi::Attack()
{
	mCount++;
	if (mCount > 20)
	{
		mImgNum++;
		if (mImgNum > 3 && mMoveFlag)
		{
			mImgNum = 0;
		}
		mCount = 0;
	}
	mMoveFlag = false;
	mAttackFlag = true;
	StateManager();
}
