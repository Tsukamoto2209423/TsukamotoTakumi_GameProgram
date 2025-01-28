#include "Input.h"
#include "KeyBoard/InputKeyBoard.h"
#include "GamePad/GamePad.h"
#include "InputParameter.h"
#include "Mouse/Mouse.h"

//初期化関数
void Input::Init(void)
{
	InputKeyBoard::Init();
	InputGamePad::Init();
	InputMouse::Init();

	//それぞれの入力情報追加
	key_.emplace_back(KEY_INPUT_ESCAPE);
	key_.emplace_back(KEY_INPUT_RETURN);
	key_.emplace_back(KEY_INPUT_BACK);
	key_.emplace_back(KEY_INPUT_UP);
	key_.emplace_back(KEY_INPUT_DOWN);
	key_.emplace_back(KEY_INPUT_LEFT);
	key_.emplace_back(KEY_INPUT_RIGHT);
	key_.emplace_back(KEY_INPUT_SPACE);
	key_.emplace_back(KEY_INPUT_LSHIFT);

	
	button_.emplace_back(XINPUT_BUTTON_BACK);
	button_.emplace_back(XINPUT_BUTTON_B);
	button_.emplace_back(XINPUT_BUTTON_A);
	button_.emplace_back(XINPUT_BUTTON_DPAD_UP);
	button_.emplace_back(XINPUT_BUTTON_DPAD_DOWN);
	button_.emplace_back(XINPUT_BUTTON_DPAD_LEFT);
	button_.emplace_back(XINPUT_BUTTON_DPAD_RIGHT);
	button_.emplace_back(XINPUT_BUTTON_B);
	button_.emplace_back(XINPUT_BUTTON_Y);
}

//入力処理関数
void Input::Step(void)
{
	//キーボード入力更新処理
	InputKeyBoard::Step();

	//ゲームパッド入力更新処理
	InputGamePad::Step();

	//マウス入力更新処理
	InputMouse::Step();

}

//今、押下されたか
bool Input::IsKeyPush(int keyCode)
{
	return InputKeyBoard::IsKeyPush(key_[keyCode]) ||
		InputGamePad::IsKeyPush(button_[keyCode]);
}

//押下され続けているか
bool Input::IsKeyKeep(int keyCode)
{
	//前フレームで押されている かつ 現フレームで押されているなら真、押されていないなら偽
	return InputKeyBoard::IsKeyKeep(key_[keyCode]) ||
		InputGamePad::IsKeyKeep(button_[keyCode]);
}

//押下され続けたボタンが離されたか
bool Input::IsKeyRelease(int keyCode)
{
	//前フレームで押されている かつ 現フレームで押されていないなら真、押されているなら偽
	return InputKeyBoard::IsKeyRelease(key_[keyCode]) ||
		InputGamePad::IsKeyRelease(button_[keyCode]);
}

//単純に押されているか
bool Input::IsKeyDown(int keyCode)
{
	//現フレームで押されているか(前フレームの状態は関係なし)
	return InputKeyBoard::IsKeyDown(key_[keyCode]) ||
		InputGamePad::IsKeyDown(button_[keyCode]);
}
