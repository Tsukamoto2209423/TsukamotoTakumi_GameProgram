#include "RandomWalk.h"

#include "Math/MyMath.h"
#include "Matrix/Matrix3D.h"

namespace BOUDAMA
{
	//初期化処理関数
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

	//行動処理関数
	void RandomWalk::Execute(void)
	{
		if (const auto& owner = owner_.lock())
		{
			owner->AddVelocity(owner->GetDir() * moveSpeed_);

			//一定の速度を超えたら
			if (owner->GetVelocity().SquareL2Norm() > squareMaxMoveSpeed_)
			{
				owner->SetVelocity(owner->GetVelocity().Normalize() * maxMoveSpeed_);
			}

			owner->MovePos(owner->GetVelocity());

			//端に行ったら反対を向く
			if (maxMovementRange_ < MyMath::Abs(owner->GetPosX()) || maxMovementRange_ < MyMath::Abs(owner->GetPosZ()))
			{
				owner->SetDir(owner->GetDir().Inverse());
				owner->SetVelocity(owner->GetVelocity().Inverse());
				owner->RotateYaw(owner->GetDir());
			}

			//移動する角度切り替え時間計測
			++directionChangeTimeCount_;

			if (directionChangeInterval_ <= directionChangeTimeCount_)
			{
				owner->SetDir(Vector3D(0.0f, 0.0f, 1.0f) * Matrix3D::GetYawMatrix(MyMath::DegreesToRadian(GetRand(359))));

				//角度切り替え設定
				owner->RotateYaw(owner->GetDir());

				//速度初期化
				owner->SetVelocity(MyMath::ZERO_VECTOR_3D);

				//移動する角度切り替え時間初期化
				directionChangeTimeCount_ = 0;
			}

			const Vector3D normalizeTargetPos = owner->GetTargetPosition().Normalize();

			//プレイヤーが視界の範囲内に居ないなら関数脱出
			if (0.0f < Vector3D::Dot(owner->GetDir(), normalizeTargetPos))
			{
				return;
			}

			//プレイヤーが近くにいたら
			if ((owner->GetTargetPosition() - owner->GetPos()).SquareL2Norm() < squareFindOutRange_)
			{
				//プレイヤー発見状態に移行
				nextStateName_ = ENEMY_STATE::FIND_OUT;
				isTransitionToNextState_ = true;

				return;
			}
		}
	}
}