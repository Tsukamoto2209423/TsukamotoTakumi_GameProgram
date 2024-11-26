#include "Attack.h"
#include "Math/MyMath.h"
#include "Enemy/EnemyParameter.h"

namespace BOUDAMA
{
	//‰Šú‰»ˆ—ŠÖ”
	void Attack::Enter(void)
	{
		if (const auto& owner = owner_.lock())
		{
			owner->SetVelocity(owner->GetDir().Normalize() * MONSTER::ATTACK_SPEED);
		}

		isTransitionToNextState_ = false;
	}

	//s“®ˆ—ŠÖ”
	void Attack::Execute(void)
	{
		if (const auto& owner = owner_.lock())
		{
			owner->MovePos(owner->GetVelocity());

			if (MyMath::Abs(owner->GetPosX()) > MONSTER::MAX_POS_X_Z)
			{
				owner->SetPosX(0.0f < owner->GetPosX() ? MONSTER::MAX_POS_X_Z : -MONSTER::MAX_POS_X_Z);
				owner->GetDir().Inverse();
				owner->GetVelocity().Inverse();
			}

			if (MyMath::Abs(owner->GetPosZ()) > MONSTER::MAX_POS_X_Z)
			{
				owner->SetPosZ(0.0f < owner->GetPosZ() ? MONSTER::MAX_POS_X_Z : -MONSTER::MAX_POS_X_Z);
				owner->GetDir().Inverse();
				owner->GetVelocity().Inverse();
			}

			//UŒ‚ŽžŠÔŒv‘ª
			++attackTimeCount_;

			if (attackTimeCount_ > MONSTER::ATTACK_MAX_TIME)
			{
				nextStateName_ = ENEMY_STATE::SEARCH;

				attackTimeCount_ = 0;
			}

		}
	}
}
