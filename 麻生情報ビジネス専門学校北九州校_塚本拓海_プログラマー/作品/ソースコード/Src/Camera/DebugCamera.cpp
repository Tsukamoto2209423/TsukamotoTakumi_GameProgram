#include "DebugCamera.h"
#include "Camera.h"
#include <Input/Mouse/Mouse.h>
#include "Input/KeyBoard/InputKeyBoard.h"
#include "Math/MyMath.h"
#include "Matrix/Matrix3D.h"
#include <Common.h>

namespace BOUDAMA
{
	//カメラ初期化関数
	void DebugCamera::Init(void)
	{
		//// カメラの設定
		//SetCameraNearFar(1.0f, 27000.0f);

		//SetupCamera_Perspective(MyMath::PI_OVER_THREE);

		pos_ = { 0.0f, CAMERA::POS_Y_DISTANCE, CAMERA::POS_Z_DISTANCE };		//カメラ位置
		target_ = { 0.0f, 0.0f, 0.0f };										//注視点
		up_ = { 0.0f, 1.0f, 0.0f };												//上方向
		rot_ = { MyMath::PI_OVER_SIX, 0.0f, 0.0f };							//カメラ角度

		dir_ = { 0.0f,0.0f,1.0f };

		//カメラ位置設定
		SetCameraPositionAndTargetAndUpVec(pos_, target_, up_);

	}

	//カメラ行動処理関数
	void DebugCamera::Step(const Vector3D& playerPos)
	{
		//カメラの場所設定

		//左シフトキーを押していると加速
		float speed = InputKeyBoard::IsKeyDown(KEY::L_SHIFT) ? CAMERA::FAST_SPEED : CAMERA::SPEED;
		Vector3D cameraSpeed = dir_ * speed;
		cameraSpeed.y = 0.0f;

		//上昇
		if (InputKeyBoard::IsKeyDown(KEY::Q))
		{
			target_.y -= CAMERA::UP_DOWN_SPEED;
		}

		//下降
		if (InputKeyBoard::IsKeyDown(KEY::E))
		{
			target_.y += CAMERA::UP_DOWN_SPEED;
		}

		//前移動
		if (InputKeyBoard::IsKeyDown(KEY::W))
		{
			target_ += cameraSpeed;
		}
		//後移動
		if (InputKeyBoard::IsKeyDown(KEY::S))
		{
			target_ -= cameraSpeed;
		}

		//左シフトキーを押していると加速
		//左右に水平移動するので π/2 足す
		float left_right_speed = InputKeyBoard::IsKeyDown(KEY::L_SHIFT) ? CAMERA::FAST_SPEED : CAMERA::SPEED;
		Vector3D left_right_cameraSpeed = dir_ * Matrix3D::GetYawMatrix( MyMath::HALF_PI) * speed;
		left_right_cameraSpeed.y = 0.0f;

		//左移動
		if (InputKeyBoard::IsKeyDown(KEY::A))
		{
			//差なので左に移動
			target_ -= left_right_cameraSpeed;
		}
		//右移動
		if (InputKeyBoard::IsKeyDown(KEY::D))
		{
			//和なので右に移動
			target_ += left_right_cameraSpeed;
		}



		//上回転
		if (InputKeyBoard::IsKeyDown(KEY::UP))
		{
			// rot_の上下の角度θの定義域は (-π/2) + π/100 <= θ <= (π/2) - π/100
			if (rot_.x > -MyMath::HALF_PI + CAMERA::ROT_UP_DOWN_SPEED)
			{
				rot_.x -= CAMERA::ROT_UP_DOWN_SPEED;
			}
		}

		//下回転
		if (InputKeyBoard::IsKeyDown(KEY::DOWN))
		{
			// rot_の上下の角度θの定義域は　(π/2) + π/100 <= θ <= (π/2) - π/100
			if (rot_.x < MyMath::HALF_PI - CAMERA::ROT_UP_DOWN_SPEED)
			{
				rot_.x += CAMERA::ROT_UP_DOWN_SPEED;
			}

		}

		// 右回転
		if (InputKeyBoard::IsKeyDown(KEY::RIGHT))
		{
			rot_.y += CAMERA::ROT_RIGHT_LEFT_SPEED;
		}

		// 左回転
		if (InputKeyBoard::IsKeyDown(KEY::LEFT))
		{
			rot_.y -= CAMERA::ROT_RIGHT_LEFT_SPEED;

		}

		//マウス視点操作
		const Vector3D MouseMoveValue(InputMouse::GetMoveValueVertical(), InputMouse::GetMoveValueHorizontal(), 0.0f);

		if (MyMath::Abs(MouseMoveValue.x) > Common::KINDA_SMALL_NUMBER || MyMath::Abs(MouseMoveValue.y) > Common::KINDA_SMALL_NUMBER)
		{
			rot_ += MouseMoveValue * CAMERA::MOUSE_SENSITIVITY;
		}

		//rot_.x < 0
		if (rot_.x < 0.0f)
		{
			rot_.x = 0.0f;
		}

		//rot_.x > π/2
		if (rot_.x >= MyMath::HALF_PI)
		{
			rot_.x = MyMath::HALF_PI - MyMath::INVERSE_TWO_PI;
		}

		//rot_.y < -π/2
		if (rot_.y < -MyMath::PI)
		{
			rot_.y = MyMath::PI;
		}

		//rot_.y > π/2
		if (rot_.y > MyMath::PI)
		{
			rot_.y = -MyMath::PI;
		}
	}

	//カメラ更新関数
	void DebugCamera::UpDate(void)
	{
		//行列によるカメラ位置計算
		Matrix3D RetCameraMat = Matrix3D::GetTranslateMatrix(target_)
			* Matrix3D::GetYawMatrix(rot_.y)
			* Matrix3D::GetPitchMatrix(rot_.x)
			* Matrix3D::GetTranslateMatrix(-target_.x, -target_.y, -target_.z - 1.0f);

		pos_ = RetCameraMat * target_;


		//カメラ向いている方向計算
		dir_ = (target_ - pos_).Normalize();

		//カメラ位置設定
		SetCameraPositionAndTargetAndUpVec(pos_, target_, up_);
	}
}
