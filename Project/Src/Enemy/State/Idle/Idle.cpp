#include "Idle.h"
#include "Math/MyMath.h"

namespace BOUDAMA
{
	//‰Šú‰»ˆ—ŠÖ”
	void Idle::Enter(void)
	{
		if (const auto& owner = owner_.lock())
		{
			owner->SetVelocity(MyMath::ZERO_VECTOR_3D);
		}
	}

	//s“®ˆ—ŠÖ”
	void Idle::Execute(void)
	{
		//‰½‚à‚µ‚È‚¢
	}
}
