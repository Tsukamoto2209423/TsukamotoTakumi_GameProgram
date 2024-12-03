#include "StraightAttack.h"
#include "Math/MyMath.h"
#include "Enemy/EnemyParameter.h"

namespace BOUDAMA
{
	//初期化処理関数
	void StraightAttack::Enter(void)
	{
		if (const auto& owner = owner_.lock())
		{
			owner->SetVelocity(owner->GetDir() * MONSTER::ATTACK_SPEED);
			owner->SetIsInvincible(true);
		}

		isTransitionToNextState_ = false;
	}

	//行動処理関数
	void StraightAttack::Execute(void)
	{
		if (const auto& owner = owner_.lock())
		{
			owner->MovePos(owner->GetVelocity());

			if (ENEMY_MANAGER::MAX_POS_X_Z < MyMath::Abs(owner->GetPosX()))
			{
				owner->SetPosX(0.0f < owner->GetPosX() ? ENEMY_MANAGER::MAX_POS_X_Z : -ENEMY_MANAGER::MAX_POS_X_Z);
				owner->SetDir(owner->GetDir().Inverse());
				owner->SetVelocity(owner->GetVelocity().Inverse());
				//角度切り替え設定
				owner->RotateYaw(owner->GetDir());

			}

			if (ENEMY_MANAGER::MAX_POS_X_Z < MyMath::Abs(owner->GetPosZ()))
			{
				owner->SetPosZ(0.0f < owner->GetPosZ() ? ENEMY_MANAGER::MAX_POS_X_Z : -ENEMY_MANAGER::MAX_POS_X_Z);
				owner->SetDir(owner->GetDir().Inverse());
				owner->SetVelocity(owner->GetVelocity().Inverse());
				//角度切り替え設定
				owner->RotateYaw(owner->GetDir());

			}

			//攻撃時間計測
			++attackTimeCount_;

			if (maxAttackTime_ <= attackTimeCount_)
			{
				owner->SetVelocity(MyMath::ZERO_VECTOR_3D);
				nextStateName_ = ENEMY_STATE::RANDOM_WALK;
				owner->SetIsInvincible(false);

				attackTimeCount_ = 0;
				isTransitionToNextState_ = true;
			}

		}
	}
}
