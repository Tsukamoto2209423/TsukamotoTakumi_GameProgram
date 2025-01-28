#include "RunAway.h"
#include "Math/MyMath.h"

namespace BOUDAMA
{
	namespace RUN_AWAY
	{
		//���̎��Ԉȏ�o�߂����瓦����Ԃ���������
		constexpr int CALM_DOWN_TIME = 360;
	}

	//�����������֐�
	void RunAway::Enter(void)
	{
		if (const auto& owner = owner_.lock())
		{
			owner->SetVelocity(MyMath::ZERO_VECTOR_3D);
			owner->SetRot(MyMath::ZERO_VECTOR_3D);
		}

		isTransitionToNextState_ = false;
	}

	//�s�������֐�
	void RunAway::Execute(void)
	{
		if (const auto& owner = owner_.lock())
		{
			//������������̃x�N�g��
			Vector3D runAwayDirection = owner->GetPos() - owner->GetTargetPosition();

			//������ɂ͈ړ������Ȃ�
			runAwayDirection.y = 0.0f;

			owner->SetDir(runAwayDirection.Normalize());
			owner->SetVelocity(owner->GetDir() * moveSpeed_);

			//�p�x�؂�ւ��ݒ�
			owner->RotateYaw(owner->GetDir());

			//�ړ�������
			owner->MovePos(owner->GetVelocity());

			++timeCount_;

			//��莞�ԓ������������
			if (RUN_AWAY::CALM_DOWN_TIME < timeCount_)
			{
				timeCount_ = 0;
				isTransitionToNextState_ = true;
			}

		}
	}
}
