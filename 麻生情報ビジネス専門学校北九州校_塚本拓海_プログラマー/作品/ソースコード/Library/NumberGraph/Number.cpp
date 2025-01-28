#include "Number.h"
#include "DxLib.h"

//�����������֐�
void NumberGraph::Init(void)
{
	for (int graphHandle : graphHandle_)
	{
		graphHandle = -1;
	}
}

//�ǂݍ��ݏ����֐�
void NumberGraph::Load(void)
{
	LoadDivGraph(NUMBER_GRAPH::PATH, NUMBER_GRAPH::ALL_NUM, 10, 1, 64, 64, graphHandle_);
}

//�ꌅ�ڂ̐������獶�֏��ɕ`�悷��֐�
void NumberGraph::Draw(int drawNum, int initPosX, int initPosY, int drawInterval, float drawNumScale)
{
	//�`�悷�鐔����ۑ�
	int tempNum = drawNum;

	//��̈ʂ̐����𒲂ׂ邽�߂̕ϐ�
	int remainderNum = 0;

	//������񐔂�ۑ�����ϐ�
	int num = 0;

	//�E���珇�ɑS�ĕ`�悷��܂ő�����
	while(-1)
	{
		//10�Ŋ���A��̈ʂ̐����𒲂ׂ�
		remainderNum = tempNum % 10;
		//��̈ʂ̐�����`��
		DrawRotaGraph(initPosX - (drawInterval * num), initPosY, drawNumScale, 0.0f, graphHandle_[remainderNum], true);
		//�\�̈ʂ̐�������̈ʂɈړ�����
		tempNum /= 10;

		//�S�ĕ`�悵����߂�
		if (tempNum <= 0)
		{
			return;
		}

		//���̏ꏊ�ɕ`�悷�邽�߂ɃC���N�������g
		++num;
	}
}


void NumberGraph::Fin(void)
{
	//�摜�j������
	for (int graphHandle : graphHandle_)
	{
		if (graphHandle != -1)
		{
			DeleteGraph(graphHandle);
			graphHandle = -1;
		}
	}
}