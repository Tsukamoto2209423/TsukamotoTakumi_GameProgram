#include "RandomWalk.h"

#include "Math/MyMath.h"
#include "Matrix/Matrix3D.h"

namespace BOUDAMA
{
	//�����������֐�
	void RandomWalk::Enter(void)
	{
		if (const auto& owner = owner_.lock())
		{
			owner->SetDir(owner->GetDir() * Matrix3D::GetYawMatrix(MyMath::DegreesToRadian(GetRand(359))));
			owner->SetVelocity(MyMath::ZERO_VECTOR_3D);
			owner->SetRot(MyMath::ZERO_VECTOR_3D);
			owner->RotateYaw(owner->GetDir());
		}

		isTransitionToNextState_ = false;
	}

	//�s�������֐�
	void RandomWalk::Execute(void)
	{
		if (const auto& owner = owner_.lock())
		{
			owner->AddVelocity(owner->GetDir() * moveSpeed_);

			//���̑��x�𒴂�����
			if (owner->GetVelocity().SquareL2Norm() > squareMaxMoveSpeed_)
			{
				owner->SetVelocity(owner->GetVelocity().Normalize() * maxMoveSpeed_);
			}

			owner->MovePos(owner->GetVelocity());

			//�[�ɍs�����甽�΂�����
			if (maxMovementRange_ < MyMath::Abs(owner->GetPosX()) || maxMovementRange_ < MyMath::Abs(owner->GetPosZ()))
			{
				owner->SetDir(owner->GetDir().Inverse());
				owner->SetVelocity(owner->GetVelocity().Inverse());
				owner->RotateYaw(owner->GetDir());
			}

			//�ړ�����p�x�؂�ւ����Ԍv��
			++directionChangeTimeCount_;

			if (directionChangeInterval_ <= directionChangeTimeCount_)
			{
				owner->SetDir(Vector3D(0.0f, 0.0f, 1.0f) * Matrix3D::GetYawMatrix(MyMath::DegreesToRadian(GetRand(359))));

				//�p�x�؂�ւ��ݒ�
				owner->RotateYaw(owner->GetDir());

				//���x������
				owner->SetVelocity(MyMath::ZERO_VECTOR_3D);

				//�ړ�����p�x�؂�ւ����ԏ�����
				directionChangeTimeCount_ = 0;
			}

			const Vector3D normalizeTargetPos = owner->GetTargetPosition().Normalize();

			//�v���C���[�����E�͈͓̔��ɋ��Ȃ��Ȃ�֐��E�o
			if (0.0f < Vector3D::Dot(owner->GetDir(), normalizeTargetPos))
			{
				return;
			}

			//�v���C���[���߂��ɂ�����
			if ((owner->GetTargetPosition() - owner->GetPos()).SquareL2Norm() < squareFindOutRange_)
			{
				//�v���C���[������ԂɈڍs
				nextStateName_ = ENEMY_STATE::FIND_OUT;
				isTransitionToNextState_ = true;

				return;
			}
		}
	}
}