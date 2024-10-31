#pragma once

#include <Vector/Vector3D.h>
#include "Transform/Transform.h"

namespace BOUDAMA
{
	//カメラ基底クラス
	class CameraBase : public Transform
	{
	protected:
		//注視点
		Vector3D target_;

		//上方向
		Vector3D up_;

	public:
		//コンストラクタ
		CameraBase() {}

		//デストラクタ
		virtual ~CameraBase() {}

		//初期化処理関数
		virtual void Init(void) = 0;

		//移動処理関数
		virtual void Step(const Vector3D& playerPos) = 0;

		//更新関数
		virtual void UpDate(void) = 0;


		//注視点取得
		inline Vector3D GetTarget(void) const { return target_; }

		//注視点取得
		inline void SetTarget(const Vector3D& target) { target_ = target; }


		//上方向取得
		inline Vector3D GetUp(void) const { return up_; }

		//上方向設定
		inline void SetUp(const Vector3D& up) { up_ = up; }


	};
}
