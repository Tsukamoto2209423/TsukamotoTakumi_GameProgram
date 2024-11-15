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
	}

	//行動処理関数
	void Idle::Execute(void)
	{
		//何もしない
	}
}
