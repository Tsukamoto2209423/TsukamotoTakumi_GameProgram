#include "InputKeyBoard.h"
#include <DxLib.h>

//�������֐�
void InputKeyBoard::Init(void)
{
	//�擪�A�h���X�擾
	char* currentKey = currentKeyBuf_;
	char* preKey = preKeyBuf_;
	
	//������
	for (int index = 0; index < KEYBOARD::KEY_BUF_LEN; ++index,++currentKey,++preKey)
	{
		*currentKey = '\0';
		*preKey = '\0';
	}
}

//���͏���
void InputKeyBoard::Step(void)
{
	//�z��̐擪�A�h���X�擾
	char* currentKey = currentKeyBuf_;
	char* preKey = preKeyBuf_;

	//�O�t���[���ɓ��͂��������i�[
	for (int index = 0; index < KEYBOARD::KEY_BUF_LEN; ++index, ++preKey, ++currentKey)
	{
		*preKey = *currentKey;
	}

	//���t���[���ŉ�����Ă�������i�[
	GetHitKeyStateAll(currentKeyBuf_);
}

//���A�������ꂽ��
bool InputKeyBoard::IsKeyPush(int keyCode)
{
	//�O�t���[���ŉ�����Ă��Ȃ� ���� ���t���[���ŉ�����Ă���Ȃ�^�A������Ă��Ȃ��Ȃ�U
	return !preKeyBuf_[keyCode] && currentKeyBuf_[keyCode];
}

//�������ꑱ���Ă��邩
bool InputKeyBoard::IsKeyKeep(int keyCode)
{
	//�O�t���[���ŉ�����Ă��� ���� ���t���[���ŉ�����Ă���Ȃ�^�A������Ă��Ȃ��Ȃ�U
	return preKeyBuf_[keyCode] && currentKeyBuf_[keyCode];
}

//�������ꑱ�����{�^���������ꂽ��
bool InputKeyBoard::IsKeyRelease(int keyCode)
{
	//�O�t���[���ŉ�����Ă��� ���� ���t���[���ŉ�����Ă��Ȃ��Ȃ�^�A������Ă���Ȃ�U
	return preKeyBuf_[keyCode] && !currentKeyBuf_[keyCode];
}

//�P���ɉ�����Ă��邩
bool InputKeyBoard::IsKeyDown(int keyCode)
{
	//���t���[���ŉ�����Ă��邩(�O�t���[���̏�Ԃ͊֌W�Ȃ�)
	return currentKeyBuf_[keyCode];
}
