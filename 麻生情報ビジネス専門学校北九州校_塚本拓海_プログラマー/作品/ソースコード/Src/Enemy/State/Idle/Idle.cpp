#include "Idle.h"
#include "Math/MyMath.h"

namespace BOUDAMA
{
	//初期化処理関数
	void Idle::Enter(void)
	{
		if (const auto& owner = owner_.lock())
		{
			owner->SetVelocity(MyMath::ZERO_VECTOR_3D);
		}

		isTransitionToNextState_ = false;
	}

	//行動処理関数
	void Idle::Execute(void)
	{
		//-1の場合は、これ以上何もしない完全に停止させている状態
		if(maxIdleTime_ == -1)
		{
			//何もしない
			return;
		}

		++idleTimeCount_;

		if (maxIdleTime_ <= idleTimeCount_)
		{
			isTransitionToNextState_ = true;
		}
	}
}
