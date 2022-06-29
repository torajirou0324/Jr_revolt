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

private:
	std::vector<Zombi*> m_pZombi;
	int mZombiImg[3];
	int mZombiAttackImg[4];
	int mZombiMoveImg[6];
};