#pragma once
#pragma warning(disable:26812)
#include <vector>

enum TYPE
{
	ENTER,
	ESCAPE,
	//UP,
	LEFT,
	RIGHT,
	SPACE,
	V,
	END
};

class Input
{
	static Input* input;
	struct key
	{
		int pressCount;
	};
	std::vector<key> keynum;
public:
	// �R�s�[�֎~
	Input(const Input&) = delete;
	Input& operator=(const Input&) = delete;

	Input();
	~Input();

	static void GetInstance();
	static void DeleteInstance();

	static void Update();
	// �������u��
	static bool IsPress(TYPE t) 
	{ 
		if (input->keynum[t].pressCount == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	// �����Ă���Ƃ�
	static bool IsPressed(TYPE t)
	{
		if (input->keynum[t].pressCount > 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	// �������u��
	static bool NoPress(TYPE t)
	{
		if (input->keynum[t].pressCount == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	// �����Ă���Ƃ�
	static bool NoPressed(TYPE t)
	{
		if (input->keynum[t].pressCount < 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};