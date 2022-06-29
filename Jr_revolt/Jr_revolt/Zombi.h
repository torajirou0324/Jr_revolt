#pragma once

class Zombi
{
public:
	Zombi(int posX, int posY);
	~Zombi();

	void Update();

	// �Z�b�^�[
	void SetFallFlag(const bool& _flag) { mFallFlag = _flag; }
	// �Q�b�^�[
	const int& GetImgNum() const { return mImgNum; }
	const float& GetPosX() const { return mPosX; }
	const float& GetPosY() const { return mPosY; }
	const bool& GetVecFlag()const { return mVecFlag; }
	const bool& GetAttackFlag()const { return mAttackFlag; }
	const bool& GetMoveFlag()const { return mMoveFlag; }
private:

	int mImgNum;
	int mCount;

	float mPosY;
	float mPosX;
	float mVelocity;

	bool mAttackFlag;
	bool mMoveFlag;
	bool mVecFlag;
	bool mFallFlag;
	bool mDamageFlag;
};