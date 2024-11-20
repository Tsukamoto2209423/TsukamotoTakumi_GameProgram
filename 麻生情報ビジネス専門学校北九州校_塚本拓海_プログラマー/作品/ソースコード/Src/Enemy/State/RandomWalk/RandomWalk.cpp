#include "RandomWalk.h"

#include "Math/MyMath.h"
#include "Matrix/Matrix3D.h"

namespace BOUDAMA
{
	//初期化処理関数
	void RandomWalk::Enter(void)
	{
		if (const auto& owner = owner_.lock())
		{
			owner->GetDir().Normalize();
			owner->SetVelocity(MyMath::ZERO_VECTOR_3D);
		}

		isTransitionToNextState_ = false;
	}

	//行動処理関数
	void RandomWalk::Execute(void)
	{
		if (const auto& owner = owner_.lock())
		{
			owner->MovePos(owner->GetDir() * moveSpeed_);

			if (maxMovementRange_ < MyMath::Abs(owner->GetPosX()) || maxMovementRange_ < MyMath::Abs(owner->GetPosZ()))
			{
				owner->GetDir().Inverse();
				owner->GetVelocity().Inverse();
			}

			//移動する角度切り替え時間計測
			++directionChangeTimeCount_;

			if (directionChangeInterval_ <= directionChangeTimeCount_)
			{
				owner->SetDir(owner->GetDir() * Matrix3D::GetYawMatrix(MyMath::DegreesToRadian(GetRand(359))));

				//角度切り替え設定
				owner->RotateYaw(owner->GetDir());

				//速度初期化
				owner->SetVelocity(MyMath::ZERO_VECTOR_3D);

				//移動する角度切り替え時間初期化
				directionChangeTimeCount_ = 0;
			}
		}
	}
}