#include "EnemyBase.h"
#include <Effekseer/Effekseer.h>
#include <Matrix/Matrix3D.h>
#include <Math/MyMath.h>
#include <EffekseerParameter.h>
#include <Score/Score.h>

namespace BOUDAMA
{
	//�ǂݍ��ݏ����֐�
	void EnemyBase::Load(int originalHandle)
	{
		if (handle_ == -1)
		{
			handle_ = MV1DuplicateModel(originalHandle);

			//�ʒu�E�p�x�ݒ�
			MV1SetPosition(handle_, pos_);
			MV1SetRotationXYZ(handle_, rot_);
		}
	}

	//�o�������֐�
	void EnemyBase::AppearanceRequest(void)
	{
		//�����ʒu�ݒ�
		pos_ = Matrix3D::GetYawMatrix(MyMath::DegreesToRadian(GetRand(359))) *
			Matrix3D::GetTranslateMatrix(Vector3D(0.0f, 0.0f, 3750.0f)) * MyMath::ZERO_VECTOR_3D;

		//���ґh��
		isAlive_ = true;
		isCollisionEnabled_ = true;

		//�ʒu�E�p�x�ݒ�
		MV1SetPosition(handle_, pos_);
		MV1SetRotationXYZ(handle_, rot_);
	}

	//�s�������֐�
	void EnemyBase::Step(const Vector3D& playerPos) {}


	void EnemyBase::HitCalculation(void) 
	{
		--hp_;

		if (hp_ <= 0)
		{
			stateMachine_->ChangeState(ENEMY_STATE::CORPSE);
			Score::AddScore(scoreNum_);
		}
		else
		{
			stateMachine_->ChangeState(ENEMY_STATE::KNOCK_BACK);
		}

		CEffekseerCtrl::Request(EFFECT::HIT_EFFECT, pos_, false);
	}
	
	void EnemyBase::HitCalculation(int damage) 
	{
		hp_ -= damage;

		if (hp_ <= 0)
		{
			stateMachine_->ChangeState(ENEMY_STATE::CORPSE);
			Score::AddScore(scoreNum_);
		}
		else
		{
			stateMachine_->ChangeState(ENEMY_STATE::KNOCK_BACK);
		}

		CEffekseerCtrl::Request(EFFECT::HIT_EFFECT, pos_, false);
	}

	void EnemyBase::DeathCalculation(const Vector3D& hitObjectVelocity)
	{
		//�Ԃ���������̑��x�󂯎��A������΂��C�����悳���o�����߂�KNOCK_BACK_BOOST���|���đ��傳����
		velocity_ = hitObjectVelocity * ENEMY::KNOCK_BACK_BOOST;

		stateMachine_->ChangeState(ENEMY_STATE::CORPSE);

		CEffekseerCtrl::Request(EFFECT::HIT_EFFECT, pos_, false);
	}
}
