#include "Chase.h"
#include "Math/MyMath.h"

namespace BOUDAMA
{
	//‰Šú‰»ˆ—ŠÖ”
	void Chase::Enter(void)
	{
		if (const auto& owner = owner_.lock())
		{
			owner->SetVelocity(MyMath::ZERO_VECTOR_3D);
		}

		isTransitionToNextState_ = false;
	}

	//s“®ˆ—ŠÖ”
	void Chase::Execute(void)
	{
		if (const auto& owner = owner_.lock())
		{
			owner->SetDir((owner->GetTargetPosition() - owner->GetPos()).Normalize());
			owner->SetVelocity(owner->GetDir() * moveSpeed_);

			//Šp“xØ‚è‘Ö‚¦Ý’è
			owner->RotateYaw(owner->GetDir());

			//ˆÚ“®‚³‚¹‚é
			owner->MovePos(owner->GetVelocity());	
		}
	}
}
