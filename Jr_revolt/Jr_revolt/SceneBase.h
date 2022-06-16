#pragma once

enum class TAG_SCENE
{
	TAG_TITLE,
	TAG_PLAY,
	TAG_NONE
};

class SceneBase
{
public:
	SceneBase() {};
	virtual ~SceneBase() = 0;

	virtual TAG_SCENE Update() = 0;
	virtual void Draw() = 0;
};