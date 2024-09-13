#include "DxLib.h"
#include "Camera.h"
#include "Input/KeyBoard/InputKeyBoard.h"
#include "Math/MyMath.h"
#include "Matrix/Matrix3D.h"
#include "Player/Player.h"
#include <math.h>
#include <Effekseer/Effekseer.h>
#include <Input/GamePad/GamePad.h>
#include <Input/Mouse/Mouse.h>
#include <Input/Input.h>
#include <Common.h>


//カメラ初期化関数
void Camera::Init(void)
{
	// カメラの設定
	SetCameraNearFar(1.0f, 27000.0f);

	SetupCamera_Perspective(MY_MATH::PI_OVER_THREE);

	pos_ = { 0.0f, CAMERA::POS_Y_DISTANCE, CAMERA::POS_Z_DISTANCE };	//カメラ位置
	target_ = { 0.0f, 0.0f, 0.0f };												//注視点
	up_ = { 0.0f, 1.0f, 0.0f };												//上方向
	rot_ = { MY_MATH::PI_OVER_SIX, 0.0f, 0.0f };						//カメラ角度

	dir_ = { 0.0f,0.0f,1.0f };

	distanceToPlayer_ = CAMERA::POS_Z_DISTANCE;

	//カメラ位置設定
	SetCameraPositionAndTargetAndUpVec(pos_, target_, up_);

}

//カメラ行動処理関数
void Camera::Step(const Vector3D& playerPos)
{
	//カメラの対象物
	target_ = playerPos;

	if (Input::IsKeyKeep(GAME_INPUT::TURBO))
	{
		//カメラが離れられる最大の距離にする
		distanceToPlayer_ = CAMERA::MAX_DISTANCE;

		// 左回転
		if (InputKeyBoard::IsKeyDown(KEY::LEFT))
		{
			rot_.y -= CAMERA::ROT_RIGHT_LEFT_SPEED;

			// rot_の左右の角度θの定義域は -π < θ <= π
			if (rot_.y < -MY_MATH::PI)
			{
				rot_.y = MY_MATH::PI;
			}

		}

		// 右回転
		if (InputKeyBoard::IsKeyDown(KEY::RIGHT))
		{
			rot_.y += CAMERA::ROT_RIGHT_LEFT_SPEED;

			// rot_の左右の角度θの定義域は -π <= θ < π
			if (rot_.y > MY_MATH::PI)
			{
				rot_.y = -MY_MATH::PI;
			}

		}

		return;
	}

	//プレイヤーの位置からカメラの位置までのベクトル作成
	dir_ = playerPos - pos_;

	//ベクトルの長さ取得
	distanceToPlayer_ = dir_.L2Norm();

	//カメラが近づける最小の距離以上離れているなら
	distanceToPlayer_ >= CAMERA::MIN_DISTANCE ?

		//カメラが離れられる最大の距離以上離れていたら
		(distanceToPlayer_ >= CAMERA::MAX_DISTANCE ?

		//カメラが離れられる最大の距離にする
		distanceToPlayer_ = CAMERA::MAX_DISTANCE

		//短ければ追いかける
		: distanceToPlayer_ -= CAMERA::SPEED)

		//カメラが近づける最小の距離にする
		: distanceToPlayer_ = CAMERA::MIN_DISTANCE;

	//自分から見て下方向に回転
	if (InputKeyBoard::IsKeyDown(KEY::UP))
	{
		rot_.x -= CAMERA::ROT_UP_DOWN_SPEED;

		// rot_の上下の角度θの定義域は　(π/2) + π/100 <= θ <= (π/2) - π/100
		if (rot_.x < 0.0f)
		{
			rot_.x = 0.0f;
		}
	}

	//自分から見て上方向に回転
	if (InputKeyBoard::IsKeyDown(KEY::DOWN))
	{
		rot_.x += CAMERA::ROT_UP_DOWN_SPEED;

		// rot_の上下の角度θの定義域は (-π/2) + π/100 <= θ <= (π/2) - π/100
		if (rot_.x > MY_MATH::HALF_PI - CAMERA::ROT_UP_DOWN_SPEED)
		{
			rot_.x = MY_MATH::HALF_PI - CAMERA::ROT_UP_DOWN_SPEED;
		}
	}

	//自分から見て右方向に回転
	if (InputKeyBoard::IsKeyDown(KEY::LEFT))
	{
		rot_.y -= CAMERA::ROT_RIGHT_LEFT_SPEED;

		// rot_の左右の角度θの定義域は -π < θ <= π
		if (rot_.y < -MY_MATH::PI)
		{
			rot_.y = MY_MATH::PI;
		}

	}

	//自分から見て左方向に回転
	if (InputKeyBoard::IsKeyDown(KEY::RIGHT))
	{
		rot_.y += CAMERA::ROT_RIGHT_LEFT_SPEED;

		// rot_の左右の角度θの定義域は -π <= θ < π
		if (rot_.y > MY_MATH::PI)
		{
			rot_.y = -MY_MATH::PI;
		}

	}

	//ゲームパッドのRスティック取得
	const Vector3D GamePadRStick = InputGamePad::GetRStickVector().Normalize();

	if (MyMath::Abs(GamePadRStick.x) > Common::KINDA_SMALL_NUMBER || MyMath::Abs(GamePadRStick.y) > Common::KINDA_SMALL_NUMBER)
	{
		rot_ += GamePadRStick * CAMERA::GAMEPAD_ROT_COEFFICIENT;

		//rot_.x < (-π/2) + (π/100)
		if (rot_.x < -MY_MATH::HALF_PI + CAMERA::ROT_UP_DOWN_SPEED)
		{
			rot_.x = -MY_MATH::HALF_PI + CAMERA::ROT_UP_DOWN_SPEED;
		}

		//rot_.x > (π/2) - (π/100)
		if (rot_.x > MY_MATH::HALF_PI - CAMERA::ROT_UP_DOWN_SPEED)
		{
			rot_.x = MY_MATH::HALF_PI - CAMERA::ROT_UP_DOWN_SPEED;
		}


		//rot_.y < -π/2
		if (rot_.y < -MY_MATH::PI)
		{
			rot_.y = MY_MATH::PI;
		}

		//rot_.y > π/2
		if (rot_.y > MY_MATH::PI)
		{
			rot_.y = -MY_MATH::PI;
		}
	}
}

//カメラ更新関数
void Camera::UpDate(void)
{
	//行列によるカメラ位置計算
	Matrix3D RetCameraMat = Matrix3D::GetTranslateMatrix(target_)
		* Matrix3D::GetYawMatrix(rot_.y)
		* Matrix3D::GetPitchMatrix(rot_.x)
		* Matrix3D::GetTranslateMatrix(-target_.x, -target_.y, -target_.z - distanceToPlayer_);

	pos_ = RetCameraMat * target_;

	//カメラ向いている方向計算
	dir_ = Matrix3D::GetTranslateMatrix(dir_)
		* Matrix3D::GetYawMatrix(rot_.y)
		* Matrix3D::GetPitchMatrix(-dir_.x) * dir_;

	//カメラ位置設定
	SetCameraPositionAndTargetAndUpVec(pos_, target_, up_);

}
