#include <DxLib.h>
#include "SceneManager.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	// ��ʃ��[�h�̐ݒ�
	SetGraphMode(1920, 1080, 16, 60);
	ChangeWindowMode(TRUE);

	// DxLib����������
	if (DxLib_Init() == -1)return -1;

	// �O���t�B�b�N�̕`���𗠉�ʂɃZ�b�g
	SetDrawScreen(DX_SCREEN_BACK);

	SceneManager* SMG = new SceneManager;

	delete SMG;

	return 0;
}