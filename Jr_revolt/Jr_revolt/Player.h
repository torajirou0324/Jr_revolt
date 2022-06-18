#pragma once

class Player
{
public:
	Player(int x, int y);
	~Player();

	void Update();
	void Draw();

	// �Z�b�^�[
	void SetPosX(const int& _x) { mPosX = _x; }
	void SetJumpFlag(const bool& _flag) { mJampFlag = _flag; }

	// �Q�b�^�[
	const int& GetPosX() const { return mPosX; }
	const int& GetPosY() const { return mPosY; }
private:
	int mPlayerImg[8];
	int mPlayerAttackImg[6];
	int mImgNum;
	int mImgCount;
	int mPosX;
	int mPosY;
	int mSpeed;

	float mVelocity;

	bool mJampFlag;
	bool mAttackFlag;
	bool mPlayerVecFlag;
};