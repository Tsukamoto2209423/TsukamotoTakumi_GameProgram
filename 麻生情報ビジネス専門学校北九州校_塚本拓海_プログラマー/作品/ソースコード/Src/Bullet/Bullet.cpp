#include "Bullet.h"
#include "Math/MyMath.h"
#include "Common/Common.h"
#include "Player/PlayerParameter.h"

namespace BOUDAMA
{
	//�R���X�g���N�^
	Bullet::Bullet(void)
	{
		//������
		handle_ = -1;
		isAlive_ = false;
		radius_ = BULLET::RADIUS;
		lifeSpan_ = 0;
		pos_ = MyMath::ZERO_VECTOR_3D;
		dir_ = MyMath::ZERO_VECTOR_3D;
		velocity_ = MyMath::ZERO_VECTOR_3D;
	}

	//�f�X�g���N�^
	Bullet::~Bullet(void)
	{

	}

	//�s�������֐�
	void Bullet::Step(void)
	{
		//�e�𓮂���
		dir_.x = -sinf(rot_.y) * BULLET::SPEED;
		dir_.z = -cosf(rot_.y) * BULLET::SPEED;

		pos_ += dir_;

		++lifeSpan_;

		//��ʊO�ɏo���ꍇ�A���S����
		if (MyMath::Abs(pos_.x) > 3000.0f || MyMath::Abs(pos_.z) > 3000.0f || lifeSpan_ >= BULLET::MAX_LIFE_SPAN)
		{
			isAlive_ = false;
			lifeSpan_ = 0;
			dir_ = MyMath::ZERO_VECTOR_3D;
		}

		//���W�ݒ�
		MV1SetPosition(handle_, pos_);
	}
}
