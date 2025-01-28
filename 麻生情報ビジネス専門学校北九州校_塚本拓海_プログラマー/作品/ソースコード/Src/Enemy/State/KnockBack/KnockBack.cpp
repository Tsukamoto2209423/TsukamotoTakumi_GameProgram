#include "KnockBack.h"
#include <Math/MyMath.h>

namespace BOUDAMA
{
	namespace KNOCK_BACK
	{
		constexpr float SPEED = 10.0f;
		constexpr float UP_SPEED = 11.5f;
		constexpr float GRAVITY = 0.5f;
	}

	//�����������֐�
	void KnockBack::Enter(void)
	{
		if (const auto& owner = owner_.lock())
		{
			Vector3D knockBackDirection = owner->GetPos() - owner->GetTargetPosition();
			knockBackDirection = knockBackDirection.Normalize() * KNOCK_BACK::SPEED;
			knockBackDirection.y += KNOCK_BACK::UP_SPEED;
			owner->SetVelocity(knockBackDirection);

			owner->SetIsCollisionEnabled(false);
		}

		isTransitionToNextState_ = false;
	}

	//�s�������֐�
	void KnockBack::Execute(void)
	{
		if (const auto& owner = owner_.lock())
		{
			//�����̑��x���ʒu�ɉ��Z
			owner->MovePos(owner->GetVelocity());

			owner->SubVelocity(Vector3D(0.0f, KNOCK_BACK::GRAVITY, 0.0f));

			//�m�b�N�o�b�N��Ԃ̎��Ԍv��
			++timeCount_;

			//�m�b�N�o�b�N��Ԃ̏������ő�񐔂���Ă�����
			if (maxTimeCount_ < timeCount_)
			{
				//����������
				timeCount_ = 0;

				isTransitionToNextState_ = true;
				owner->SetIsCollisionEnabled(true);

				return;
			}
		}
	}

}