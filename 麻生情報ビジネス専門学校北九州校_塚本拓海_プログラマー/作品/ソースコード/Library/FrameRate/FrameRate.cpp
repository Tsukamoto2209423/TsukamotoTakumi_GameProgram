#include "FrameRate.h"
#include <DxLib.h>

//�������s����֐�
bool FrameRate::IsPassedFrameRateTime(void)
{
	//���݂̎��Ԃ��O��̃t���[�������
	//1000/60�~���b(1/60�b)�ȏ�o�߂��Ă����珈�������s����
	return (currentTime_ - lastFrameTime_ >= FRAMERATE::FRAME_TIME);
}

void FrameRate::Step(void)
{
	//���݂̎��Ԃ��擾
	currentTime_ = GetNowCount();

	//�ŏ��̃��[�v�Ȃ�
	//���݂̎��Ԃ��AFPS�v�Z���������Ԃɐݒ�
	if (calcFpsTime_ == 0.0f)
	{
		calcFpsTime_ = currentTime_;
		fps_ = static_cast<float>(FRAMERATE::FRAME_RATE);
	}
}

//FPS�v�Z�X�V�֐�
void FrameRate::Update(void)
{
	//�t���[�����s���̎��Ԃ��X�V
	lastFrameTime_ = currentTime_;

	//�t���[�������J�E���g
	++count_;
}

//FPS�v�Z
void FrameRate::CalcFPS()
{
	//�O���FPS���v�Z�������Ԃ���̌o�ߎ��Ԃ����߂�
	int difTime = currentTime_ - calcFpsTime_;

	//�O���FPS���v�Z�������Ԃ���
	//1�b�ȏ�o�߂��Ă�����FPS���v�Z����
	if (difTime > 1000)
	{
		//�t���[���񐔂��~���b�ɍ��킹��
		//�����܂ŏo�������̂�float�ɃL���X�g
		float frameCount = static_cast<float>(count_ * 1000.0f);

		//FPS�����߂�
		//���z�̐��l�� 60000 / 1000 �� 60 �ƂȂ�
		fps_ = frameCount / difTime;

		//�t���[�����[�g�J�E���g���N���A
		count_ = 0;

		//FPS���v�Z�������Ԃ��X�V
		calcFpsTime_ = currentTime_;
	}
}

//FPS�\�� (�f�o�b�N�p)
void FrameRate::DrawFPS()
{
	unsigned int color = GetColor(255, 0, 0);
	DrawFormatString(1175, 700, color, "FPS[%.2f]", fps_);
}
