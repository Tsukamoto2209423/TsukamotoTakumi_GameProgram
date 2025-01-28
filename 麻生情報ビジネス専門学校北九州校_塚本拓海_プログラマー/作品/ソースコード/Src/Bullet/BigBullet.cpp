#include "BigBullet.h"
#include "Math/MyMath.h"
#include "Player/PlayerParameter.h"

namespace BOUDAMA
{
	//�R���X�g���N�^
	BigBullet::BigBullet(void)
	{
		//������
		handle_ = -1;
		isAlive_ = false;
		lifeSpan_ = 0;
		radius_ = BIG_BULLET::RADIUS;
		pos_ = MyMath::ZERO_VECTOR_3D;
		dir_ = MyMath::ZERO_VECTOR_3D;
		velocity_ = MyMath::ZERO_VECTOR_3D;
	}

	//�f�X�g���N�^
	BigBullet::~BigBullet(void)
	{

	}

	//�ǂݍ��ݏ����֐�
	void BigBullet::Load(int origineHandle)
	{
		if (handle_ == -1)
		{
			handle_ = MV1DuplicateModel(origineHandle);
			MV1SetScale(handle_, { 1.3f,1.3f,1.3f });
		}
	}

	//�s�������֐�
	void BigBullet::Step(void)
	{
		//�e�𓮂���
		dir_.x = -sinf(rot_.y) * BIG_BULLET::SPEED;
		dir_.z = -cosf(rot_.y) * BIG_BULLET::SPEED;

		pos_ += dir_;

		++lifeSpan_;

		//��ʊO�ɏo�����������s�����ꍇ�A���S����
		if (MyMath::Abs(pos_.x) > BIG_BULLET::MAX_POS_X_Z || MyMath::Abs(pos_.z) > BIG_BULLET::MAX_POS_X_Z ||
			lifeSpan_ >= BIG_BULLET::MAX_LIFE_SPAN)
		{
			isAlive_ = false;
			lifeSpan_ = 0;
			dir_ = MyMath::ZERO_VECTOR_3D;
		}

		//���W�ݒ�
		MV1SetPosition(handle_, pos_);
	}

	//�����蔻�菈��
	void BigBullet::HitCalculation(void)
	{
		//���S����
		isAlive_ = false;
		pos_ = MyMath::ZERO_VECTOR_3D;
		radius_ = 50.0f;
	}
}
