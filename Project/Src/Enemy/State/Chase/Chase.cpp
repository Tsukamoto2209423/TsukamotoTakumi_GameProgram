#include "Chase.h"

namespace BOUDAMA
{
	//‰Šú‰»ˆ—ŠÖ”
	void Chase::Enter(void)
	{

	}

	//s“®ˆ—ŠÖ”
	void Chase::Execute(void)
	{
		if (const auto& owner = owner_.lock())
		{
			owner->AddVelocity(owner->GetDir());
			owner->MovePos(owner->GetVelocity());	
		}
	}
}
