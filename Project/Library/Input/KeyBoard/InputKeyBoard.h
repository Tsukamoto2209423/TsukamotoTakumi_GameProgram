#pragma once

#include <vector>
#include <Input/InputParameter.h>

//キーボード入力用クラス
class InputKeyBoard
{
private:
	//現フレームに入力している情報
	static inline char currentKeyBuf_[KEYBOARD::KEY_BUF_LEN];

	//前フレームに入力した情報
	static inline char preKeyBuf_[KEYBOARD::KEY_BUF_LEN];

public:
	InputKeyBoard() = delete;
	~InputKeyBoard() = delete;

	//初期化
	static void Init(void);
	//行動処理関数
	static void Step(void);

	//今、押下されたか
	static bool IsKeyPush(int keyCode);
	
	//押下され続けているか
	static bool IsKeyKeep(int keyCode);
	
	//押下され続けたボタンが離されたか
	static bool IsKeyRelease(int keyCode);

	//単純に押されているか
	static bool IsKeyDown(int keyCode);

};
