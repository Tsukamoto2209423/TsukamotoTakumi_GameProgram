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
	//コンストラクタ
	EnemyMonster::EnemyMonster()
	{
		//初期化
		handle_ = -1;
		isAlive_ = true;
		hp_ = MONSTER::HP;
		radius_ = BOMBER::RADIUS;
		pos_ = MyMath::ZERO_VECTOR_3D;
		velocity_ = MyMath::ZERO_VECTOR_3D;
		rot_ = MyMath::ZERO_VECTOR_3D;
	}

	//デストラクタ
	EnemyMonster::~EnemyMonster()
	{

	}

	//初期化処理関数
	void EnemyMonster::Init(void)
	{
		//初期化
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

	//行動処理関数
	void EnemyMonster::Step(const Vector3D& playerPos)
	{
		//死亡している場合は実行しない
		if (!isAlive_)
		{
			return;
		}

		targetPosition_ = playerPos;

		stateMachine_->Step();

		//重力をかけても地面にめり込まなければ重力処理をする
		pos_.y - MONSTER::GRAVITY > MONSTER::RADIUS ? pos_.y -= MONSTER::GRAVITY : pos_.y = MONSTER::RADIUS;

		//位置・角度設定
		MV1SetPosition(handle_, pos_);
		MV1SetRotationXYZ(handle_, rot_);

		return;

	}

	//描画処理関数
	void EnemyMonster::Draw(void)
	{
		if (!isAlive_)
		{
			return;
		}

		MV1DrawModel(handle_);

  		DrawLine3D(pos_, pos_ + dir_ * MONSTER::FIND_OUT_RANGE, GetColor(255, 0, 0));

	}

	//出現処理関数
	void EnemyMonster::AppearanceRequest(void)
	{
		//初期位置設定
		pos_ = Matrix3D::GetYawMatrix(MyMath::DegreesToRadian(GetRand(359)))
			* Matrix3D::GetTranslateMatrix(MONSTER::INIT_POS) * MyMath::ZERO_VECTOR_3D;

		//角度初期化
		rot_ = MyMath::ZERO_VECTOR_3D;

		//速度初期化
		velocity_ = MyMath::ZERO_VECTOR_3D;

		//死者蘇生
		isAlive_ = true;
		isCollisionEnabled_ = true;

		stateMachine_->ChangeState(ENEMY_STATE::RANDOM_WALK);

		//位置・角度設定
		MV1SetPosition(handle_, pos_);
		MV1SetRotationXYZ(handle_, rot_);
	}


}
