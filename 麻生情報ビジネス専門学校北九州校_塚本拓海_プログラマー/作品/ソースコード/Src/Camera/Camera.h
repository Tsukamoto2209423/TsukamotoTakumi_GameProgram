#pragma once

#include "CameraBase.h"
#include "Vector/Vector3D.h"
#include "Math/MyMath.h"

namespace BOUDAMA
{
	namespace CAMERA
	{
		//カメラ位置のXとZ距離の倍数
		constexpr int POS_LEFT_RIGHT_DISTANCE_MULTIPLE = 40;

		//カメラ位置のY距離
		constexpr int POS_UP_DISTANCE = 30;

		//カメラのターゲットのY距離
		constexpr int TARGET_POS_Y_DISTANCE = 20;

		//カメラを上に上昇させる距離
		constexpr float POS_Y_DISTANCE = 590.0f;

		//カメラを手前に後退させる距離
		constexpr float POS_Z_DISTANCE = -450.0f;

		//カメラ移動速度
		constexpr float SPEED = 15.0f;
		
		//上下方向のカメラ移動速度
		constexpr float UP_DOWN_SPEED = 10.0f;

		//高速カメラ移動速度
		constexpr float FAST_SPEED = 25.5f;

		//カメラ左右回転速度
		constexpr float ROT_RIGHT_LEFT_SPEED = MyMath::PI / 30.0f;

		//カメラ上下回転速度
		constexpr float ROT_UP_DOWN_SPEED = MyMath::PI * 0.01f;

		//カメラ注視点左右速度
		constexpr float TARGET_POS_LEFT_RIGHT_SPEED = 2.5f;

		//カメラ注視点上下速度
		constexpr float TARGET_POS_UP_DOWN_SPEED = 0.35f;

		//ゲームパッドでカメラを回転させるときにかける補正係数
		constexpr float GAMEPAD_ROT_COEFFICIENT = 0.04f;

		//マウスでカメラを回転させるときにかける補正係数
		constexpr float MOUSE_SENSITIVITY = 0.01f;

		//プレイヤーに近づくことができる最小の直線距離
		constexpr float MIN_DISTANCE = 300.0f;

		//プレイヤーから遠ざかることができる最大の直線距離
		constexpr float MAX_DISTANCE = 750.0f;
	}

	//カメラクラス
	class Camera : public CameraBase
	{
	private:
		//カメラからプレイヤーまでの距離
		float distanceToPlayer_;

	public:
		//コンストラクタ
		Camera() { distanceToPlayer_ = 0.0f; }

		//デストラクタ
		~Camera() {}

		//初期化処理関数
		void Init(void) override;

		//移動処理関数
		void Step(const Vector3D& playerPos) override;

		//更新関数
		void UpDate(void) override;
	};
}
