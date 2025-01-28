#include "Enemy.h"
#include "EnemyParameter.h"

#include <memory>

#include "Math/MyMath.h"
#include "Common/Common.h"
#include "Player/Player.h"
#include <Player/PlayerParameter.h>
#include <Matrix/Matrix3D.h>

#include "State/Idle/Idle.h"
#include "State/Chase/Chase.h"
#include "State/KnockBack/KnockBack.h"
#include "State/Corpse/Corpse.h"

namespace BOUDAMA
{
	//�����������֐�
	void Enemy::Init(void)
	{
		//������
		handle_ = -1;
		isAlive_ = false;
		hp_ = DARUMA::HP;
		scoreNum_ = DARUMA::ADD_SCORE_NUM;
		radius_ = DARUMA::RADIUS;
		pos_ = DARUMA::INIT_POS;
		velocity_ = MyMath::ZERO_VECTOR_3D;
		rot_ = MyMath::ZERO_VECTOR_3D;

		stateMachine_ = std::make_unique<EnemyBase::StateMachineType>();

		//��Ԓǉ�
		stateMachine_->AddState<Chase>(ENEMY_STATE::CHASE, DARUMA::SPEED);
		stateMachine_->AddState<KnockBack>(ENEMY_STATE::KNOCK_BACK, ENEMY_STATE::CHASE);
		stateMachine_->AddState<Corpse>(ENEMY_STATE::CORPSE);

		//�Q�[���J�n���̏�Ԑݒ�
		stateMachine_->ChangeState(ENEMY_STATE::CHASE);
	}

	//�s�������֐�
	void Enemy::Step(const Vector3D& playerPos)
	{
		//���S���Ă�������s���Ȃ�
		if (!isAlive_)
		{
			return;
		}

		targetPosition_ = playerPos;

		stateMachine_->Step();

		//�d�͂������Ă��n�ʂɂ߂荞�܂Ȃ���Ώ���������
		pos_.y - DARUMA::GRAVITY > DARUMA::RADIUS ? pos_.y -= DARUMA::GRAVITY : pos_.y = DARUMA::RADIUS;

		//�ʒu�E�p�x�ݒ�
		MV1SetPosition(handle_, pos_);
		MV1SetRotationXYZ(handle_, rot_);

		return;

	}


	//�`�揈���֐�
	void Enemy::Draw(void)
	{
		//���S���Ă���ꍇ�͎��s���Ȃ�
		if (!isAlive_)
		{
			return;
		}

		//�`�揈��
		MV1DrawModel(handle_);

	}

	//�o�������֐�
	void Enemy::AppearanceRequest(void)
	{
		//�����ʒu�ݒ�
		pos_ = Matrix3D::GetYawMatrix(MyMath::DegreesToRadian(static_cast<float>(GetRand(359)))) *
			Matrix3D::GetTranslateMatrix(DARUMA::INIT_POS) * MyMath::ZERO_VECTOR_3D;

		//�p�x������
		rot_ = MyMath::ZERO_VECTOR_3D;

		//���x������
		velocity_ = MyMath::ZERO_VECTOR_3D;


		//���ґh��
		isAlive_ = true;
		isCollisionEnabled_ = true;

		stateMachine_->ChangeState(ENEMY_STATE::CHASE);

		//�ʒu�E�p�x�ݒ�
		MV1SetPosition(handle_, pos_);
		MV1SetRotationXYZ(handle_, rot_);
	}

}
