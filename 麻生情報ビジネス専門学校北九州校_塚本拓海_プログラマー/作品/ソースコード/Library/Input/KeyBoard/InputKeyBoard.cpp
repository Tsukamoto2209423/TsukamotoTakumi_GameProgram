#include "InputKeyBoard.h"
#include <DxLib.h>

//初期化関数
void InputKeyBoard::Init(void)
{
	//先頭アドレス取得
	char* currentKey = currentKeyBuf_;
	char* preKey = preKeyBuf_;
	
	//初期化
	for (int index = 0; index < KEYBOARD::KEY_BUF_LEN; ++index,++currentKey,++preKey)
	{
		*currentKey = '\0';
		*preKey = '\0';
	}
}

//入力処理
void InputKeyBoard::Step(void)
{
	//配列の先頭アドレス取得
	char* currentKey = currentKeyBuf_;
	char* preKey = preKeyBuf_;

	//前フレームに入力した情報を格納
	for (int index = 0; index < KEYBOARD::KEY_BUF_LEN; ++index, ++preKey, ++currentKey)
	{
		*preKey = *currentKey;
	}

	//現フレームで押されている情報を格納
	GetHitKeyStateAll(currentKeyBuf_);
}

//今、押下されたか
bool InputKeyBoard::IsKeyPush(int keyCode)
{
	//前フレームで押されていない かつ 現フレームで押されているなら真、押されていないなら偽
	return !preKeyBuf_[keyCode] && currentKeyBuf_[keyCode];
}

//押下され続けているか
bool InputKeyBoard::IsKeyKeep(int keyCode)
{
	//前フレームで押されている かつ 現フレームで押されているなら真、押されていないなら偽
	return preKeyBuf_[keyCode] && currentKeyBuf_[keyCode];
}

//押下され続けたボタンが離されたか
bool InputKeyBoard::IsKeyRelease(int keyCode)
{
	//前フレームで押されている かつ 現フレームで押されていないなら真、押されているなら偽
	return preKeyBuf_[keyCode] && !currentKeyBuf_[keyCode];
}

//単純に押されているか
bool InputKeyBoard::IsKeyDown(int keyCode)
{
	//現フレームで押されているか(前フレームの状態は関係なし)
	return currentKeyBuf_[keyCode];
}
