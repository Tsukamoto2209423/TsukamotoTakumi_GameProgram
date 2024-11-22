#include "KnockBack.h"
#include <Math/MyMath.h>

namespace BOUDAMA
{
	//初期化処理関数
	void KnockBack::Enter(void)
	{
		if (const auto& owner = owner_.lock())
		{
			Vector3D knockBackDirection = owner->GetPos() - owner->GetTargetPosition();
			owner->SetVelocity(knockBackDirection.Normalize() * KNOCK_BACK::SPEED);
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

				nextStateName_ = ENEMY_STATE::CHASE;
				isTransitionToNextState_ = true;

				return;
			}

			//自分の速度を位置に加算し、上に上昇させる
			Vector3D velocity = owner->GetVelocity();
			velocity.y += KNOCK_BACK::SPEED;
			owner->MovePos(velocity);

			//ノックバック状態の時間計測
			++timeCount_;
		}
	}

}