#pragma once

enum class TAG_SCENE
{
	TAG_TITLE,
	TAG_PLAY,
	TAG_CLEAR,
	TAG_OVER,
	TAG_ESCAPE,
	TAG_NONE
};

class SceneBase
{
public:
	SceneBase() {};
	~SceneBase() {};

	virtual TAG_SCENE Update() = 0;
	virtual void Draw() = 0;
};