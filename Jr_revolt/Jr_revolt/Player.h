#pragma once
#include <string>

class Player
{
public:
	Player(float x, float y);
	~Player();

	void Update();
	void Draw();

	// セッター
	void SetPosX(const float& _x) { mPosX = _x; }
	void SetPosY(const float& _y) { mPosY = _y; }
	void SetJumpFlag(const bool& _flag) { mJumpFlag = _flag; }

	// ゲッター
	const std::string& GetPlayerName() const { return mPlayerName; }
	const float& GetPosX() const { return mPosX; }
	const float& GetPosY() const { return mPosY; }
	const float& GetSpeed() const { return mSpeed; }
private:
	std::string mPlayerName;

	int mPlayerImg[8];
	int mPlayerAttackImg[6];
	int mImgNum;
	int mImgCount;

	float mPosX;
	float mPosY;
	float mSpeed;
	float mVelocityX;
	float mVelocityY;

	bool mJumpFlag;
	bool mAttackFlag;
	bool mPlayerVecFlag;
	bool mDamageFlag;
};