#include "FindOut.h"
#include "Math/MyMath.h"
#include "Enemy/EnemyFlyweightImage.h"
#include "Sound/Sound.h"

namespace BOUDAMA
{
	//�����������֐�
	void FindOut::Enter(void)
	{
		if (const auto& owner = owner_.lock())
		{
			owner->SetVelocity(MyMath::ZERO_VECTOR_3D);
		}

		SoundManager::GetInstance()->PlaySoundData(SOUND::SE::FIND_OUT, DX_PLAYTYPE_BACK);

		isTransitionToNextState_ = false;
	}

	//�s�������֐�
	void FindOut::Execute(void)
	{
		if (const auto& owner = owner_.lock())
		{
			owner->SetDir(owner->GetTargetPosition() - owner->GetPos());

			//�p�x�؂�ւ��ݒ�
			owner->RotateYaw(owner->GetDir());

			//�u�I�v�̉摜��\������
			DrawBillboard3D(owner->GetPos() + exclamationMarkDistance_, 0.5f, 0.0f, 128.0f, 0.0f, EnemyFlyweightImage::GetImageHandle(FLYWEIGHT_IMAGE::EXCLAMATION), true);


			++reactionTimeCount_;

			if (maxReactionTimeCount_ < reactionTimeCount_)
			{
				owner->SetDir(owner->GetDir().Normalize());
				reactionTimeCount_ = 0;
				isTransitionToNextState_ = true;
			}
		}
	}
}
