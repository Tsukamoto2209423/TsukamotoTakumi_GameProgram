#include "FindOut.h"
#include "Math/MyMath.h"

namespace BOUDAMA
{
	//‰Šú‰»ˆ—ŠÖ”
	void FindOut::Enter(void)
	{
		if (const auto& owner = owner_.lock())
		{
			owner->SetVelocity(MyMath::ZERO_VECTOR_3D);
		}

		isTransitionToNextState_ = false;
	}

	//s“®ˆ—ŠÖ”
	void FindOut::Execute(void)
	{
		if (const auto& owner = owner_.lock())
		{
			owner->SetDir(owner->GetTargetPosition() - owner->GetPos());

			//Šp“xØ‚è‘Ö‚¦Ý’è
			owner->RotateYaw(owner->GetDir());
		}
	}
}