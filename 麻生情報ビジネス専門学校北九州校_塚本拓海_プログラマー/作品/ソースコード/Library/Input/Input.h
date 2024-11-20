#pragma once

#include <vector>

//入力統一管理用クラス
class Input
{
private:
	//キーボード入力
	static inline std::vector<int> key_;

	//ゲームパッド入力
	static inline std::vector<int> button_;

public:
	//統一初期化関数
	static void Init(void);

	//統一入力処理関数
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