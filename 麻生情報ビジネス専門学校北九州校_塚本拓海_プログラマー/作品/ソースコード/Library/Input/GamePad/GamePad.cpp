#include "GamePad.h"
#include "Math/MyMath.h"
#include <Input/InputParameter.h>

//�������֐�
void InputGamePad::Init(void)
{
	//������
	currentKeyBuf_ = { 0 };
	preKeyBuf_ = { 0 };

	//STICK_ERROR_NUM�ȉ��̒l�͎󂯎��Ȃ��悤�ɂ���
	SetJoypadDeadZone(DX_INPUT_PAD1, GAME_PAD::STICK_ERROR_NUM);
}

//���͏����֐�
void InputGamePad::Step(void)
{
	//�z��̐擪�A�h���X���擾
	unsigned char* preKeyButton = preKeyBuf_.Buttons;
	unsigned char* currentKeyButton = currentKeyBuf_.Buttons;

	//�O�t���[���ɓ��͂��������i�[
	for (int index = 0; index < GAME_PAD::BUTTON_MAX_NUM; ++index, ++preKeyButton, ++currentKeyButton)
	{
		*preKeyButton = *currentKeyButton;
	}

	//���t���[���ŉ�����Ă�������i�[
	GetJoypadXInputState(DX_INPUT_PAD1, &currentKeyBuf_);

}

//���X�e�B�b�N�̒l�擾
Vector3D InputGamePad::GetLStickVector(void)
{
	//(X��,Y��,Z��)�̏��ō��X�e�B�b�N�̌X���̊������v�Z
	const Vector3D vec(currentKeyBuf_.ThumbLX * GAME_PAD::STICK_PERCENT,
		0.0f,
		currentKeyBuf_.ThumbLY * GAME_PAD::STICK_PERCENT);

	//���͒l���덷�͈͓̔��Ȃ�[���x�N�g����Ԃ�
	if (GAME_PAD::STICK_ERROR_NUM >= MyMath::Abs(vec.x) && GAME_PAD::STICK_ERROR_NUM >= MyMath::Abs(vec.z))
	{
		return MyMath::ZERO_VECTOR_3D;
	}

	//���͂��ꂽ�Ȃ�A���̒l��Ԃ�
	return vec;
}

//�E�X�e�B�b�N�̒l�擾
Vector3D InputGamePad::GetRStickVector(void)
{
	//(X��,Y��,Z��)�̏��ō��X�e�B�b�N�̌X���̊������v�Z
	const Vector3D vec(-currentKeyBuf_.ThumbRY * GAME_PAD::STICK_PERCENT,
		currentKeyBuf_.ThumbRX * GAME_PAD::STICK_PERCENT,
		0.0f);

	//���͒l���덷�͈͓̔��Ȃ�[���x�N�g����Ԃ�
	if (GAME_PAD::STICK_ERROR_NUM >= MyMath::Abs(vec.x) && GAME_PAD::STICK_ERROR_NUM >= MyMath::Abs(vec.y))
	{
		return MyMath::ZERO_VECTOR_3D;
	}

	//���͂��ꂽ�Ȃ�A���̒l��Ԃ�
	return vec;
}

//���A�������ꂽ��
bool InputGamePad::IsKeyPush(int keyCode)
{
	//�O�t���[���ŉ�����Ă��Ȃ� ���� ���t���[���ŉ�����Ă���Ȃ�^�A������Ă��Ȃ��Ȃ�U
	return preKeyBuf_.Buttons[keyCode] == 0 && currentKeyBuf_.Buttons[keyCode] == 1;
}

//�������ꑱ���Ă��邩
bool InputGamePad::IsKeyKeep(int keyCode)
{
	//�O�t���[���ŉ�����Ă��� ���� ���t���[���ŉ�����Ă���Ȃ�^�A������Ă��Ȃ��Ȃ�U
	return preKeyBuf_.Buttons[keyCode] == 1 && currentKeyBuf_.Buttons[keyCode] == 1;
}

//�������ꑱ�����{�^���������ꂽ��
bool InputGamePad::IsKeyRelease(int keyCode)
{
	//�O�t���[���ŉ�����Ă��� ���� ���t���[���ŉ�����Ă��Ȃ��Ȃ�^�A������Ă���Ȃ�U
	return preKeyBuf_.Buttons[keyCode] == 1 && currentKeyBuf_.Buttons[keyCode] == 0;
}

//�P���ɉ�����Ă��邩
bool InputGamePad::IsKeyDown(int keyCode)
{
	//���t���[���ŉ�����Ă��邩(�O�t���[���̏�Ԃ͊֌W�Ȃ�)
	return currentKeyBuf_.Buttons[keyCode] == 1;
}
