#include "EnemyBase.h"
#include <Effekseer/Effekseer.h>
#include <Matrix/Matrix3D.h>
#include <Math/MyMath.h>
#include <EffekseerParameter.h>

namespace BOUDAMA
{
	//読み込み処理関数
	void EnemyBase::Load(int originalHandle)
	{
		if (handle_ == -1)
		{
			handle_ = MV1DuplicateModel(originalHandle);

			//位置・角度設定
			MV1SetPosition(handle_, pos_);
			MV1SetRotationXYZ(handle_, rot_);
		}
	}

	//出現処理関数
	void EnemyBase::AppearanceRequest(void)
	{
		//初期位置設定
		pos_ = Matrix3D::GetYawMatrix(MyMath::DegreesToRadian(GetRand(359)))
			* Matrix3D::GetTranslateMatrix(Vector3D(0.0f, 0.0f, 3750.0f)) * MyMath::ZERO_VECTOR_3D;

		//死者蘇生
		isAlive_ = true;
		isCollisionEnabled_ = true;

		//位置・角度設定
		MV1SetPosition(handle_, pos_);
		MV1SetRotationXYZ(handle_, rot_);
	}

	//行動処理関数
	void EnemyBase::Step(const Vector3D& playerPos) {}


	void EnemyBase::HitCalculation(void) 
	{
		stateMachine_->ChangeState(ENEMY_STATE::KNOCK_BACK);

		CEffekseerCtrl::Request(EFFECT::HIT_EFFECT, pos_, false);
	}

	void EnemyBase::DeathCalculation(const Vector3D& hitObjectVelocity)
	{
		//ぶつかった相手の速度受け取り、吹っ飛ばす気持ちよさを出すためにKNOCK_BACK_BOOSTを掛けて増大させる
		velocity_ = hitObjectVelocity * ENEMY::KNOCK_BACK_BOOST;

		stateMachine_->ChangeState(ENEMY_STATE::CORPSE);

		CEffekseerCtrl::Request(EFFECT::HIT_EFFECT, pos_, false);
	}
}
