#include "KnockBack.h"
#include <Math/MyMath.h>

namespace BOUDAMA
{
	namespace KNOCK_BACK
	{
		constexpr float SPEED = 10.0f;
		constexpr float UP_SPEED = 3.0f;
	}

	//初期化処理関数
	void KnockBack::Enter(void)
	{
		if (const auto& owner = owner_.lock())
		{
			Vector3D knockBackDirection = owner->GetPos() - owner->GetTargetPosition();
			owner->SetVelocity(knockBackDirection.Normalize() * KNOCK_BACK::SPEED);

			owner->SetIsCollisionEnabled(false);
		}

		isTransitionToNextState_ = false;
	}

	//行動処理関数
	void KnockBack::Execute(void)
	{
		if (const auto& owner = owner_.lock())
		{
			//ノックバック状態の処理が最大回数されていたら
			if (maxTimeCount_ < timeCount_)
			{
				//初期化処理
				timeCount_ = 0;

				//追尾状態に遷移
				nextStateName_ = ENEMY_STATE::CHASE;
				isTransitionToNextState_ = true;
				owner->SetIsCollisionEnabled(true);

				return;
			}

			//自分の速度を位置に加算し、上に上昇させる
			Vector3D velocity = owner->GetVelocity();
			velocity.y += KNOCK_BACK::UP_SPEED;
			owner->MovePos(velocity);

			//ノックバック状態の時間計測
			++timeCount_;
		}
	}

}