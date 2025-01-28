#pragma once

#include <vector>
#include <Input/InputParameter.h>

//�L�[�{�[�h���͗p�N���X
class InputKeyBoard
{
private:
	//���t���[���ɓ��͂��Ă�����
	static inline char currentKeyBuf_[KEYBOARD::KEY_BUF_LEN];

	//�O�t���[���ɓ��͂������
	static inline char preKeyBuf_[KEYBOARD::KEY_BUF_LEN];

public:
	InputKeyBoard() = delete;
	~InputKeyBoard() = delete;

	//������
	static void Init(void);

	//�s�������֐�
	static void Step(void);

	//���A�������ꂽ��
	static bool IsKeyPush(int keyCode);
	
	//�������ꑱ���Ă��邩
	static bool IsKeyKeep(int keyCode);
	
	//�������ꑱ�����{�^���������ꂽ��
	static bool IsKeyRelease(int keyCode);

	//�P���ɉ�����Ă��邩
	static bool IsKeyDown(int keyCode);

};
