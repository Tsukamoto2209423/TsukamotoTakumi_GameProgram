#include "EnemyBomber.h"
#include "EnemyParameter.h"
#include "Math/MyMath.h"
#include "Common/Common.h"
#include "Player/Player.h"
#include <Player/PlayerParameter.h>
#include <Matrix/Matrix3D.h>
#include "State/RandomWalk/RandomWalk.h"
#include "State/FindOut/FindOut.h"
#include "State/Attack/StraightAttack.h"
#include "State/KnockBack/KnockBack.h"
#include "State/Corpse/Corpse.h"

namespace BOUDAMA
{
	//コンストラクタ
	EnemyBomber::EnemyBomber()
	{
		//初期化
		handle_ = -1;
		isAlive_ = false;
		hp_ = 3;
		radius_ = BOMBER::RADIUS;
		pos_ = MyMath::ZERO_VECTOR_3D;
		velocity_ = MyMath::ZERO_VECTOR_3D;
		rot_ = MyMath::ZERO_VECTOR_3D;


		findOutReactionCount_ = 0;
		moveAngleChangeCount_ = 0;
		knockBackTimeCount_ = 0;
		attackChargeCount_ = 0;
	}

	//デストラクタ
	EnemyBomber::~EnemyBomber()
	{

	}

	//初期化処理関数
	void EnemyBomber::Init(void)
	{
		//初期化
		handle_ = -1;
		isAlive_ = false;
		hp_ = 3;
		radius_ = BOMBER::RADIUS;
		knockBackTimeCount_ = 0;
		pos_ = BOMBER::INIT_POS;
		velocity_ = MyMath::ZERO_VECTOR_3D;
		rot_ = MyMath::ZERO_VECTOR_3D;


		findOutReactionCount_ = 0;
		moveAngleChangeCount_ = 0;
		knockBackTimeCount_ = 0;
		attackChargeCount_ = 0;

		stateMachine_ = std::make_unique<EnemyBase::StateMachineType>();

		stateMachine_->AddState<RandomWalk>(ENEMY_STATE::RANDOM_WALK, ENEMY_STATE::FIND_OUT, BOMBER::SPEED, BOMBER::MAX_SPEED, BOMBER::FIND_OUT_RANGE);
		stateMachine_->AddState<FindOut>(ENEMY_STATE::FIND_OUT, ENEMY_STATE::ATTACK, BOMBER::REACTION_MAX_TIME);
		stateMachine_->AddState<KnockBack>(ENEMY_STATE::KNOCK_BACK, ENEMY_STATE::RANDOM_WALK);
		stateMachine_->AddState<Corpse>(ENEMY_STATE::CORPSE);

		stateMachine_->ChangeState(ENEMY_STATE::RANDOM_WALK);

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

	}

	//出現処理関数
	void EnemyBomber::AppearanceRequest(void)
	{
		//初期位置設定
		pos_ = Matrix3D::GetYawMatrix(MyMath::DegreesToRadian(GetRand(359))) *
			Matrix3D::GetTranslateMatrix(BOMBER::INIT_POS) * MyMath::ZERO_VECTOR_3D;

		//角度初期化
		rot_ = MyMath::ZERO_VECTOR_3D;

		//死者蘇生
		isAlive_ = true;

		//位置・角度設定
		MV1SetPosition(handle_, pos_);
		MV1SetRotationXYZ(handle_, rot_);
	}
}
