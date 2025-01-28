#include "Input.h"
#include "KeyBoard/InputKeyBoard.h"
#include "GamePad/GamePad.h"
#include "InputParameter.h"
#include "Mouse/Mouse.h"

//�������֐�
void Input::Init(void)
{
	InputKeyBoard::Init();
	InputGamePad::Init();
	InputMouse::Init();

	//���ꂼ��̓��͏��ǉ�
	key_.emplace_back(KEY_INPUT_ESCAPE);
	key_.emplace_back(KEY_INPUT_RETURN);
	key_.emplace_back(KEY_INPUT_BACK);
	key_.emplace_back(KEY_INPUT_UP);
	key_.emplace_back(KEY_INPUT_DOWN);
	key_.emplace_back(KEY_INPUT_LEFT);
	key_.emplace_back(KEY_INPUT_RIGHT);
	key_.emplace_back(KEY_INPUT_SPACE);
	key_.emplace_back(KEY_INPUT_LSHIFT);

	
	button_.emplace_back(XINPUT_BUTTON_BACK);
	button_.emplace_back(XINPUT_BUTTON_B);
	button_.emplace_back(XINPUT_BUTTON_A);
	button_.emplace_back(XINPUT_BUTTON_DPAD_UP);
	button_.emplace_back(XINPUT_BUTTON_DPAD_DOWN);
	button_.emplace_back(XINPUT_BUTTON_DPAD_LEFT);
	button_.emplace_back(XINPUT_BUTTON_DPAD_RIGHT);
	button_.emplace_back(XINPUT_BUTTON_B);
	button_.emplace_back(XINPUT_BUTTON_Y);
}

//���͏����֐�
void Input::Step(void)
{
	//�L�[�{�[�h���͍X�V����
	InputKeyBoard::Step();

	//�Q�[���p�b�h���͍X�V����
	InputGamePad::Step();

	//�}�E�X���͍X�V����
	InputMouse::Step();

}

//���A�������ꂽ��
bool Input::IsKeyPush(int keyCode)
{
	return InputKeyBoard::IsKeyPush(key_[keyCode]) ||
		InputGamePad::IsKeyPush(button_[keyCode]);
}

//�������ꑱ���Ă��邩
bool Input::IsKeyKeep(int keyCode)
{
	//�O�t���[���ŉ�����Ă��� ���� ���t���[���ŉ�����Ă���Ȃ�^�A������Ă��Ȃ��Ȃ�U
	return InputKeyBoard::IsKeyKeep(key_[keyCode]) ||
		InputGamePad::IsKeyKeep(button_[keyCode]);
}

//�������ꑱ�����{�^���������ꂽ��
bool Input::IsKeyRelease(int keyCode)
{
	//�O�t���[���ŉ�����Ă��� ���� ���t���[���ŉ�����Ă��Ȃ��Ȃ�^�A������Ă���Ȃ�U
	return InputKeyBoard::IsKeyRelease(key_[keyCode]) ||
		InputGamePad::IsKeyRelease(button_[keyCode]);
}

//�P���ɉ�����Ă��邩
bool Input::IsKeyDown(int keyCode)
{
	//���t���[���ŉ�����Ă��邩(�O�t���[���̏�Ԃ͊֌W�Ȃ�)
	return InputKeyBoard::IsKeyDown(key_[keyCode]) ||
		InputGamePad::IsKeyDown(button_[keyCode]);
}
