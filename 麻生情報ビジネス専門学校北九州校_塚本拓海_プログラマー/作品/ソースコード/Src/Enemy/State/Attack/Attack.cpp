#include "Attack.h"
#include "Math/MyMath.h"
#include "Enemy/EnemyParameter.h"

namespace BOUDAMA
{
	//初期化処理関数
	void Attack::Enter(void)
	{
		if (const auto& owner = owner_.lock())
		{
			owner->SetVelocity(owner->GetDir().Normalize() * MONSTER::ATTACK_SPEED);
		}

		isTransitionToNextState_ = false;
	}

	//行動処理関数
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

			//攻撃時間計測
			++attackTimeCount_;

			if (attackTimeCount_ > MONSTER::ATTACK_MAX_TIME)
			{
				nextStateName_ = ENEMY_STATE::SEARCH;

				attackTimeCount_ = 0;
			}

		}
	}
}
