
#include "DxLib.h"
#include "Score.h"
#include "NumberGraph/Number.h"

namespace BOUDAMA
{
	void Score::Init(void)
	{
		score_ = 0;
		endlessBestScore_ = 0;
		scoreCharaHandle_ = -1;
		bestScoreCharaHandle_ = -1;
	}

	//�ǂݍ��ݏ����֐�
	void Score::Load(void)
	{
		if (scoreCharaHandle_ == -1)
		{
			scoreCharaHandle_ = LoadGraph(SCORE::SCORE_CHARA_PATH);
		}

		if (bestScoreCharaHandle_ == -1)
		{
			bestScoreCharaHandle_ = LoadGraph(SCORE::BEST_SCORE_CHARA_PATH);
		}
	}

	//�`�揈��
	void Score::Draw(int initPosX, int initPosY, int drawInterval, float drawNumScale)
	{
		NumberGraph::Draw(score_, initPosX, initPosY, drawInterval, drawNumScale);
	}

	//�j�������֐�
	void Score::Fin(void)
	{
		if (scoreCharaHandle_ != -1)
		{
			DeleteGraph(scoreCharaHandle_);
		}
		if (bestScoreCharaHandle_ != -1)
		{
			DeleteGraph(bestScoreCharaHandle_);
		}
	}

	//�ō��L�^�X�V����
	void Score::UpdateBestScore(void)
	{
		if (bestScore_ < score_)
		{
			bestScore_ = score_;
		}
	}

	//�ō��L�^�X�V����
	void Score::UpdateEndlessBestScore(void)
	{
		if (endlessBestScore_ < score_)
		{
			endlessBestScore_ = score_;
		}
	}

	//�L�^�`��
	void Score::DrawScore(int initPosX, int initPosY)
	{
		//�u�X�R�A�v�̕����̉摜�̕`��ʒu��ς��邽�߂ɍŌ�ɕ`�悵�������̈ʒu��ۑ�����
		int lastDrawPosX = initPosX;

		//�`�悷�鐔����ۑ�
		unsigned int tempNum = score_;

		//��̈ʂ̐����𒲂ׂ邽�߂̕ϐ�
		int remainderNum = 0;

		//�E���珇�ɑS�ĕ`�悷��܂ő�����
		while (-1)
		{
			//10�Ŋ���A��̈ʂ̐����𒲂ׂ�
			remainderNum = tempNum % 10;

			//��̈ʂ̐�����`��
			DrawRotaGraph(lastDrawPosX, initPosY, 1.0f, 0.0f, NumberGraph::GetGraphHandle(remainderNum), true);

			//�\�̈ʂ̐�������̈ʂɈړ�����
			tempNum /= 10;

			//�S�ĕ`�悵����E�o
			if (tempNum <= 0)
			{
				break;
			}

			//���̌��̐�����`�悷�邽�߂Ɉʒu���ړ�
			lastDrawPosX -= NUMBER_GRAPH::DRAW_POS_INTERVAL;
		}

		//�u�X�R�A�v�̉摜�`��
		DrawRotaGraph(lastDrawPosX - SCORE::SCORE_CHARA_SUB_POS_X, initPosY, 0.5f, 0.0f, scoreCharaHandle_, true);

	}

	//�x�X�g�X�R�A�`��
	void Score::DrawBestScore(void)
	{
		NumberGraph::Draw(bestScore_, SCORE::CLEAR_GAMEOVER::BEST_SCORE_INIT_POS_X, SCORE::CLEAR_GAMEOVER::BEST_SCORE_INIT_POS_Y);

		DrawRotaGraph(SCORE::CLEAR_GAMEOVER::BEST_SCORE_CHARA_POS_X, SCORE::CLEAR_GAMEOVER::BEST_SCORE_CHARA_POS_Y, 1.0f, 0.0f, bestScoreCharaHandle_, true);
	}

	//�ō��L�^�`��
	void Score::DrawEndlessBestScore(void)
	{
		NumberGraph::Draw(endlessBestScore_, SCORE::CLEAR_GAMEOVER::BEST_SCORE_INIT_POS_X, SCORE::CLEAR_GAMEOVER::BEST_SCORE_INIT_POS_Y);

		DrawRotaGraph(SCORE::CLEAR_GAMEOVER::BEST_SCORE_CHARA_POS_X, SCORE::CLEAR_GAMEOVER::BEST_SCORE_CHARA_POS_Y, 1.0f, 0.0f, bestScoreCharaHandle_, true);

	}
}
