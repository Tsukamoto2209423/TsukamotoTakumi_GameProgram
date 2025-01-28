#include "EnemyMonster.h"
#include "EnemyParameter.h"
#include <Math/MyMath.h>
#include <Matrix/Matrix3D.h>
#include "State/RandomWalk/RandomWalk.h"
#include "State/FindOut/FindOut.h"
#include "State/Attack/StraightAttack.h"
#include "State/KnockBack/KnockBack.h"
#include "State/Corpse/Corpse.h"
#include "State/Idle/Idle.h"

namespace BOUDAMA
{
	//�R���X�g���N�^
	EnemyMonster::EnemyMonster()
	{
		//������
		handle_ = -1;
		isAlive_ = true;
		hp_ = MONSTER::HP;
		radius_ = BOMBER::RADIUS;
		pos_ = MyMath::ZERO_VECTOR_3D;
		velocity_ = MyMath::ZERO_VECTOR_3D;
		rot_ = MyMath::ZERO_VECTOR_3D;
	}

	//�f�X�g���N�^
	EnemyMonster::~EnemyMonster()
	{

	}

	//�����������֐�
	void EnemyMonster::Init(void)
	{
		//������
		handle_ = -1;
		scoreNum_ = MONSTER::ADD_SCORE_NUM;
		isAlive_ = false;
		hp_ = MONSTER::HP;
		radius_ = BOMBER::RADIUS;
		pos_ = MONSTER::INIT_POS;
		velocity_ = MyMath::ZERO_VECTOR_3D;
		rot_ = MyMath::ZERO_VECTOR_3D;
		dir_ = { 0.0f,0.0f,1.0f };

		dir_ *= Matrix3D::GetYawMatrix(MyMath::DegreesToRadian(GetRand(359)));

		rot_.y = std::atan2(-dir_.x, -dir_.z);

		pos_ *= Matrix3D::GetYawMatrix(MyMath::DegreesToRadian(GetRand(359)));


		stateMachine_ = std::make_unique<EnemyBase::StateMachineType>();

		stateMachine_->AddState<RandomWalk>(ENEMY_STATE::RANDOM_WALK, ENEMY_STATE::FIND_OUT, MONSTER::SPEED, MONSTER::MAX_SPEED, MONSTER::FIND_OUT_RANGE, MONSTER::MAX_POS_X_Z, MONSTER::DIRECTION_CHANGE_INTERVAL);
		stateMachine_->AddState<FindOut>(ENEMY_STATE::FIND_OUT, ENEMY_STATE::ATTACK, MONSTER::REACTION_MAX_TIME, MONSTER::ADD_EXCLAMATION_DISTANCE);
		stateMachine_->AddState<StraightAttack>(ENEMY_STATE::ATTACK, ENEMY_STATE::IDLE, MONSTER::ATTACK_SPEED, MONSTER::ATTACK_MAX_TIME);
		stateMachine_->AddState<Idle>(ENEMY_STATE::IDLE, ENEMY_STATE::RANDOM_WALK, MONSTER::ATTACK_STUN_TIME);
		stateMachine_->AddState<KnockBack>(ENEMY_STATE::KNOCK_BACK, ENEMY_STATE::IDLE);
		stateMachine_->AddState<Corpse>(ENEMY_STATE::CORPSE, ENEMY_STATE::IDLE);

		stateMachine_->ChangeState(ENEMY_STATE::RANDOM_WALK);

		MV1SetScale(handle_, VECTOR(2.0f, 2.0f, 2.0f));
	}

	//�s�������֐�
	void EnemyMonster::Step(const Vector3D& playerPos)
	{
		//���S���Ă���ꍇ�͎��s���Ȃ�
		if (!isAlive_)
		{
			return;
		}

		targetPosition_ = playerPos;

		stateMachine_->Step();

		//�d�͂������Ă��n�ʂɂ߂荞�܂Ȃ���Ώd�͏���������
		pos_.y - MONSTER::GRAVITY > MONSTER::RADIUS ? pos_.y -= MONSTER::GRAVITY : pos_.y = MONSTER::RADIUS;

		//�ʒu�E�p�x�ݒ�
		MV1SetPosition(handle_, pos_);
		MV1SetRotationXYZ(handle_, rot_);

		return;

	}

	//�`�揈���֐�
	void EnemyMonster::Draw(void)
	{
		if (!isAlive_)
		{
			return;
		}

		MV1DrawModel(handle_);

  		DrawLine3D(pos_, pos_ + dir_ * MONSTER::FIND_OUT_RANGE, GetColor(255, 0, 0));

	}

	//�o�������֐�
	void EnemyMonster::AppearanceRequest(void)
	{
		//�����ʒu�ݒ�
		pos_ = Matrix3D::GetYawMatrix(MyMath::DegreesToRadian(GetRand(359)))
			* Matrix3D::GetTranslateMatrix(MONSTER::INIT_POS) * MyMath::ZERO_VECTOR_3D;

		//�p�x������
		rot_ = MyMath::ZERO_VECTOR_3D;

		//���x������
		velocity_ = MyMath::ZERO_VECTOR_3D;

		//���ґh��
		isAlive_ = true;
		isCollisionEnabled_ = true;

		stateMachine_->ChangeState(ENEMY_STATE::RANDOM_WALK);

		//�ʒu�E�p�x�ݒ�
		MV1SetPosition(handle_, pos_);
		MV1SetRotationXYZ(handle_, rot_);
	}


}
