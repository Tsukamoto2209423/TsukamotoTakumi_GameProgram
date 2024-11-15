#include "KnockBack.h"
#include <Math/MyMath.h>

namespace BOUDAMA
{
	//初期化処理関数
	void KnockBack::Enter(void)
	{

	}

	//行動処理関数
	void KnockBack::Execute(void)
	{
		if (const auto& owner = owner_.lock())
		{
			//ノックバック状態の処理が最大回数されていたら
			if (maxTimeCount_ < timeCount_)
			{
				//初期化処理
				timeCount_ = 0;

				owner->SetIsActive(false);

				return;
			}

			//自分の速度を位置に加算し、上に上昇させる
			Vector3D velocity = owner->GetVelocity();
			velocity.y += 9.5f;
			owner->MovePos(velocity);

			//回転させる
			owner->Rotate(MyMath::INVERSE_TWO_PI, 0.0f, 0.0f);

			//ノックバック状態の時間計測
			++timeCount_;
		}
	}

}