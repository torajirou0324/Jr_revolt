#include <iostream>
#include <fstream>
#include <sstream>
#include <DxLib.h>
#include "Player.h"
#include "Input.h"
#include "Collision.h"

Player::Player(float x, float y)
	: mImgNum(0)
	, mImgCount(0)
	, mPosX(x)
	, mPosY(y)
	, mSpeed(0.0f)
	, mVelocity(0.0f)
	, mJampFlag(true)
	, mAttackFlag(false)
	, mPlayerVecFlag(true)
	, mDamageFlag(false)
{
	std::ifstream ifs("data/txt/PlayerName.txt");     // ファイル読み取り専用ストリーム
	std::getline(ifs, mPlayerName);

	// 文字列を使った読み込み
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
	// プレイヤーの移動処理(ジャンプ中・攻撃中・被弾中は移動を受付ない)
	if (mJampFlag && !mAttackFlag && !mDamageFlag)
	{
		if (Input::IsPressed(LEFT))
		{
			mSpeed = -1.8f;
			mPlayerVecFlag = false;
		}
		if (Input::IsPressed(RIGHT))
		{
			mSpeed = 1.8f;
			mPlayerVecFlag = true;
		}
		if (Input::NoPressed(LEFT) && Input::NoPressed(RIGHT))
		{
			mSpeed = 0;
		}
	}
	mPosX += mSpeed;
	//if (mPosX < 0) { mPosX = 0.0f; }
	//if (mPosX > 1770) { mPosX = 1770.0f; }

	// プレイヤーと敵が当たっているかどうかの取得
	mDamageFlag = Collision::GetPlayerDamageFlag();

	// 地面についているときジャンプを有効にする
	if (Input::IsPressed(SPACE) && mJampFlag)
	{
		mVelocity = -5.5f;
		mJampFlag = false;
	}
	// 空中にいるとき
	if (!mJampFlag)
	{
		mVelocity += 0.1f;
		mPosY += mVelocity;
		if (mVelocity > 6.0f)
		{
			mVelocity = 6.0f;
		}
	}

	// プレイヤーがVを押したとき攻撃フラグをtrueにする
	if (Input::IsPress(V) && !mAttackFlag)
	{
		mAttackFlag = true;
		mImgNum = 0;
		mImgCount = 0;
	}
	if (mAttackFlag && mJampFlag) { mSpeed = 0; }
	//　プレイヤーが攻撃しているかしていないかをセット
	Collision::PlayerAttackFlag(mAttackFlag);

	// プレイヤーの画像を回す処理
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
	// プレイヤーが攻撃中かどうか
	if (!mAttackFlag)
	{
		// プレイヤーの画像向き反転するかしないか
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
		// プレイヤーの画像向き反転するかしないか
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
