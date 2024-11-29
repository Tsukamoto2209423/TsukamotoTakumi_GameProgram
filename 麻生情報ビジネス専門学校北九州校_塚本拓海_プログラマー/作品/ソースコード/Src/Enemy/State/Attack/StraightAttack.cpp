#include "StraightAttack.h"
#include "Math/MyMath.h"
#include "Enemy/EnemyParameter.h"

namespace BOUDAMA
{
	//‰Šú‰»ˆ—ŠÖ”
	void StraightAttack::Enter(void)
	{
		if (const auto& owner = owner_.lock())
		{
			owner->SetVelocity(owner->GetDir() * MONSTER::ATTACK_SPEED);
			owner->SetIsInvincible(true);
		}

		isTransitionToNextState_ = false;
	}

	//s“®ˆ—ŠÖ”
	void StraightAttack::Execute(void)
	{
		if (const auto& owner = owner_.lock())
		{
			owner->MovePos(owner->GetVelocity());

			if (MyMath::Abs(owner->GetPosX()) > ENEMY_MANAGER::MAX_POS_X_Z)
			{
				owner->SetPosX(0.0f < owner->GetPosX() ? ENEMY_MANAGER::MAX_POS_X_Z : -ENEMY_MANAGER::MAX_POS_X_Z);
				owner->SetDir(owner->GetDir().Inverse());
				owner->SetVelocity(owner->GetVelocity().Inverse());
				//Šp“xØ‚è‘Ö‚¦İ’è
				owner->RotateYaw(owner->GetDir());

			}

			if (MyMath::Abs(owner->GetPosZ()) > ENEMY_MANAGER::MAX_POS_X_Z)
			{
				owner->SetPosZ(0.0f < owner->GetPosZ() ? ENEMY_MANAGER::MAX_POS_X_Z : -ENEMY_MANAGER::MAX_POS_X_Z);
				owner->SetDir(owner->GetDir().Inverse());
				owner->SetVelocity(owner->GetVelocity().Inverse());
				//Šp“xØ‚è‘Ö‚¦İ’è
				owner->RotateYaw(owner->GetDir());

			}

			//UŒ‚ŠÔŒv‘ª
			++attackTimeCount_;

			if (maxAttackTime_ <= attackTimeCount_)
			{
				owner->SetVelocity(MyMath::ZERO_VECTOR_3D);
				nextStateName_ = ENEMY_STATE::RANDOM_WALK;
				owner->SetIsInvincible(false);

				attackTimeCount_ = 0;
				isTransitionToNextState_ = true;;
			}

		}
	}
}
