#pragma once

class Input
{
	static Input* input;
	struct key
	{
		char keyCode;
		int pressCount;
	};

	static void Update();
};