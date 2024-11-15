#include "Chase.h"

namespace BOUDAMA
{
	//初期化処理関数
	void Chase::Enter(void)
	{

	}

	//行動処理関数
	void Chase::Execute(void)
	{
		if (const auto& owner = owner_.lock())
		{
			owner->AddVelocity(owner->GetDir());
			owner->MovePos(owner->GetVelocity());	
		}
	}
}
