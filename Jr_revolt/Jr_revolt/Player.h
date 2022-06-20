#pragma once

class Player
{
public:
	Player(float x, int y);
	~Player();

	void Update();
	void Draw();

	// セッター
	void SetPosX(const float& _x) { mPosX = _x; }
	void SetJumpFlag(const bool& _flag) { mJampFlag = _flag; }

	// ゲッター
	const float& GetPosX() const { return mPosX; }
	const int& GetPosY() const { return mPosY; }
private:
	int mPlayerImg[8];
	int mPlayerAttackImg[6];
	int mImgNum;
	int mImgCount;
	int mPosY;

	float mPosX;
	float mSpeed;
	float mVelocity;

	bool mJampFlag;
	bool mAttackFlag;
	bool mPlayerVecFlag;
};