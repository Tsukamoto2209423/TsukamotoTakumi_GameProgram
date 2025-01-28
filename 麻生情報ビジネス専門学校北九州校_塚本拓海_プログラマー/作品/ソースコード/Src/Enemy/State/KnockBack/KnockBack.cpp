#include "KnockBack.h"
#include <Math/MyMath.h>

namespace BOUDAMA
{
	namespace KNOCK_BACK
	{
		constexpr float SPEED = 10.0f;
		constexpr float UP_SPEED = 11.5f;
		constexpr float GRAVITY = 0.5f;
	}

	//初期化処理関数
	void KnockBack::Enter(void)
	{
		if (const auto& owner = owner_.lock())
		{
			Vector3D knockBackDirection = owner->GetPos() - owner->GetTargetPosition();
			knockBackDirection = knockBackDirection.Normalize() * KNOCK_BACK::SPEED;
			knockBackDirection.y += KNOCK_BACK::UP_SPEED;
			owner->SetVelocity(knockBackDirection);

			owner->SetIsCollisionEnabled(false);
		}

		isTransitionToNextState_ = false;
	}

	//行動処理関数
	void KnockBack::Execute(void)
	{
		if (const auto& owner = owner_.lock())
		{
			//自分の速度を位置に加算
			owner->MovePos(owner->GetVelocity());

			owner->SubVelocity(Vector3D(0.0f, KNOCK_BACK::GRAVITY, 0.0f));

			//ノックバック状態の時間計測
			++timeCount_;

			//ノックバック状態の処理が最大回数されていたら
			if (maxTimeCount_ < timeCount_)
			{
				//初期化処理
				timeCount_ = 0;

				isTransitionToNextState_ = true;
				owner->SetIsCollisionEnabled(true);

				return;
			}
		}
	}

}