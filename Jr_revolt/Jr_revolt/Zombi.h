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
	const int& GetPosX() const { return mPosX; }
	const int& GetPosY() const { return mPosY; }
	const bool& GetVecFlag()const { return mVecFlag; }
	const bool& GetAttackFlag()const { return mAttackFlag; }
	const bool& GetMoveFlag()const { return mMoveFlag; }
private:
	int mPosX;
	int mPosY;
	int mImgNum;
	int mCount;

	float mVelocity;

	bool mAttackFlag;
	bool mMoveFlag;
	bool mVecFlag;
	bool mFallFlag;
};