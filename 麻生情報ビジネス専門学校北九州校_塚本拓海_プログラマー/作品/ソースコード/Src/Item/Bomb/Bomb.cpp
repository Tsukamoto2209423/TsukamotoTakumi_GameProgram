#include "Bomb.h"
#include <Math/MyMath.h>
#include "Effekseer/Effekseer.h"
#include <EffekseerParameter.h>

namespace BOUDAMA
{
	//初期化処理関数
	void Bomb::Init(void)
	{
		//初期化
		handle_ = -1;
		state_ = BOMB_STATE::NORMAL;
		isAlive_ = false;
		hp_ = 1;
		radius_ = BOMB::RADIUS;
		pos_ = MyMath::ZERO_VECTOR_3D;
		velocity_ = MyMath::ZERO_VECTOR_3D;
		rot_ = MyMath::ZERO_VECTOR_3D;

		countExplodeTimeLimit_ = BOMB::MAX_EXPLODE_TIME_LIMIT;

		playerOnlyEffect_ = false;
	}

	//行動処理関数
	void Bomb::Step(void)
	{
		(this->*MoveFunctionPointer[state_])();
	}

	//描画処理関数
	void Bomb::Draw(void)
	{
		//生存している場合は描画
		if (isAlive_ && state_ != BOMB_STATE::EXPLOSION)
		{
			MV1DrawModel(handle_);
		}
	}

	//出現処理関数
	void Bomb::AppearanceRequest(void)
	{
		isAlive_ = true;
		Ignite();
	}

	//アイテムの効果実行
	void Bomb::EffectExecute(const std::shared_ptr<Object>& targetObject)
	{
		targetObject->SubHP(BOMB::ATTACK_POWER);

		const Vector3D& myPosToTargetVector = targetObject->GetPos() - pos_;

		//距離に応じて与える速度ベクトルの長さを変える
		const Vector3D& addExplosionVelocity = (BOMB::EXPLOSION_BOOST / myPosToTargetVector.L2Norm()) * myPosToTargetVector;

		targetObject->AddVelocity(addExplosionVelocity);

		targetObject->HitCalculation();

		CEffekseerCtrl::Request(EFFECT::HIT_EFFECT, targetObject->GetPos(), false);
	}

	//当たったときの処理
	void Bomb::HitCalculation(void)
	{
		if (state_ != BOMB_STATE::EXPLOSION)
		{
			MoveTrigger();
		}
	}

	//爆弾に火をつける
	void Bomb::Ignite(void)
	{
		state_ = BOMB_STATE::IGNITION;
	}

	void Bomb::MoveNormal(void)
	{
		//生存していなければ実行しない
		if (!isAlive_)
		{
			return;
		}

		//Y軸のぐるぐる回転する処理
		rot_.y = rot_.y >= MyMath::TWO_PI - MyMath::PI_OVER_TWENTY ? 0.0f : rot_.y + MyMath::PI_OVER_TWENTY;

		//座標設定
		MV1SetPosition(handle_, pos_);
		MV1SetRotationXYZ(handle_, rot_);
	}

	//着火して投げられたときの処理
	void Bomb::MoveIgnition(void)
	{
		//爆発するまでの時間計測
		--countExplodeTimeLimit_;

		//爆発までのカウントダウンが0になったら
		if (countExplodeTimeLimit_ <= 0)
		{
			//その場で爆発状態に遷移
			state_ = BOMB_STATE::TRIGGER;

			countExplodeTimeLimit_ = BOMB::MAX_EXPLODE_TIME_LIMIT;

			radius_ = BOMB::EXPLODE_RADIUS;

			return;
		}

		pos_ += velocity_;

		velocity_.y -= BOMB::GRAVITY;

		//重力処理
		if (pos_.y <= BOMB::GROUND_POS)
		{
			pos_.y = BOMB::GROUND_POS;
			velocity_ = MyMath::ZERO_VECTOR_3D;
		}

		//画面外に出た場合、死亡判定
		if (MyMath::Abs(pos_.x) > BOMB::MAX_POS_X_Z || MyMath::Abs(pos_.z) > BOMB::MAX_POS_X_Z)
		{
			isAlive_ = false;
			velocity_ = MyMath::ZERO_VECTOR_3D;
		}

		//位置・角度設定
		MV1SetPosition(handle_, pos_);
		MV1SetRotationXYZ(handle_, rot_);
	}

	//爆発が起こった瞬間の状態
	void Bomb::MoveTrigger(void)
	{
		state_ = BOMB_STATE::EXPLOSION;
		CEffekseerCtrl::Request(EFFECT::EXPLOSION, pos_, false);
		radius_ = BOMB::EXPLODE_RADIUS;
	}

	//爆発しているときの処理
	void Bomb::MoveExplosion(void)
	{
		//爆発中の時間計測
		++explosionTime_;

		//爆発時間が最大まで行ったら
		if (BOMB::MAX_EXPLOSION_TIME <= explosionTime_)
		{
			isAlive_ = false;
			state_ = BOMB_STATE::NORMAL;
			explosionTime_ = 0;
			radius_ = BOMB::RADIUS;
		}
	}
}
