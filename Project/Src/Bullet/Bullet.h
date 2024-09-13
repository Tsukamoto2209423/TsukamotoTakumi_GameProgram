#pragma once

#include "BulletBase.h"

namespace BULLET
{
	//モデルパス
	constexpr char PATH[] = "Data/Model/Bullet/Beta_Bullet.x";

	//弾速
	constexpr float SPEED = 70.5f;

	//最大数
	constexpr int MAX_NUM = 20;

	//寿命
	constexpr int MAX_LIFE_SPAN = 5;
	
	//半径
	constexpr float RADIUS = 60.0f;

	//X軸とZ軸で行ける最大の位置
	constexpr float MAX_POS_X_Z = 7000.0f;
}

//弾クラス
class Bullet : public BulletBase
{
public:
	//コンストラクタ
	Bullet();
	//デストラクタ
	~Bullet();

	//行動処理関数
	void Step(void) override;
};
