/*
	�������r�W�l�X���w�Z �k��B�Z
	�w�Дԍ��F2209423
	�����F�˖{��C
	�v���O���}�[
*/

#include "Game/GameSystem.h"

//���C���֐�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���̋N��
	BOUDAMA::GameSystem::Start();

	//�Q�[���̃��[�v
	BOUDAMA::GameSystem::MainLoop();

	//�Q�[���̏I��
	BOUDAMA::GameSystem::Fin();

	//�v���O�����̏I��
	return 0;

}//WinMain�֐��I��芇��
