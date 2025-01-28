#pragma once

#include <vector>
#include "DxLib.h"
#include "Vector/Vector3D.h"


//�Q�[���p�b�h���͗p�N���X
class InputGamePad
{
private:
	//���݂̃t���[���̓��͏��i�[�p�ϐ�
	static inline XINPUT_STATE currentKeyBuf_;

	//�O�t���[���̓��͏��i�[�p�ϐ�
	static inline XINPUT_STATE preKeyBuf_;

public:
	//�R���X�g���N�^
	InputGamePad() = delete;

	//�f�X�g���N�^
	~InputGamePad() = delete;

	//�������֐�
	static void Init(void);

	//���͏����֐�
	static void Step(void);

	//���X�e�B�b�N�̌X�����x�N�g���ɂ��Ď擾
	static Vector3D GetLStickVector(void);

	//�E�X�e�B�b�N�̌X�����x�N�g���ɂ��Ď擾
	static Vector3D GetRStickVector(void);

	//���A�������ꂽ��
	static bool IsKeyPush(int keyCode);
	//�������ꑱ���Ă��邩
	static bool IsKeyKeep(int keyCode);
	//�������ꑱ�����{�^���������ꂽ��
	static bool IsKeyRelease(int keyCode);

	//�P���ɉ�����Ă��邩
	static bool IsKeyDown(int keyCode);

};
