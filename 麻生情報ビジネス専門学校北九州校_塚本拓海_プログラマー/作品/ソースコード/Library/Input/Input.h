#pragma once

#include <vector>

//���͓���Ǘ��p�N���X
class Input
{
private:
	//�L�[�{�[�h����
	static inline std::vector<int> key_;

	//�Q�[���p�b�h����
	static inline std::vector<int> button_;

public:
	//���ꏉ�����֐�
	static void Init(void);

	//������͏����֐�
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