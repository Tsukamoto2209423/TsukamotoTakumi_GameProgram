#include "Corpse.h"
#include "Math/MyMath.h"

namespace BOUDAMA
{
	//初期化処理関数
	void Corpse::Enter(void)
	{
		if (const auto& owner = owner_.lock())
		{
			Vector3D knockBackDirection = owner->GetPos() - owner->GetTargetPosition();
			owner->SetVelocity(knockBackDirection.Normalize() * CORPSE::SPEED);
		}

		isTransitionToNextState_ = false;
	}

	//行動処理関数
	void Corpse::Execute(void)
	{
		if (const auto& owner = owner_.lock())
		{
			//死体状態の処理が最大回数されていたら
			if (CORPSE::MAX_CORPSE_TIME_COUNT < timeCount_)
			{
				//初期化処理
				timeCount_ = 0;

				owner->SetIsActive(false);

				return;
			}

			//自分の速度を位置に加算し、斜め上に移動させる
			Vector3D velocity = owner->GetVelocity();
			velocity.y += CORPSE::SPEED;
			owner->MovePos(velocity);

			//X軸回転させる
			owner->RotatePitch(MyMath::INVERSE_TWO_PI);

			//死体状態の時間計測
			++timeCount_;
		}
	}
}
