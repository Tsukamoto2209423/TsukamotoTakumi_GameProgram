#include "EnemyBomber.h"
#include "EnemyParameter.h"
#include "Math/MyMath.h"
#include "Common/Common.h"
#include "Player/Player.h"
#include <Player/PlayerParameter.h>
#include <Matrix/Matrix3D.h>

namespace BOUDAMA
{
	//コンストラクタ
	EnemyBomber::EnemyBomber()
	{
		//初期化
		handle_ = -1;
		isAlive_ = false;
		hp_ = 3;
		radius_ = ENEMY_BOMBER::RADIUS;
		state_ = ENEMY::STATE::SEARCH;
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
		radius_ = ENEMY_BOMBER::RADIUS;
		knockBackTimeCount_ = 0;
		state_ = ENEMY::STATE::SEARCH;
		pos_ = ENEMY_BOMBER::INIT_POS;
		velocity_ = MyMath::ZERO_VECTOR_3D;
		rot_ = MyMath::ZERO_VECTOR_3D;


		findOutReactionCount_ = 0;
		moveAngleChangeCount_ = 0;
		knockBackTimeCount_ = 0;
		attackChargeCount_ = 0;
	}

	//行動処理関数
	void EnemyBomber::Step(const Vector3D& playerPos)
	{
		//死亡していたら実行しない
		if (!isAlive_)
		{
			return;
		}


		if (state_ == ENEMY::STATE::KNOCK_BACK)
		{
			if (knockBackTimeCount_ > 60)
			{
				knockBackTimeCount_ = 0;
				isAlive_ = false;
				state_ = ENEMY::STATE::SEARCH;
				pos_ = MyMath::ZERO_VECTOR_3D;
				rot_ = MyMath::ZERO_VECTOR_3D;
				velocity_ = MyMath::ZERO_VECTOR_3D;
			}

			pos_ += velocity_;
			pos_.y += 9.5f;

			rot_.x += MyMath::INVERSE_TWO_PI;

			//ノックバックの時間計測
			++knockBackTimeCount_;

			//位置・角度設定
			MV1SetPosition(handle_, pos_);
			MV1SetRotationXYZ(handle_, rot_);


			return;
		}


		//プレイヤー探索状態
		if (state_ == ENEMY::STATE::SEARCH)
		{
			velocity_ += dir_.Normalize() * 0.125f;

			//一定の速度を超えたら
			if (velocity_.SquareL2Norm() > ENEMY_BOMBER::MAX_SPEED * ENEMY_BOMBER::MAX_SPEED)
			{
				velocity_ = velocity_.Normalize() * ENEMY_BOMBER::MAX_SPEED;
			}

			pos_ += velocity_;

			if (MyMath::Abs(pos_.x) > ENEMY_BOMBER::MAX_POS_X_Z)
			{
				pos_.x = 0.0f < pos_.x ? ENEMY_BOMBER::MAX_POS_X_Z : -ENEMY_BOMBER::MAX_POS_X_Z;
				dir_ = -dir_;
				velocity_ = -velocity_;
			}

			if (MyMath::Abs(pos_.z) > ENEMY_BOMBER::MAX_POS_X_Z)
			{
				pos_.z = 0.0f < pos_.z ? ENEMY_BOMBER::MAX_POS_X_Z : -ENEMY_BOMBER::MAX_POS_X_Z;

				dir_ = -dir_;
				velocity_ = -velocity_;
			}

			//位置・角度設定
			MV1SetPosition(handle_, pos_);
			MV1SetRotationXYZ(handle_, rot_);


			//移動する角度切り替え時間計測
			++moveAngleChangeCount_;

			if (moveAngleChangeCount_ >= ENEMY_BOMBER::MOVEANGLE_CHANGE_MAX_NUM)
			{
				dir_ = dir_ * Matrix3D::GetYawMatrix(MyMath::DegreesToRadian(GetRand(359)));

				//角度切り替え設定
				rot_.y = atan2f(-dir_.x, -dir_.z);

				//速度初期化
				velocity_ = { 0.0f,0.0f,0.0f };

				//移動する角度切り替え時間初期化
				moveAngleChangeCount_ = 0;
			}

			//プレイヤーを視界の範囲内に居ないなら関数脱出
			if (Vector3D::Dot(dir_, playerPos) < 0.0f)
			{
				return;
			}

			//プレイヤーが近くにいたら
			if ((playerPos - pos_).SquareL2Norm() < ENEMY_BOMBER::SQUARE_FIND_OUT_RANGE)
			{
				//プレイヤー発見状態に移行
				state_ = ENEMY::STATE::FIND_OUT;

				velocity_ = { 0.0f,0.0f,0.0f };

				return;
			}

			return;
		}

		//プレイヤー発見状態
		if (state_ == ENEMY::STATE::FIND_OUT)
		{
			//プレイヤーの方向を向かせる
			dir_ = playerPos - pos_;

			rot_.y = atan2f(-dir_.x, -dir_.z);

			MV1SetRotationXYZ(handle_, rot_);

			//見つけた時の反応時間計測
			++findOutReactionCount_;

			//一定時間経ったら追いかけ状態に移行
			if (findOutReactionCount_ >= ENEMY_BOMBER::REACTION_MAX_TIME)
			{
				state_ = ENEMY::STATE::CHASE;
				findOutReactionCount_ = 0;

				return;
			}

			return;
		}

		//プレイヤー追跡状態
		if (state_ == ENEMY::STATE::CHASE)
		{
			//自分自身からプレイヤーまでのベクトル作成
			dir_ = playerPos - pos_;

			//単位ベクトルにしてスカラー倍し速度に加算
			velocity_ += dir_.Normalize() * ENEMY_BOMBER::CHASE_SPEED;

			//位置に加算
			pos_ += velocity_;

			rot_.y = atan2f(-dir_.x, -dir_.z);

			//一定距離まで近づいたら
			if (dir_.SquareL2Norm() < ENEMY_BOMBER::SQUARE_CHASE_MIN_RANGE)
			{
				//攻撃溜め状態に移行
				state_ = ENEMY::STATE::CHARGE;

				velocity_ = { 0.0f,0.0f,0.0f };
			}

			//位置・角度設定
			MV1SetPosition(handle_, pos_);
			MV1SetRotationXYZ(handle_, rot_);

			return;
		}


		//攻撃溜め状態
		if (state_ == ENEMY::STATE::CHARGE)
		{
			//攻撃溜め時間計測
			++attackChargeCount_;

			//プレイヤーのほうを向く
			dir_ = playerPos - pos_;
			rot_.y = atan2f(-dir_.x, -dir_.z);

			//位置・角度設定
			MV1SetPosition(handle_, pos_);
			MV1SetRotationXYZ(handle_, rot_);

			//攻撃溜め時間経過
			if (attackChargeCount_ > ENEMY_BOMBER::ATTACK_CHARGE_MAX_TIME)
			{
				//攻撃状態に移行
				state_ = ENEMY::STATE::ATTACK;

				//最高速度に設定
				velocity_ = dir_.Normalize() * ENEMY_BOMBER::MAX_SPEED * 2.0f;

				//攻撃溜め時間初期化
				attackChargeCount_ = 0;

				return;
			}

			return;
		}

		//攻撃状態
		if (state_ == ENEMY::STATE::ATTACK)
		{

		}
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
			Matrix3D::GetTranslateMatrix(ENEMY_BOMBER::INIT_POS) * MyMath::ZERO_VECTOR_3D;

		//角度初期化
		rot_ = { 0.0f,0.0f,0.0f };

		//死者蘇生
		isAlive_ = true;

		//位置・角度設定
		MV1SetPosition(handle_, pos_);
		MV1SetRotationXYZ(handle_, rot_);
	}

	//当たり判定処理
	void EnemyBomber::HitCalculation(void)
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
