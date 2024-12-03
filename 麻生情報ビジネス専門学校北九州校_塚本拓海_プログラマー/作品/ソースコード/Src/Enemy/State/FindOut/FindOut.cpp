#include "FindOut.h"
#include "Math/MyMath.h"
#include "Enemy/EnemyFlyweightImage.h"
#include "Sound/Sound.h"

namespace BOUDAMA
{
	//初期化処理関数
	void FindOut::Enter(void)
	{
		if (const auto& owner = owner_.lock())
		{
			owner->SetVelocity(MyMath::ZERO_VECTOR_3D);
		}

		SoundManager::GetInstance()->PlaySoundData(SOUND::SE::FIND_OUT, DX_PLAYTYPE_BACK);

		isTransitionToNextState_ = false;
	}

	//行動処理関数
	void FindOut::Execute(void)
	{
		if (const auto& owner = owner_.lock())
		{
			owner->SetDir(owner->GetTargetPosition() - owner->GetPos());

			//角度切り替え設定
			owner->RotateYaw(owner->GetDir());

			//「！」の画像を表示する
			DrawBillboard3D(owner->GetPos() + exclamationMarkDistance_, 0.5f, 0.0f, 128.0f, 0.0f, EnemyFlyweightImage::GetImageHandle(FLYWEIGHT_IMAGE::EXCLAMATION), true);


			++reactionTimeCount_;

			if (maxReactionTimeCount_ < reactionTimeCount_)
			{
				owner->SetDir(owner->GetDir().Normalize());
				reactionTimeCount_ = 0;
				nextStateName_ = ENEMY_STATE::ATTACK;
				isTransitionToNextState_ = true;
			}
		}
	}
}
