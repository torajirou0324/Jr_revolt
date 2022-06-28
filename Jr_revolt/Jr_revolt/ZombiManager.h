#pragma once
#include <vector>
class Zombi;

class ZombiManager
{
public:
	ZombiManager();
	~ZombiManager();

	void Update();
	void Draw();

	// セッター
	void SetMapPosX(const float& _posX) { mMapPosX = _posX; }
private:
	std::vector<Zombi*> m_pZombi;
	int mZombiImg[3];
	int mZombiAttackImg[4];
	int mZombiMoveImg[6];
	float mMapPosX;
};