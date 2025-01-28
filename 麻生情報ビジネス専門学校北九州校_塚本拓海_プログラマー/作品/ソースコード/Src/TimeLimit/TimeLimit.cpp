#include "TimeLimit.h"
#include "TimeLimitParameter.h"
#include <DxLib.h>
#include <NumberGraph/Number.h>
#include <FrameRate/FrameRate.h>
#include <Common.h>

namespace BOUDAMA
{
	//�R���X�g���N�^
	TimeLimit::TimeLimit()
	{
		count_ = TIME_LIMIT::INIT_TIME;
		characterHandle_ = -1;
		infinityHandle_ = -1;
		isEndless_ = false;
	}

	//�f�X�g���N�^
	TimeLimit::~TimeLimit()
	{

	}

	//������
	void TimeLimit::Init(void)
	{
		// �v���J�n���Ԃ��擾
		start_ = system_clock::now();
		count_ = TIME_LIMIT::INIT_TIME;
		characterHandle_ = -1;
	}

	void TimeLimit::Load(void)
	{
		//�G���h���X�Ȃ�
		if (isEndless_)
		{
			//�u���v�̉摜�ǂݍ���
			infinityHandle_ = LoadGraph(TIME_LIMIT::INFINITY_PATH);
		}

		characterHandle_ = LoadGraph(TIME_LIMIT::CHARA_PATH);
	}

	void TimeLimit::Step(void)
	{
		//�G���h���X�̏ꍇ�͏������Ȃ�
		if (isEndless_)
		{
			return;
		}

		//�f�o�b�O���͏�ɗ��z���Ԃ�Ԃ�
#ifdef _DEBUG
		count_ -= FRAMERATE::FRAME_TIME;

#else

	//���݂̎��Ԏ擾
		end_ = system_clock::now();

		//�~���b�Ōo�ߎ��ԕ��A���Ԃ����炷
		count_ -= static_cast<int>(duration_cast<std::chrono::milliseconds>(end_ - start_).count());

		//���݂̎��Ԃ�O�̎��Ԃɕۑ�
		start_ = end_;

#endif // _DEBUG

	}

	// �`�揈��
	void TimeLimit::Draw(void)
	{
		//�u�̂���v��`��
		DrawRotaGraph(TIME_LIMIT::CHARA_POS_X, TIME_LIMIT::CHARA_POS_Y, 0.5f, 0.0f, characterHandle_, true);

		//�G���h���X�Ȃ�
		if (isEndless_)
		{
			//�u���v��`��
			DrawRotaGraph(TIME_LIMIT::INFINITY_POS_X, TIME_LIMIT::INFINITY_POS_Y, 1.0f, 0.0f, infinityHandle_, true);

			//�������^�[������
			return;
		}

		//�����_���ʂ܂ŕ`�悷�邽�߂�count_�̓~���b�Ȃ̂�0.01�{����
		NumberGraph::Draw(static_cast<int>(count_ * 0.01f), TIME_LIMIT::INIT_NUM_POS_X, TIME_LIMIT::INIT_NUM_POS_Y);

		//�R���}�`��
		DrawRotaGraph(TIME_LIMIT::COMMA_POS_X, TIME_LIMIT::COMMA_POS_Y, 0.25f, 0.0f, NumberGraph::GetGraphHandle(0), true);

		//10�b�����Ȃ�^�񒆂ɓ����Ȑ������`��
		if (count_ < 10000)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 32);
			DrawRotaGraph(Common::WINDOW_WIDTH_HALF, Common::WINDOW_HEIGHT_HALF, 7.0f, 0.0f, NumberGraph::GetGraphHandle(static_cast<int>(count_ * 0.001f)), true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}

		//1�b�����Ȃ�u0.�v���`��
		if (count_ < 1000)
		{
			DrawRotaGraph(TIME_LIMIT::INIT_NUM_POS_X - TIME_LIMIT::NUM_POS_INTERVAL, TIME_LIMIT::INIT_NUM_POS_Y, 0.75f, 0.0f, NumberGraph::GetGraphHandle(0), true);
		}
	}

	//�j������
	void TimeLimit::Fin(void)
	{
		//�u�̂���v�̉摜�`��p�n���h�����폜
		DeleteGraph(characterHandle_);
	}
}
