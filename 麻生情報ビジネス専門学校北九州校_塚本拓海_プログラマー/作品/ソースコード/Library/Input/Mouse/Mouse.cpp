#include "Mouse.h"

//�����������֐�
void InputMouse::Init(void)
{
	currentPosX_ = 0;
	currentPosY_ = 0;
	prePosX_ = 0;
	prePosY_ = 0;
	isCurrentClick_ = false;
	isPreClick_ = false;
}

//�s�������֐�
void InputMouse::Step(void)
{
	//1�t���[���O�̏����L��
	isPreClick_ = isCurrentClick_;

	//1�t���[���O�̈ʒu�����L��
	prePosX_ = currentPosX_;
	prePosY_ = currentPosY_;

	//���݂̃t���[���ō��N���b�N����Ă��邩
	isCurrentClick_ = GetMouseInput() == MOUSE_INPUT_LEFT;

	//���݂̃}�E�X�̈ʒu���L��
	GetMousePoint(&currentPosX_, &currentPosY_);

}