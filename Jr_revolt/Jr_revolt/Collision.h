#pragma once

class Collision
{
	static Collision* AABB;
	int mPlayerX;
	int mPlayerY;
	int mMapX;
	int mMapX3;

	bool mPlayerAttackFlag;
	bool mPlayerDamageFlag;
	bool mEnemyDamageFlag;
	bool mMapMoveFlag;
public:
	// コピー禁止
	Collision(const Collision&) = delete;
	Collision& operator=(const Collision&) = delete;

	Collision();
	~Collision();

	static void GetInstance()
	{
		AABB = new Collision;
	}
	static void DeleteInstance()
	{
		if (AABB != nullptr)
		{
			delete AABB;
			AABB = nullptr;
		}
	}

	// セッター
	static void PlayerUpdate(const int& _playerX, const int& _playerY,const int& _mapX,const int& _mapY)
	{
		AABB->mPlayerX = _playerX;
		AABB->mPlayerY = _playerY;
	}
	static void MapUpdate(const int& _mapX, const int& _mapX3)
	{
		AABB->mMapX = _mapX;
		AABB->mMapX3 = _mapX3;
	}
	static void PlayerAttackFlag(const bool& _playerAttackFlag)
	{
		AABB->mPlayerAttackFlag = _playerAttackFlag;
	}
	static void MapMove(const bool& _flag)
	{
		AABB->mMapMoveFlag = _flag;
	}

	// ゲッター
	const static void PlayerCollision(const int& _enemyX, const int& _enemyY,const int& size_x,const int& size_y)
	{
		if (((_enemyX >= AABB->mPlayerX + 40 && _enemyX <= AABB->mPlayerX + 110) ||
			(AABB->mPlayerX + 40 >= _enemyX && AABB->mPlayerX + 40 <= _enemyX + size_x)) &&
			((_enemyY > AABB->mPlayerY && _enemyY < AABB->mPlayerY + 180) ||
				(AABB->mPlayerY > _enemyY && AABB->mPlayerY < _enemyY + size_y)))
		{
			AABB->mPlayerDamageFlag = true;
		}
		else
		{
			AABB->mPlayerDamageFlag = false;
		}
	}
	const static bool& EnemyCollision(const int& _enemyX, const int& _enemyY, const int& size_x, const int& size_y)
	{
		if (((_enemyX >= AABB->mPlayerX + 110 && _enemyX <= AABB->mPlayerX + 150) ||
			(AABB->mPlayerX + 110 >= _enemyX && AABB->mPlayerX + 110 <= _enemyX + size_x)) &&
			((_enemyY > AABB->mPlayerY && _enemyY < AABB->mPlayerY + 180) ||
				(AABB->mPlayerY > _enemyY && AABB->mPlayerY < _enemyY + size_y)))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	const static int& GetPlayerX() { return AABB->mPlayerX; }
	const static int& GetPlayerY() { return AABB->mPlayerY; }
	const static int& GetMapX() { return AABB->mMapX; }
	const static int& GetMapX3() { return AABB->mMapX3; }
	const static bool& GetPlayerDamageFlag() { return AABB->mPlayerDamageFlag; }
	const static bool& GetAttackFlag() { return AABB->mPlayerAttackFlag; }
	const static bool& GetMapMoveFlag() { return AABB->mMapMoveFlag; }
};