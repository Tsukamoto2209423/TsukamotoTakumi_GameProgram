#include "Combo.h"
#include <DxLib.h>
#include <NumberGraph/Number.h>

namespace BOUDAMA
{
	//�R���X�g���N�^
	Combo::Combo()
	{
		charaHandle_ = -1;
		presiousCharaHandle_ = -1;
		comboNum_ = 0;
		countTime_ = 0;
		drawInterval_ = 0;
		graphScale_ = 0.0f;
	}

	//�f�X�g���N�^
	Combo::~Combo()
	{

	}

	//�����������֐�
	void Combo::Init(void)
	{
		charaHandle_ = -1;
		comboNum_ = 0;
		countTime_ = COMBO::MAX_COUNT_TIME;
		drawInterval_ = static_cast<int>(NUMBER_GRAPH::SIZE * COMBO::INIT_SCALE);
		graphScale_ = COMBO::INIT_SCALE;
	}

	//�ǂݍ��ݏ���
	void Combo::Load(void)
	{
		if (charaHandle_ == -1)
		{
			charaHandle_ = LoadGraph(COMBO::PATH);
			presiousCharaHandle_ = LoadGraph(COMBO::PRE_PATH);
		}
	}

	//�s�������֐�
	void Combo::Step(void)
	{
		//�R���{���Ȃ�
		if (comboNum_ > 0)
		{
			//���Ԃ����炷
			--countTime_;
		}

		//0�ɂȂ�����
		if (countTime_ <= 0)
		{
			//������
			comboNum_ = 0;
			countTime_ = COMBO::MAX_COUNT_TIME;
		}


		//������x�R���{������摜��傫������
		if (COMBO::ADD_SCALE_COMBO_NUM <= comboNum_)
		{
			graphScale_ = COMBO::BIG_SCALE;
			//�摜��傫�������̂ŊԊu��傫������
			drawInterval_ = static_cast<int>(NUMBER_GRAPH::SIZE * graphScale_);
		}
		//�R���{���Ă��Ȃ��ꍇ�͒ʏ�̑傫��
		else
		{
			graphScale_ = COMBO::INIT_SCALE;
			drawInterval_ = static_cast<int>(NUMBER_GRAPH::SIZE * graphScale_);
		}

	}

	//�`�揈���֐�
	void Combo::Draw(void)
	{
		//�R���{���������Ă��Ȃ��Ȃ�`�悵�Ȃ�
		if (comboNum_ > 0)
		{
			NumberGraph::Draw(comboNum_, COMBO::INIT_POS_X, COMBO::INIT_POS_Y, drawInterval_, graphScale_);

			//�R���{���ɉ����ĕ`�悷�镶�������߂�
			comboNum_ >= 20 ?
				DrawRotaGraph(COMBO::INIT_POS_X + 100, COMBO::INIT_POS_Y, graphScale_, 0.0f, presiousCharaHandle_, true)
				: DrawRotaGraph(COMBO::INIT_POS_X + 100, COMBO::INIT_POS_Y, graphScale_, 0.0f, charaHandle_, true);
		}
	}

	//�j�������֐�
	void Combo::Fin(void)
	{
		DeleteGraph(charaHandle_);
		DeleteGraph(presiousCharaHandle_);

		comboNum_ = 0;
		countTime_ = COMBO::MAX_COUNT_TIME;
	}
}
