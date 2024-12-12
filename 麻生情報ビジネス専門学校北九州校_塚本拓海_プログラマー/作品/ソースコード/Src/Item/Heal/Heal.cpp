#include "Heal.h"

#include "DxLib.h"

#include <Item/ItemParameter.h>
#include <Math/MyMath.h>

namespace BOUDAMA
{
	void Heal::Init(void)
	{
		radius_ = HEAL::RADIUS;
		healValue_ = HEAL::HEAL_VALUE;
		isAlive_ = false;

		playerOnlyEffect_ = true;
	}

	//読み込み処理関数
	void Heal::Load(const int originalHandle)
	{
		if (handle_ == -1)
		{
			handle_ = MV1DuplicateModel(originalHandle);
		}

		MV1SetScale(handle_, VECTOR(0.5f, 0.5f, 0.5f));
	}

	void Heal::Step(void)
	{
		//生存していなければ実行しない
		if (!isAlive_)
		{
			return;
		}

		floatMotionTheta_ < MyMath::TWO_PI ? floatMotionTheta_ += MyMath::INVERSE_TWO_PI : floatMotionTheta_ = 0.0f;

		pos_.y += HEAL::FLOAT_MOTION_BOOST * std::sin(floatMotionTheta_);

		//座標設定
		MV1SetPosition(handle_, pos_);
		MV1SetRotationXYZ(handle_, rot_);
	}

	//描画処理関数
	void Heal::Draw(void)
	{
		//生存している場合は描画
		if (isAlive_)
		{
			MV1DrawModel(handle_);
		}

		DrawSphere3D(pos_, radius_, 16, GetColor(0, 255, 0), GetColor(0, 255, 255), false);
	}

	//出現処理関数
	void Heal::AppearanceRequest(void)
	{
		isAlive_ = true;

		pos_ = { HEAL::INIT_POS_X_Z + GetRand(BOMB::INIT_POS_XZ_RAND_MAX_NUM),
				HEAL::GROUND_POS,
				HEAL::INIT_POS_X_Z + GetRand(BOMB::INIT_POS_XZ_RAND_MAX_NUM) };

		//座標設定
		MV1SetPosition(handle_, pos_);
		MV1SetRotationXYZ(handle_, rot_);
	}

	//アイテムを使用した時の効果実行関数
	void Heal::EffectExecute(const std::shared_ptr<Object>& targetObject)
	{
		//HP回復
		targetObject->AddHP(healValue_);

		isAlive_ = false;
		pos_ = MyMath::ZERO_VECTOR_3D;
	}
}
