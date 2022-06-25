#include "Input.h"
#include <DxLib.h>

Input* Input::input = nullptr;

Input::Input()
{
	key k;
	k.pressCount = 0;
	for (int i = 0; i < END; i++)
	{
		keynum.push_back(k);
	}
}

Input::~Input()
{
	keynum.clear();
}

void Input::GetInstance()
{
	if (input == nullptr)
	{
		input = new Input;
	}
}

void Input::DeleteInstance()
{
	if (input != nullptr) 
	{
		delete input;
		input = nullptr;
	}
}

void Input::Update()
{
	// Enter
	{
		if (CheckHitKey(KEY_INPUT_RETURN))
		{
			input->keynum[ENTER].pressCount = max(++input->keynum[ENTER].pressCount, 1);
		}
		else
		{
			input->keynum[ENTER].pressCount = min(--input->keynum[ENTER].pressCount, 0);
		}
	} 
	// ESCAPE
	{
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			input->keynum[ESCAPE].pressCount = max(++input->keynum[ESCAPE].pressCount, 1);
		}
		else
		{
			input->keynum[ESCAPE].pressCount = min(--input->keynum[ESCAPE].pressCount, 0);
		}
	}
	// UP
	//{
	//	if (CheckHitKey(KEY_INPUT_UP))
	//	{
	//		input->keynum[UP].pressCount = max(++input->keynum[ESCAPE].pressCount, 1);
	//	}
	//	else
	//	{
	//		input->keynum[UP].pressCount = min(--input->keynum[ESCAPE].pressCount, 0);
	//	}
	//}
	// LEFT
	{
		if (CheckHitKey(KEY_INPUT_LEFT))
		{
			input->keynum[LEFT].pressCount = max(++input->keynum[LEFT].pressCount, 1);
		}
		else
		{
			input->keynum[LEFT].pressCount = min(--input->keynum[LEFT].pressCount, 0);
		}
	}
	// RIGHT
	{
		if (CheckHitKey(KEY_INPUT_RIGHT))
		{
			input->keynum[RIGHT].pressCount = max(++input->keynum[RIGHT].pressCount, 1);
		}
		else
		{
			input->keynum[RIGHT].pressCount = min(--input->keynum[RIGHT].pressCount, 0);
		}
	}
	// SPACE
	{
		if (CheckHitKey(KEY_INPUT_SPACE))
		{
			input->keynum[SPACE].pressCount = max(++input->keynum[SPACE].pressCount, 1);
		}
		else
		{
			input->keynum[SPACE].pressCount = min(--input->keynum[SPACE].pressCount, 0);
		}
	}
	// V
	{
		if (CheckHitKey(KEY_INPUT_V))
		{
			input->keynum[V].pressCount = max(++input->keynum[V].pressCount, 1);
		}
		else
		{
			input->keynum[V].pressCount = min(--input->keynum[V].pressCount, 0);
		}
	}
}
