#include "EnemyMonster.h"
#include "EnemyParameter.h"
#include <Math/MyMath.h>
#include <Matrix/Matrix3D.h>

namespace BOUDAMA
{
	//コンストラクタ
	EnemyMonster::EnemyMonster()
	{
		//初期化
		handle_ = -1;
		attackChargeCount_ = 0;
		attackTimeCount_ = 0;
		findOutReactionCount_ = 0;
		moveAngleChangeCount_ = 0;
		isAlive_ = true;
		hp_ = 3;
		radius_ = ENEMY_BOMBER::RADIUS;
		state_ = ENEMY::STATE::SEARCH;
		pos_ = MY_MATH::ZERO_VECTOR_3D;
		velocity_ = MY_MATH::ZERO_VECTOR_3D;
		rot_ = MY_MATH::ZERO_VECTOR_3D;
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
		attackChargeCount_ = 0;
		attackTimeCount_ = 0;
		findOutReactionCount_ = 0;
		moveAngleChangeCount_ = 0;
		knockBackTimeCount_ = 0;
		scoreNum_ = ENEMY_MONSTER::ADD_SCORE_NUM;
		state_ = ENEMY::STATE::SEARCH;
		isAlive_ = false;
		hp_ = 3;
		radius_ = ENEMY_BOMBER::RADIUS;
		pos_ = ENEMY_MONSTER::INIT_POS;
		velocity_ = MY_MATH::ZERO_VECTOR_3D;
		rot_ = MY_MATH::ZERO_VECTOR_3D;
		dir_ = { 0.0f,0.0f,1.0f };

		dir_ *= Matrix3D::GetYawMatrix(MyMath::DegreesToRadian(GetRand(359)));

		rot_.y = atan2f(-dir_.x, -dir_.z);

		pos_ *= Matrix3D::GetYawMatrix(MyMath::DegreesToRadian(GetRand(359)));

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

		//ノックバック状態の処理
		if (state_ == ENEMY::STATE::KNOCK_BACK)
		{
			//ノックバック状態の処理が120回されていたら
			if (knockBackTimeCount_ > 120)
			{
				knockBackTimeCount_ = 0;
				isAlive_ = false;
				state_ = ENEMY::STATE::SEARCH;
				pos_ = MY_MATH::ZERO_VECTOR_3D;
				rot_ = MY_MATH::ZERO_VECTOR_3D;
				velocity_ = MY_MATH::ZERO_VECTOR_3D;

				//位置・角度設定
				MV1SetPosition(handle_, pos_);
				MV1SetRotationXYZ(handle_, rot_);

				return;
			}

			//ノックバック状態の時間計測
			++knockBackTimeCount_;


			//自分の速度を位置に加算し、上に上昇させる
			pos_ += velocity_;
			pos_.y += ENEMY_MONSTER::KNOCKBACK_Y_POWER;

			rot_.x += MY_MATH::PI_OVER_TEN;

			//位置・角度設定
			MV1SetPosition(handle_, pos_);
			MV1SetRotationXYZ(handle_, rot_);

			return;
		}

		//重力をかけても地面にめり込まなければ処理をする
		pos_.y - ENEMY::GRAVITY >= ENEMY_MONSTER::GROUND_POS_Y ? pos_.y -= ENEMY::GRAVITY : pos_.y = ENEMY_MONSTER::GROUND_POS_Y;

		//プレイヤー探索状態
		if (state_ == ENEMY::STATE::SEARCH)
		{
			velocity_ += dir_.Normalize() * 0.125f;

			//一定の速度を超えたら
			if (velocity_.SquareL2Norm() > ENEMY_MONSTER::MAX_SPEED * ENEMY_MONSTER::MAX_SPEED)
			{
				velocity_ = velocity_.Normalize() * ENEMY_MONSTER::MAX_SPEED;
			}

			pos_ += velocity_;

			if (MyMath::Abs(pos_.x) > ENEMY_MONSTER::MAX_POS_X_Z)
			{
				pos_.x = 0.0f < pos_.x ? ENEMY_MONSTER::MAX_POS_X_Z : -ENEMY_MONSTER::MAX_POS_X_Z;
				dir_ = -dir_;
				velocity_ = -velocity_;
			}

			if (MyMath::Abs(pos_.z) > ENEMY_MONSTER::MAX_POS_X_Z)
			{
				pos_.z = 0.0f < pos_.z ? ENEMY_MONSTER::MAX_POS_X_Z : -ENEMY_MONSTER::MAX_POS_X_Z;

				dir_ = -dir_;
				velocity_ = -velocity_;
			}

			//位置・角度設定
			MV1SetPosition(handle_, pos_);
			MV1SetRotationXYZ(handle_, rot_);


			//移動する角度切り替え時間計測
			++moveAngleChangeCount_;

			if (moveAngleChangeCount_ >= ENEMY_MONSTER::MOVEANGLE_CHANGE_MAX_NUM)
			{
				dir_ = dir_ * Matrix3D::GetYawMatrix(MyMath::DegreesToRadian(GetRand(359)));

				//角度切り替え設定
				rot_.y = atan2f(-dir_.x, -dir_.z);

				//速度初期化
				velocity_ = MY_MATH::ZERO_VECTOR_3D;

				//移動する角度切り替え時間初期化
				moveAngleChangeCount_ = 0;
			}

			//プレイヤーを視界の範囲内に居ないなら関数脱出
			if (Vector3D::Dot(dir_, playerPos) < 0.0f)
			{
				return;
			}

			//プレイヤーが近くにいたら
			if ((playerPos - pos_).SquareL2Norm() < ENEMY_MONSTER::SQUARE_FIND_OUT_RANGE)
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
			//見つけた時の反応時間計測
			++findOutReactionCount_;

			//プレイヤーのほうを向く
			dir_ = playerPos - pos_;
			dir_.y = 0.0f;
			rot_.y = atan2f(-dir_.x, -dir_.z);

			MV1SetRotationXYZ(handle_, rot_);

			//一定時間経ったら追いかけ状態に移行
			if (findOutReactionCount_ >= ENEMY_MONSTER::REACTION_MAX_TIME)
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
			dir_.y = 0.0f;

			//単位ベクトルにしてスカラー倍し速度に加算
			velocity_ += dir_.Normalize() * ENEMY_MONSTER::CHASE_SPEED;

			//位置に加算
			pos_ += velocity_;

			rot_.y = atan2f(-dir_.x, -dir_.z);

			//一定距離まで近づいたら
			if (dir_.SquareL2Norm() < ENEMY_MONSTER::SQUARE_FIND_OUT_RANGE)
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
			dir_ = playerPos - pos_;
			dir_.y = 0.0f;

			rot_.y = atan2f(-dir_.x, -dir_.z);

			//位置・角度設定
			MV1SetPosition(handle_, pos_);
			MV1SetRotationXYZ(handle_, rot_);

			//攻撃溜め時間計測
			++attackChargeCount_;

			if (attackChargeCount_ > ENEMY_MONSTER::ATTACK_CHARGE_MAX_TIME)
			{
				//攻撃状態に移行
				state_ = ENEMY::STATE::ATTACK;

				//最高速度に設定
				velocity_ = dir_.Normalize() * ENEMY_MONSTER::MAX_SPEED * 2.0f;

				//攻撃溜め時間初期化
				attackChargeCount_ = 0;

				return;
			}

			return;
		}

		//攻撃状態
		if (state_ == ENEMY::STATE::ATTACK)
		{
			pos_ += velocity_;

			if (MyMath::Abs(pos_.x) > ENEMY_MONSTER::MAX_POS_X_Z)
			{
				pos_.x = 0.0f < pos_.x ? ENEMY_MONSTER::MAX_POS_X_Z : -ENEMY_MONSTER::MAX_POS_X_Z;
				dir_ = -dir_;
				velocity_ = -velocity_;
			}

			if (MyMath::Abs(pos_.z) > ENEMY_MONSTER::MAX_POS_X_Z)
			{
				pos_.z = 0.0f < pos_.z ? ENEMY_MONSTER::MAX_POS_X_Z : -ENEMY_MONSTER::MAX_POS_X_Z;

				dir_ = -dir_;
				velocity_ = -velocity_;
			}

			//位置・角度設定
			MV1SetPosition(handle_, pos_);
			MV1SetRotationXYZ(handle_, rot_);

			//攻撃時間計測
			++attackTimeCount_;

			if (attackTimeCount_ > ENEMY_MONSTER::ATTACK_MAX_TIME)
			{
				state_ = ENEMY::STATE::SEARCH;

				attackTimeCount_ = 0;
			}

			return;
		}
	}

	//描画処理関数
	void EnemyMonster::Draw(void)
	{
		if (!isAlive_)
		{
			return;
		}

		MV1DrawModel(handle_);

		DrawLine3D(pos_, pos_ + dir_.Normalize() * ENEMY_MONSTER::FIND_OUT_RANGE, GetColor(255, 0, 0));

	}

	//出現処理関数
	void EnemyMonster::AppearanceRequest(void)
	{
		//初期位置設定
		pos_ = Matrix3D::GetYawMatrix(MyMath::DegreesToRadian(static_cast<float>(GetRand(359))))
			* Matrix3D::GetTranslateMatrix(ENEMY_MONSTER::INIT_POS) * MY_MATH::ZERO_VECTOR_3D;

		//死者蘇生
		isAlive_ = true;

		//位置・角度設定
		MV1SetPosition(handle_, pos_);
		MV1SetRotationXYZ(handle_, rot_);
	}


	//当たり判定処理
	void EnemyMonster::HitCalculation(void)
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
