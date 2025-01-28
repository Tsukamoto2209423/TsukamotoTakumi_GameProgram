#include "BigSubstance.h"
#include "Math/MyMath.h"
#include "SubstanceParameter.h"

namespace BOUDAMA
{
	//�R���X�g���N�^
	BigSubstance::BigSubstance()
	{

	}

	//�f�X�g���N�^
	BigSubstance::~BigSubstance()
	{

	}

	//�����������֐�
	void BigSubstance::Init(void)
	{
		//������
		handle_ = -1;
		isAlive_ = false;
		pos_ = { static_cast<float>(GetRand(600)),20.0f ,static_cast<float>(GetRand(600)) };
		velocity_ = MyMath::ZERO_VECTOR_3D;
		rot_ = MyMath::ZERO_VECTOR_3D;
		radius_ = BIGSUBSTANCE::RADIUS;

		addScoreNum = BIGSUBSTANCE::ADD_SCORE_NUM;
	}


	//�ǂݍ��ݏ����֐�
	void BigSubstance::Load(int origineHandle)
	{
		//�������f���f�[�^�ǂݍ��ݏ���
		handle_ = MV1DuplicateModel(origineHandle);
		MV1SetScale(handle_, VECTOR(2.0f, 2.0f, 2.0f));
	}
}
