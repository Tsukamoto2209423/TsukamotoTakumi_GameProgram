#include "FindOut.h"
#include "Math/MyMath.h"

namespace BOUDAMA
{
	//初期化処理関数
	void FindOut::Enter(void)
	{
		if (const auto& owner = owner_.lock())
		{
			owner->SetVelocity(MyMath::ZERO_VECTOR_3D);
		}

		isTransitionToNextState_ = false;
	}

	//行動処理関数
	void FindOut::Execute(void)
	{
		if (const auto& owner = owner_.lock())
		{
			owner->SetDir(owner->GetTargetPosition() - owner->GetPos());

			//角度切り替え設定
			owner->RotateYaw(owner->GetDir());
		}
	}
}