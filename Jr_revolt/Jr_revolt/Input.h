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
	// コピー禁止
	Input(const Input&) = delete;
	Input& operator=(const Input&) = delete;

	Input();
	~Input();

	static void GetInstance();
	static void DeleteInstance();

	static void Update();
	// 押した瞬間
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
	// 押しているとき
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
	// 離した瞬間
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
	// 離しているとき
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