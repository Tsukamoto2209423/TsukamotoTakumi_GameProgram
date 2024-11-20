#pragma once

#include <Vector/Vector2D.h>

//マウス入力用クラス
class InputMouse
{
private:
	//今、クリックしているか判定
	static inline bool isCurrentClick_;

	//1フレーム前にクリックしていたか判定
	static inline bool isPreClick_;

	//現在位置
	static inline int currentPosX_,currentPosY_;

	//1フレーム前の位置
	static inline int prePosX_, prePosY_;

public:
	//初期化処理関数
	static void Init(void);

	//入力処理関数
	static void Step(void);

	/// <summary>
	/// 現在のフレームで左クリックされたか
	/// </summary>
	/// <returns>
	/// true : 現在のフレームで押された
	/// false : 現在のフレームで押されていない
	/// </returns>
	static inline bool IsClickDown(void) { return isCurrentClick_ && !isPreClick_; }

	/// <summary>
	/// 現在のフレームで離されたか
	/// </summary>
	/// <returns>
	/// true : 現在のフレームで離された
	/// false : 現在のフレームで離されていない
	/// </returns>
	static inline bool IsClickRelease(void) { return !isCurrentClick_ && isPreClick_; }

	//マウスを移動させた値を取得
	static inline Vector2D GetMoveValue(void) { return Vector2D(static_cast<float>(currentPosX_ - prePosX_), static_cast<float>(currentPosY_ - prePosY_)); }

	//マウスを横方向に移動させた値を取得
	static inline float GetMoveValueX(void) { return static_cast<float>(currentPosX_ - prePosX_); }

	//マウスを縦方向に移動させた値を取得
	static inline float GetMoveValueY(void) { return static_cast<float>(currentPosY_ - prePosY_); }
};
