#include "BigBullet.h"
#include "Math/MyMath.h"
#include "Player/PlayerParameter.h"

//コンストラクタ
BigBullet::BigBullet(void)
{
	//初期化
	handle_ = -1;
	isAlive_ = false;
	lifeSpan_ = 0;
	radius_ = BIG_BULLET::RADIUS;
	pos_ = MY_MATH::ZERO_VECTOR_3D;
	dir_ = MY_MATH::ZERO_VECTOR_3D;
	velocity_ = MY_MATH::ZERO_VECTOR_3D;
}

//デストラクタ
BigBullet::~BigBullet(void)
{
	//破棄処理
}

//読み込み処理関数
void BigBullet::Load(int origineHandle)
{
	if (handle_ == -1)
	{
		handle_ = MV1DuplicateModel(origineHandle);
		MV1SetScale(handle_, { 1.3f,1.3f,1.3f });
	}
}

//行動処理関数
void BigBullet::Step(void)
{
	//弾を動かす
	dir_.x = -sinf(rot_.y) * BIG_BULLET::SPEED;
	dir_.z = -cosf(rot_.y) * BIG_BULLET::SPEED;

	pos_ += dir_;

	++lifeSpan_;

	//画面外に出たか寿命が尽きた場合、死亡判定
	if (MyMath::Abs(pos_.x) > BIG_BULLET::MAX_POS_X_Z || MyMath::Abs(pos_.z) > BIG_BULLET::MAX_POS_X_Z || 
		lifeSpan_ >= BIG_BULLET::MAX_LIFE_SPAN)
	{
		isAlive_ = false;
		lifeSpan_ = 0;
		dir_ = MY_MATH::ZERO_VECTOR_3D;
	}

	//座標設定
	MV1SetPosition(handle_, pos_);
}

//当たり判定処理
void BigBullet::HitCalculation(void)
{
	//死亡処理
	isAlive_ = false;
	pos_ = MY_MATH::ZERO_VECTOR_3D;
	radius_ = 50.0f;
}
