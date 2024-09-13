#include "Bullet.h"
#include "Math/MyMath.h"
#include "Common/Common.h"
#include "Player/PlayerParameter.h"

//コンストラクタ
Bullet::Bullet(void)
{
	//初期化
	handle_ = -1;
	isAlive_ = false;
	radius_ = BULLET::RADIUS;
	lifeSpan_ = 0;
	pos_ = MY_MATH::ZERO_VECTOR_3D;
	dir_ = MY_MATH::ZERO_VECTOR_3D;
	velocity_ = MY_MATH::ZERO_VECTOR_3D;
}

//デストラクタ
Bullet::~Bullet(void)
{
	//破棄処理
}

//行動処理関数
void Bullet::Step(void)
{
	//弾を動かす
	dir_.x = -sinf(rot_.y) * BULLET::SPEED;
	dir_.z = -cosf(rot_.y) * BULLET::SPEED;

	pos_ += dir_;

	++lifeSpan_;

	//画面外に出た場合、死亡判定
	if (MyMath::Abs(pos_.x) > 3000.0f || MyMath::Abs(pos_.z) > 3000.0f || lifeSpan_ >= BULLET::MAX_LIFE_SPAN)
	{
		isAlive_ = false;
		lifeSpan_ = 0;
		dir_ = MY_MATH::ZERO_VECTOR_3D;
	}

	//座標設定
	MV1SetPosition(handle_,pos_);
}
