#include "DebugCamera.h"
#include "Camera.h"
#include "Input/KeyBoard/InputKeyBoard.h"
#include "Math/MyMath.h"
#include "Matrix/Matrix3D.h"

//カメラ初期化関数
void DebugCamera::Init(void)
{
	// カメラの設定
	SetCameraNearFar(1.0f, 27000.0f);

	SetupCamera_Perspective(MY_MATH::PI_OVER_THREE);

	pos_ = { 0.0f, CAMERA::POS_Y_DISTANCE, CAMERA::POS_Z_DISTANCE };		//カメラ位置
	target_ = { 0.0f, 100.0f, 0.0f };										//注視点
	up_ = { 0.0f, 1.0f, 0.0f };												//上方向
	rot_ = { MY_MATH::PI_OVER_SIX, 0.0f, 0.0f };							//カメラ角度

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
	Vector3D cameraSpeed = { speed * sinf(rot_.y),0.0f,speed * cosf(rot_.y) };

	//上昇
	if (InputKeyBoard::IsKeyDown(KEY::Q))
	{
		pos_.y -= speed;
		target_.y -= speed;
	}

	//下降
	if (InputKeyBoard::IsKeyDown(KEY::E))
	{
		pos_.y += speed;
		target_.y += speed;
	}

	//前移動
	if (InputKeyBoard::IsKeyDown(KEY::W))
	{
		pos_ = pos_ + cameraSpeed;
		target_ = target_ + cameraSpeed;
	}
	//後移動
	if (InputKeyBoard::IsKeyDown(KEY::S))
	{
		pos_ = pos_ - cameraSpeed;
		target_ = target_ - cameraSpeed;
	}

	//左シフトキーを押していると加速
	//左右に水平移動するので π/2 足す
	float left_right_speed = InputKeyBoard::IsKeyDown(KEY::L_SHIFT) ? CAMERA::FAST_SPEED : CAMERA::SPEED;
	Vector3D left_right_cameraSpeed = { left_right_speed * sinf(rot_.y + MY_MATH::HALF_PI),0.0f,left_right_speed * cosf(rot_.y + MY_MATH::HALF_PI) };

	//左移動
	if (InputKeyBoard::IsKeyDown(KEY::A))
	{
		//差なので左に移動
		pos_ -= left_right_cameraSpeed;
		target_ -= left_right_cameraSpeed;
	}
	//右移動
	if (InputKeyBoard::IsKeyDown(KEY::D))
	{
		//和なので右に移動
		pos_ += left_right_cameraSpeed;
		target_ += left_right_cameraSpeed;
	}


	// 右回転
	if (InputKeyBoard::IsKeyDown(KEY::RIGHT))
	{
		rot_.y += CAMERA::ROT_RIGHT_LEFT_SPEED;

		// rot_の左右の角度θの定義域は -2π < θ <= 2π
		if (rot_.y <= -DX_PI_F)
		{
			rot_.y = 0.0f;
		}

	}

	// 左回転
	if (InputKeyBoard::IsKeyDown(KEY::LEFT))
	{
		rot_.y -= CAMERA::ROT_RIGHT_LEFT_SPEED;

		// rot_の左右の角度θの定義域は -2π <= θ < 2π
		if (rot_.y >= DX_PI_F)
		{
			rot_.y = 0.0f;
		}

	}

	//上回転
	if (InputKeyBoard::IsKeyDown(KEY::UP))
	{
		// rot_の上下の角度θの定義域は (-π/2) + π/100 <= θ <= (π/2) - π/100
		if (rot_.x > -MY_MATH::HALF_PI + CAMERA::ROT_UP_DOWN_SPEED)
		{
			rot_.x -= CAMERA::ROT_UP_DOWN_SPEED;
		}
	}

	//下回転
	if (InputKeyBoard::IsKeyDown(KEY::DOWN))
	{
		// rot_の上下の角度θの定義域は　(π/2) + π/100 <= θ <= (π/2) - π/100
		if (rot_.x < MY_MATH::HALF_PI - CAMERA::ROT_UP_DOWN_SPEED)
		{
			rot_.x += CAMERA::ROT_UP_DOWN_SPEED;
		}

	}

	// 右回転
	if (InputKeyBoard::IsKeyDown(KEY::RIGHT))
	{
		rot_.y += CAMERA::ROT_RIGHT_LEFT_SPEED;

		// rot_の左右の角度θの定義域は -2π < θ <= 2π
		if (rot_.y <= -MY_MATH::PI)
		{
			rot_.y = 0.0f;
		}

	}

	// 左回転
	if (InputKeyBoard::IsKeyDown(KEY::LEFT))
	{
		rot_.y -= CAMERA::ROT_RIGHT_LEFT_SPEED;

		// rot_の左右の角度θの定義域は -2π <= θ < 2π
		if (rot_.y >= MY_MATH::PI)
		{
			rot_.y = 0.0f;
		}

	}
}

//カメラ更新関数
void DebugCamera::UpDate(void)
{
	//行列によるカメラ位置計算
	Matrix3D RetCameraMat = Matrix3D::GetTranslateMatrix(target_)
		* Matrix3D::GetYawMatrix(rot_.y)
		* Matrix3D::GetPitchMatrix(rot_.x)
		* Matrix3D::GetTranslateMatrix(-target_);

	pos_ = RetCameraMat * target_;

	//
	dir_ = Matrix3D::GetYawMatrix(rot_.y) * dir_;

	//カメラ位置設定
	SetCameraPositionAndTargetAndUpVec(pos_, target_, up_);
}
