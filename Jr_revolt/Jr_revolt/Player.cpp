#include <iostream>
#include <fstream>
#include <sstream>
#include <DxLib.h>
#include "Player.h"
#include "Input.h"
#include "Collision.h"
#include "MapManager.h"

Player::Player(float x, float y)
	: mImgNum(0)
	, mImgCount(0)
	, mPosX(x)
	, mPosY(y)
	, mSpeed(0.0f)
	, mVelocityX(0.0f)
	, mVelocityY(0.0f)
	, mJumpFlag(false)
	, mAttackFlag(false)
	, mPlayerVecFlag(true)
	, mDamageFlag(false)
{
	std::ifstream ifs("data/txt/PlayerName.txt");     // �t�@�C���ǂݎ���p�X�g���[��
	std::getline(ifs, mPlayerName);

	// ��������g�����ǂݍ���
	const char job[] = "soldier";
	for (int i = 0; i < 8; i++)
	{
		std::stringstream fname;
		fname << "data/Player/" << job << i << ".png";
		mPlayerImg[i] = LoadGraph(fname.str().c_str());
	}
	const char chara[] = "soldier_attck";
	for (int i = 0; i < 6; i++)
	{
		std::stringstream fname;
		fname << "data/Player/" << chara << i << ".png";
		mPlayerAttackImg[i] = LoadGraph(fname.str().c_str());
	}
}

Player::~Player()
{
}

void Player::Update()
{
	// �v���C���[�̈ړ�����(�W�����v���E�U�����E��e���͈ړ�����t�Ȃ�)
	if (mJumpFlag && !mAttackFlag && !mDamageFlag)
	{
		if (Input::IsPressed(LEFT))
		{
			mSpeed = -1.5f;
			mPlayerVecFlag = false;
		}
		if (Input::IsPressed(RIGHT))
		{
			mSpeed = 1.5f;
			mPlayerVecFlag = true;
		}
		if (Input::NoPressed(LEFT) && Input::NoPressed(RIGHT))
		{
			mSpeed = 0;
		}
	}
	mPosX += mSpeed;
	if (mJumpFlag) { mDamageFlag = false; mVelocityX = 0.0f; }

	// �v���C���[�ƓG���������Ă��邩�ǂ����̎擾
	if(!mDamageFlag){ mDamageFlag = Collision::GetPlayerDamageFlag(); }
	if (mDamageFlag && mJumpFlag)
	{
		if (Collision::GetHitEnemyPosX() < mPosX) { mVelocityX = 5.5; }
		else { mVelocityX = -5.5f; }
		mSpeed = 0;
		mVelocityY = -4.0f;
		mJumpFlag = false;
	}

	// �n�ʂɂ��Ă���Ƃ��W�����v��L���ɂ���
	if (Input::IsPressed(SPACE) && mJumpFlag)
	{
		mPosY -= 8.0f;
		mVelocityY = -5.5f;
		mJumpFlag = false;
	}
	// �󒆂ɂ���Ƃ�
	if (!mJumpFlag)
	{
		if (mDamageFlag)
		{
			if (Collision::GetHitEnemyPosX() < mPosX) { mVelocityX -= 0.1f; if (mVelocityX < 0) { mVelocityX = 0.0f; } }
			else { mVelocityX += 0.1f; if (mVelocityX > 0) { mVelocityX = 0.0f; } }
		}
		mVelocityY += 0.1f;
		mPosX += mVelocityX;
		mPosY += mVelocityY;
		if (mVelocityY > 6.0f)
		{
			mVelocityY = 6.0f;
		}
	}

	// �v���C���[��V���������Ƃ��U���t���O��true�ɂ���
	if (Input::IsPress(V) && !mAttackFlag)
	{
		mAttackFlag = true;
		mImgNum = 0;
		mImgCount = 0;
	}
	if (mAttackFlag && mJumpFlag) { mSpeed = 0; }
	//�@�v���C���[���U�����Ă��邩���Ă��Ȃ������Z�b�g
	Collision::PlayerAttackFlag(mAttackFlag);

	// �v���C���[�̉摜���񂷏���
	if (!mAttackFlag)
	{
		if (Input::IsPressed(LEFT) || Input::IsPressed(RIGHT))
		{
			if (mImgCount < 0)
			{
				mImgCount = 0;
			}
			if (mImgCount > 20)
			{
				mImgNum++;
				mImgCount = 0;
				if (mImgNum > 7)
				{
					mImgNum = 1;
				}
			}
			mImgCount++;
		}
		else
		{
			if (mImgCount < 0)
			{
				mImgNum = 0;
			}
			mImgCount--;
		}
	}
	else
	{
		if (mImgCount > 20)
		{
			mImgNum++;
			mImgCount = 0;
			if (mImgNum > 5)
			{
				mImgNum = 0;
				mAttackFlag = false;
			}
		}
		mImgCount++;
		if (mImgNum == 3)
		{
			Collision::PlayerAttackFlag(true);
		}
		else
		{
			Collision::PlayerAttackFlag(false);
		}
	}

	Collision::PlayerUpdate(mPosX, mPosY);
}

void Player::Draw()
{
	// �v���C���[���U�������ǂ���
	if (!mAttackFlag)
	{
		// �v���C���[�̉摜�������]���邩���Ȃ���
		if (mPlayerVecFlag)
		{
			DrawGraphF(mPosX, mPosY, mPlayerImg[mImgNum], TRUE);
		}
		else
		{
			DrawTurnGraphF(mPosX, mPosY, mPlayerImg[mImgNum], TRUE);
		}
	}
	else
	{
		// �v���C���[�̉摜�������]���邩���Ȃ���
		if (mPlayerVecFlag)
		{
			DrawGraphF(mPosX -30.0f, mPosY, mPlayerAttackImg[mImgNum], TRUE);
		}
		else
		{
			DrawTurnGraphF(mPosX -30.0f, mPosY, mPlayerAttackImg[mImgNum], TRUE);
		}
	}
}
