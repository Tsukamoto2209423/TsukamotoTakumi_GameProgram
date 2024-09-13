#include "GamePad.h"
#include "Math/MyMath.h"
#include <Input/InputParameter.h>

//初期化関数
void InputGamePad::Init(void)
{
	//初期化
	currentKeyBuf_ = { 0 };
	preKeyBuf_ = { 0 };

	//STICK_ERROR_NUM以下の値は受け取らないようにする
	SetJoypadDeadZone(DX_INPUT_PAD1, GAME_PAD::STICK_ERROR_NUM);
}

//入力処理関数
void InputGamePad::Step(void)
{
	//配列の先頭アドレスを取得
	unsigned char* preKeyButton = preKeyBuf_.Buttons;
	unsigned char* currentKeyButton = currentKeyBuf_.Buttons;

	//前フレームに入力した情報を格納
	for (int index = 0; index < GAME_PAD::BUTTON_MAX_NUM; ++index, ++preKeyButton, ++currentKeyButton)
	{
		*preKeyButton = *currentKeyButton;
	}

	//現フレームで押されている情報を格納
	GetJoypadXInputState(DX_INPUT_PAD1, &currentKeyBuf_);

}

//左スティックの値取得
Vector3D InputGamePad::GetLStickVector(void)
{
	//(X軸,Y軸,Z軸)の順で左スティックの傾きの割合を計算
	const Vector3D vec(currentKeyBuf_.ThumbLX * GAME_PAD::STICK_PERCENT,
		0.0f,
		currentKeyBuf_.ThumbLY * GAME_PAD::STICK_PERCENT);

	//入力値が誤差の範囲内ならゼロベクトルを返す
	if (GAME_PAD::STICK_ERROR_NUM >= MyMath::Abs(vec.x) && GAME_PAD::STICK_ERROR_NUM >= MyMath::Abs(vec.z))
	{
		return MY_MATH::ZERO_VECTOR_3D;
	}

	//入力されたなら、その値を返す
	return vec;
}

//右スティックの値取得
Vector3D InputGamePad::GetRStickVector(void)
{
	//(X軸,Y軸,Z軸)の順で左スティックの傾きの割合を計算
	const Vector3D vec(-currentKeyBuf_.ThumbRY * GAME_PAD::STICK_PERCENT,
		currentKeyBuf_.ThumbRX * GAME_PAD::STICK_PERCENT,
		0.0f);

	//入力値が誤差の範囲内ならゼロベクトルを返す
	if (GAME_PAD::STICK_ERROR_NUM >= MyMath::Abs(vec.x) && GAME_PAD::STICK_ERROR_NUM >= MyMath::Abs(vec.y))
	{
		return MY_MATH::ZERO_VECTOR_3D;
	}

	//入力されたなら、その値を返す
	return vec;
}

//今、押下されたか
bool InputGamePad::IsKeyPush(int keyCode)
{
	//前フレームで押されていない かつ 現フレームで押されているなら真、押されていないなら偽
	return preKeyBuf_.Buttons[keyCode] == 0 && currentKeyBuf_.Buttons[keyCode] == 1;
}

//押下され続けているか
bool InputGamePad::IsKeyKeep(int keyCode)
{
	//前フレームで押されている かつ 現フレームで押されているなら真、押されていないなら偽
	return preKeyBuf_.Buttons[keyCode] == 1 && currentKeyBuf_.Buttons[keyCode] == 1;
}

//押下され続けたボタンが離されたか
bool InputGamePad::IsKeyRelease(int keyCode)
{
	//前フレームで押されている かつ 現フレームで押されていないなら真、押されているなら偽
	return preKeyBuf_.Buttons[keyCode] == 1 && currentKeyBuf_.Buttons[keyCode] == 0;
}

//単純に押されているか
bool InputGamePad::IsKeyDown(int keyCode)
{
	//現フレームで押されているか(前フレームの状態は関係なし)
	return currentKeyBuf_.Buttons[keyCode] == 1;
}
