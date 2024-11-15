#include "Enemy.h"
#include "EnemyParameter.h"
#include "Math/MyMath.h"
#include "Common/Common.h"
#include "Player/Player.h"
#include <Player/PlayerParameter.h>
#include <Matrix/Matrix3D.h>
#include "State/Idle/Idle.h"
#include "State/Chase/Chase.h"
#include "State/KnockBack/KnockBack.h"

namespace BOUDAMA
{
	//コンストラクタ
	Enemy::Enemy()
	{
		//初期化
		handle_ = -1;
		isAlive_ = false;
		hp_ = 3;
		radius_ = ENEMY::RADIUS;
		state_ = ENEMY::STATE::SEARCH;
		pos_ = MyMath::ZERO_VECTOR_3D;
		velocity_ = MyMath::ZERO_VECTOR_3D;
		rot_ = MyMath::ZERO_VECTOR_3D;
	}

	//デストラクタ
	Enemy::~Enemy()
	{

	}

	//初期化処理関数
	void Enemy::Init(void)
	{
		//初期化
		handle_ = -1;
		isAlive_ = false;
		hp_ = 3;
		knockBackTimeCount_ = 0;
		scoreNum_ = ENEMY::ADD_SCORE_NUM;
		radius_ = ENEMY::RADIUS;
		state_ = ENEMY::STATE::SEARCH;
		pos_ = ENEMY::INIT_POS;
		velocity_ = MyMath::ZERO_VECTOR_3D;
		rot_ = MyMath::ZERO_VECTOR_3D;

		stateMachine_.MakeState<Idle>(ENEMY_STATE::IDLE);
		stateMachine_.MakeState<Chase>(ENEMY_STATE::CHASE, 1.0f);
		stateMachine_.MakeState<KnockBack>(ENEMY_STATE::KNOCK_BACK, 60);

		stateMachine_.SetStartState(ENEMY_STATE::CHASE);
	}

	//行動処理関数
	void Enemy::Step(const Vector3D& playerPos)
	{
		//死亡していたら実行しない
		if (!isAlive_)
		{
			return;
		}

		//ノックバック状態の処理
		if (state_ == ENEMY::STATE::KNOCK_BACK)
		{
			//ノックバック状態の処理が60回されていたら
			if (knockBackTimeCount_ > 60)
			{
				//初期化処理
				knockBackTimeCount_ = 0;
				isAlive_ = false;
				state_ = ENEMY::STATE::SEARCH;
				pos_ = MyMath::ZERO_VECTOR_3D;
				rot_ = MyMath::ZERO_VECTOR_3D;
				velocity_ = MyMath::ZERO_VECTOR_3D;

				return;
			}

			//自分の速度を位置に加算し、上に上昇させる
			pos_ += velocity_;
			pos_.y += 9.5f;

			//回転させる
			rot_.x += MyMath::INVERSE_TWO_PI;

			//ノックバック状態の時間計測
			++knockBackTimeCount_;


			//位置・角度設定
			MV1SetPosition(handle_, pos_);
			MV1SetRotationXYZ(handle_, rot_);

			//早期リターンする
			return;
		}


		velocity_ = playerPos - pos_;

		//位置加算
		pos_ += velocity_.Normalize() * ENEMY::SPEED;

		//重力をかけても地面にめり込まなければ処理をする
		pos_.y - ENEMY::GRAVITY > 10.0f ? pos_.y -= ENEMY::GRAVITY : pos_.y = 10.0f;

		//角度θ計算
		rot_.y = atan2f(velocity_.x, velocity_.z) - DX_PI_F;

		//位置・角度設定
		MV1SetPosition(handle_, pos_);
		MV1SetRotationXYZ(handle_, rot_);

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
			Matrix3D::GetTranslateMatrix(ENEMY::INIT_POS) * MyMath::ZERO_VECTOR_3D;

		//死者蘇生
		isAlive_ = true;

		//位置・角度設定
		MV1SetPosition(handle_, pos_);
		MV1SetRotationXYZ(handle_, rot_);
	}

	//当たり判定処理
	void Enemy::HitCalculation(void)
	{
		//HPを減らす
		--hp_;

		//HPが0以下になったら
		if (hp_ <= 0)
		{
			//死亡処理
			state_ = ENEMY::STATE::KNOCK_BACK;
		}
	}
}
