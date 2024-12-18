#include "EnemyBomber.h"
#include "EnemyParameter.h"

#include "Math/MyMath.h"
#include "Common/Common.h"

#include <Matrix/Matrix3D.h>

#include "State/RandomWalk/RandomWalk.h"
#include "State/FindOut/FindOut.h"
#include "State/Chase/Chase.h"
#include "State/KnockBack/KnockBack.h"
#include "State/Corpse/Corpse.h"
#include "State/Idle/Idle.h"
#include "State/RunAway/RunAway.h"

namespace BOUDAMA
{
	//初期化処理関数
	void EnemyBomber::Init(void)
	{
		//初期化
		handle_ = -1;
		isAlive_ = false;
		hp_ = BOMBER::HP;
		radius_ = BOMBER::RADIUS;
		pos_ = BOMBER::INIT_POS;
		velocity_ = MyMath::ZERO_VECTOR_3D;
		rot_ = MyMath::ZERO_VECTOR_3D;
		dir_ = { 0.0f,0.0f,1.0f };

		scoreNum_ = BOMBER::ADD_SCORE_NUM;

		bombThrowStunTime_ = 0;

		stateMachine_ = std::make_unique<EnemyBase::StateMachineType>();

		stateMachine_->AddState<RandomWalk>(ENEMY_STATE::RANDOM_WALK, ENEMY_STATE::FIND_OUT, BOMBER::SPEED, BOMBER::MAX_SPEED, BOMBER::FIND_OUT_RANGE);
		stateMachine_->AddState<FindOut>(ENEMY_STATE::FIND_OUT, ENEMY_STATE::RUN_AWAY, BOMBER::REACTION_MAX_TIME);
		stateMachine_->AddState<RunAway>(ENEMY_STATE::RUN_AWAY, ENEMY_STATE::IDLE, BOMBER::RUN_AWAY_SPEED);
		stateMachine_->AddState<Idle>(ENEMY_STATE::IDLE, ENEMY_STATE::RANDOM_WALK, BOMBER::ATTACK_STUN_TIME);
		stateMachine_->AddState<KnockBack>(ENEMY_STATE::KNOCK_BACK, ENEMY_STATE::RANDOM_WALK);
		stateMachine_->AddState<Corpse>(ENEMY_STATE::CORPSE);

		stateMachine_->ChangeState(ENEMY_STATE::RANDOM_WALK);

		bomb_->SetIsActive(false);

		//位置・角度設定
		MV1SetPosition(handle_, pos_);
		MV1SetRotationXYZ(handle_, rot_);
	}

	//行動処理関数
	void EnemyBomber::Step(const Vector3D& playerPos)
	{
		//死亡していたら実行しない
		if (!isAlive_)
		{
			return;
		}

		targetPosition_ = playerPos;

		stateMachine_->Step();
		
		if(BOMBER::CHASE_MIN_RANGE <= pos_.y)
		{
			pos_.y -= BOMBER::GRAVITY;
		}

		if (pos_.y <= BOMBER::GROUND_POS_Y)
		{
			pos_.y = BOMBER::GROUND_POS_Y;
		}

		floatMotionTheta_ < MyMath::TWO_PI ? floatMotionTheta_ += MyMath::INVERSE_TWO_PI : floatMotionTheta_ = 0.0f;

		pos_.y += BOMBER::FLOAT_MOTION_BOOST * std::sin(floatMotionTheta_);

		if (0 < bombThrowStunTime_)
		{
			if (bombThrowStunTime_ <= BOMBER::ATTACK_STUN_TIME)
			{
				++bombThrowStunTime_;
			}
			else
			{
				bombThrowStunTime_ = 0;
				bomb_->SetIsActive(true);
			}

			//位置・角度設定
			MV1SetPosition(handle_, pos_);
			MV1SetRotationXYZ(handle_, rot_);

			return;
		}
		

		bomb_->SetPos(pos_ + BOMB::HOLD_UP_DISTANCE);
		
		Vector3D myPosToTargetPos = targetPosition_ - pos_;

		if (myPosToTargetPos.SquareL2Norm() <= BOMBER::SQUARE_CHASE_MIN_RANGE && 0.0f < Vector3D::Dot(dir_, myPosToTargetPos.Normalize()) )
		{
			Vector3D throwVelocity = myPosToTargetPos * BOMB::THROW_SPEED;
			throwVelocity.y = BOMB::THROW_SPEED;

			bomb_->SetVelocity(throwVelocity);
			bomb_->AppearanceRequest();

			++bombThrowStunTime_;

			stateMachine_->ChangeState(ENEMY_STATE::FIND_OUT);
		}

		//位置・角度設定
		MV1SetPosition(handle_, pos_);
		MV1SetRotationXYZ(handle_, rot_);
	}


	//描画処理関数
	void EnemyBomber::Draw(void)
	{
		if (!isAlive_)
		{
			return;
		}

		//モデル描画
		MV1DrawModel(handle_);

		DrawLine3D(pos_, pos_ + dir_ * BOMBER::FIND_OUT_RANGE, GetColor(255, 0, 0));
	}

	//出現処理関数
	void EnemyBomber::AppearanceRequest(void)
	{
		//初期位置設定
		pos_ = Matrix3D::GetYawMatrix(MyMath::DegreesToRadian(GetRand(359))) *
			Matrix3D::GetTranslateMatrix(BOMBER::INIT_POS) * MyMath::ZERO_VECTOR_3D;

		//角度初期化
		rot_ = MyMath::ZERO_VECTOR_3D;

		//速度初期化
		velocity_ = MyMath::ZERO_VECTOR_3D;


		//死者蘇生
		isAlive_ = true;
		isCollisionEnabled_ = true;

		stateMachine_->ChangeState(ENEMY_STATE::RANDOM_WALK);

		bomb_->SetIsActive(true);
		bomb_->SetPos(pos_ + BOMB::HOLD_UP_DISTANCE);

		//位置・角度設定
		MV1SetPosition(handle_, pos_);
		MV1SetRotationXYZ(handle_, rot_);
	}
}
