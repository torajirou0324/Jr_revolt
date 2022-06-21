#include <DxLib.h>
#include "SceneManager.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	// 画面モードの設定
	SetGraphMode(1920, 1080, 16, 60);
	ChangeWindowMode(TRUE);

	// DxLib初期化処理
	if (DxLib_Init() == -1)return -1;

	// グラフィックの描画先を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);

	SceneManager* SMG = new SceneManager;

	delete SMG;

	return 0;
}