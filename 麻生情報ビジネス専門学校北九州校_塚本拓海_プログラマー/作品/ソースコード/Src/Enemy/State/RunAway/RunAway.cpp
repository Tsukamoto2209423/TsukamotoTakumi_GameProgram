#include "RunAway.h"
#include "Math/MyMath.h"

namespace BOUDAMA
{
	namespace RUN_AWAY
	{
		//この時間以上経過したら逃走状態を解除する
		constexpr int CALM_DOWN_TIME = 360;
	}

	//初期化処理関数
	void RunAway::Enter(void)
	{
		if (const auto& owner = owner_.lock())
		{
			owner->SetVelocity(MyMath::ZERO_VECTOR_3D);
			owner->SetRot(MyMath::ZERO_VECTOR_3D);
		}

		isTransitionToNextState_ = false;
	}

	//行動処理関数
	void RunAway::Execute(void)
	{
		if (const auto& owner = owner_.lock())
		{
			//逃走する方向のベクトル
			Vector3D runAwayDirection = owner->GetPos() - owner->GetTargetPosition();

			//上方向には移動させない
			runAwayDirection.y = 0.0f;

			owner->SetDir(runAwayDirection.Normalize());
			owner->SetVelocity(owner->GetDir() * moveSpeed_);

			//角度切り替え設定
			owner->RotateYaw(owner->GetDir());

			//移動させる
			owner->MovePos(owner->GetVelocity());

			++timeCount_;

			//一定時間逃走したら解除
			if (RUN_AWAY::CALM_DOWN_TIME < timeCount_)
			{
				timeCount_ = 0;
				isTransitionToNextState_ = true;
			}

		}
	}
}
