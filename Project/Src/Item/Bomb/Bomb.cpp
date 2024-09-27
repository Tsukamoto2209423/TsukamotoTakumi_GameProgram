#include "Bomb.h"
#include <Math/MyMath.h>

//初期化処理関数
void Bomb::Init(void)
{
	//初期化
	handle_ = -1;
	state_ = BOMB::STATE::NORMAL;
	isAlive_ = true;
	hp_ = 1;
	radius_ = BOMB::RADIUS;
	pos_ = MY_MATH::ZERO_VECTOR_3D;
	velocity_ = MY_MATH::ZERO_VECTOR_3D;
	rot_ = MY_MATH::ZERO_VECTOR_3D;

	countExplodeTimeLimit_ = BOMB::MAX_EXPLODE_TIME_LIMIT;
}

//行動処理関数
void Bomb::Step(void)
{
	(this->*MoveFunctionPointer[state_])();
}

//出現処理関数
void Bomb::AppearanceRequest(void)
{
	isAlive_ = true;

	if (owner_.expired())
	{
		pos_ = { BOMB::INIT_POS_X_Z + GetRand(BOMB::INIT_POS_XZ_RAND_MAX_NUM),
			0.0f,
			BOMB::INIT_POS_X_Z + GetRand(BOMB::INIT_POS_XZ_RAND_MAX_NUM) };
	}
}

//アイテムの効果実行
void Bomb::EffectExecute(const std::shared_ptr<Object>& subjectObject)
{
	subjectObject->SubHP(BOMB::ATTACK_POWER);
}

//当たったときの処理
void Bomb::HitCalculation(void)
{
	state_ = BOMB::STATE::EXPLOSION;
	isAlive_ = false;
}

void Bomb::MoveNormal(void)
{
	//生存していなければ実行しない
	if (!isAlive_)
	{
		return;
	}

	//爆発するまでの時間計測
	--countExplodeTimeLimit_;

	//爆発までのカウントダウンが0になったら
	if (countExplodeTimeLimit_ <= 0)
	{
		//その場で爆発状態に遷移
		state_ = BOMB::STATE::EXPLOSION;
		isAlive_ = false;

		countExplodeTimeLimit_ = BOMB::MAX_EXPLODE_TIME_LIMIT;

		radius_ = BOMB::EXPLODE_RADIUS;

		return;
	}

	//誰かが自分自身を取得したときの処理
	if (!owner_.expired())
	{
		const auto& owner = owner_.lock();

		pos_ = owner->GetPos() + BOMB::HELD_UP_DISTANCE;
		rot_.y = owner->GetRotY();

		//座標設定
		MV1SetPosition(handle_, pos_);
		MV1SetRotationXYZ(handle_, rot_);

		return;
	}

	//Y軸のぐるぐる回転する処理
	rot_.y = rot_.y >= MY_MATH::TWO_PI - MY_MATH::PI_OVER_TWENTY ? 0.0f : rot_.y + MY_MATH::PI_OVER_TWENTY;

	//座標設定
	MV1SetPosition(handle_, pos_);
	MV1SetRotationXYZ(handle_, rot_);
}

//投げられたときの処理
void Bomb::MoveThrow(void)
{
	//爆発するまでの時間計測
	--countExplodeTimeLimit_;

	//dir_.x = -sinf(rot_.y) * BOMB::THROW_SPEED;
	//dir_.z = -cosf(rot_.y) * BOMB::THROW_SPEED;

	pos_ += dir_;

	dir_ *= 0.9f;

	//重力処理
	pos_.y - BOMB::GRAVITY > BOMB::GROUND_POS ? pos_.y -= BOMB::GRAVITY : pos_.y = BOMB::GROUND_POS;


	//画面外に出た場合、死亡判定
	if (MyMath::Abs(pos_.x) > BOMB::MAX_POS_X_Z || MyMath::Abs(pos_.z) > BOMB::MAX_POS_X_Z)
	{
		isAlive_ = false;
		dir_ = MY_MATH::ZERO_VECTOR_3D;
	}

	//位置・角度設定
	MV1SetPosition(handle_, pos_);
	MV1SetRotationXYZ(handle_, rot_);
}

//爆発しているときの処理
void Bomb::MoveExplosion(void)
{
	//爆発中の時間計測
	++explosionTime_;
	
	//爆発時間が最大まで行ったら
	if (explosionTime_ >= BOMB::MAX_EXPLOSION_TIME)
	{
		state_ = BOMB::STATE::NORMAL;
		explosionTime_ = 0;
		radius_ = BOMB::RADIUS;
	}
}
