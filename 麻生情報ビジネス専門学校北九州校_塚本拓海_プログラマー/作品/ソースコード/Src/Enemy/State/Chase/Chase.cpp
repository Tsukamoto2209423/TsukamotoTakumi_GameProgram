#include "Chase.h"
#include "Math/MyMath.h"

namespace BOUDAMA
{
	//�����������֐�
	void Chase::Enter(void)
	{
		if (const auto& owner = owner_.lock())
		{
			owner->SetVelocity(MyMath::ZERO_VECTOR_3D);
			owner->SetRot(MyMath::ZERO_VECTOR_3D);
		}

		isTransitionToNextState_ = false;
	}

	//�s�������֐�
	void Chase::Execute(void)
	{
		if (const auto& owner = owner_.lock())
		{
			owner->SetDir((owner->GetTargetPosition() - owner->GetPos()).Normalize());
			owner->SetVelocity(owner->GetDir() * moveSpeed_);

			//�p�x�؂�ւ��ݒ�
			owner->RotateYaw(owner->GetDir());

			//�ړ�������
			owner->MovePos(owner->GetVelocity());	
		}
	}
}
