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
	//初期化処理関数
	void Enemy::Init(void)
	{
		//初期化
		handle_ = -1;
		isAlive_ = false;
		hp_ = DARUMA::HP;
		knockBackTimeCount_ = 0;
		scoreNum_ = DARUMA::ADD_SCORE_NUM;
		radius_ = DARUMA::RADIUS;
		pos_ = DARUMA::INIT_POS;
		velocity_ = MyMath::ZERO_VECTOR_3D;
		rot_ = MyMath::ZERO_VECTOR_3D;

		stateMachine_ = std::make_unique<EnemyBase::StateMachineType>();

		stateMachine_->AddState<Chase>(ENEMY_STATE::CHASE, DARUMA::SPEED);
		stateMachine_->AddState<KnockBack>(ENEMY_STATE::KNOCK_BACK, ENEMY_STATE::CHASE);
		stateMachine_->AddState<Corpse>(ENEMY_STATE::CORPSE);

		stateMachine_->ChangeState(ENEMY_STATE::CHASE);
	}

	//行動処理関数
	void Enemy::Step(const Vector3D& playerPos)
	{
		//死亡していたら実行しない
		if (!isAlive_)
		{
			return;
		}

		targetPosition_ = playerPos;

		stateMachine_->Step();

		//重力をかけても地面にめり込まなければ処理をする
		pos_.y - DARUMA::GRAVITY > DARUMA::RADIUS ? pos_.y -= DARUMA::GRAVITY : pos_.y = DARUMA::RADIUS;

		//位置・角度設定
		MV1SetPosition(handle_, pos_);
		MV1SetRotationXYZ(handle_, rot_);

		return;

	}


	//描画処理関数
	void Enemy::Draw(void)
	{
		//死亡している場合は実行しない
		if (!isAlive_)
		{
			return;
		}

		//描画処理
		MV1DrawModel(handle_);

	}

	//出現処理関数
	void Enemy::AppearanceRequest(void)
	{
		//初期位置設定
		pos_ = Matrix3D::GetYawMatrix(MyMath::DegreesToRadian(static_cast<float>(GetRand(359)))) *
			Matrix3D::GetTranslateMatrix(DARUMA::INIT_POS) * MyMath::ZERO_VECTOR_3D;

		//死者蘇生
		isAlive_ = true;
		isCollisionEnabled_ = true;

		stateMachine_->ChangeState(ENEMY_STATE::CHASE);

		//位置・角度設定
		MV1SetPosition(handle_, pos_);
		MV1SetRotationXYZ(handle_, rot_);
	}

}
