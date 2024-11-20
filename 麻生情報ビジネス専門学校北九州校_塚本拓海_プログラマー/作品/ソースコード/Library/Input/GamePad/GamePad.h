#pragma once

#include <vector>
#include "DxLib.h"
#include "Vector/Vector3D.h"


//ゲームパッド入力用クラス
class InputGamePad
{
private:
	//現在のフレームの入力情報格納用変数
	static inline XINPUT_STATE currentKeyBuf_;

	//前フレームの入力情報格納用変数
	static inline XINPUT_STATE preKeyBuf_;

public:
	//コンストラクタ
	InputGamePad() = delete;

	//デストラクタ
	~InputGamePad() = delete;

	//初期化関数
	static void Init(void);

	//入力処理関数
	static void Step(void);

	//左スティックの傾きをベクトルにして取得
	static Vector3D GetLStickVector(void);

	//右スティックの傾きをベクトルにして取得
	static Vector3D GetRStickVector(void);

	//今、押下されたか
	static bool IsKeyPush(int keyCode);
	//押下され続けているか
	static bool IsKeyKeep(int keyCode);
	//押下され続けたボタンが離されたか
	static bool IsKeyRelease(int keyCode);

	//単純に押されているか
	static bool IsKeyDown(int keyCode);

};
