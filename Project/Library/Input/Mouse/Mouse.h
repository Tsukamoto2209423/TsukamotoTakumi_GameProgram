#pragma once

#include <Vector/Vector2D.h>

//マウス入力用クラス
class InputMouse
{
private:

public:
	//今、クリックしているか判定
	static inline bool isCurrentClick_;

	//1フレーム前にクリックしていたか判定
	static inline bool isPreClick_;

	//現在位置
	static inline int currentPosX_,currentPosY_;

	//1フレーム前の位置
	static inline int prePosX_, prePosY_;

	//初期化処理関数
	static void Init(void);

	//入力処理関数
	static void Step(void);

	//
	static inline bool IsClick(void) { return isCurrentClick_ && !isPreClick_; }

	//
	static inline bool IsClickRelease(void) { return !isCurrentClick_ && isPreClick_; }


	static inline float GetMovePosX(void) { return static_cast<float>(currentPosX_ - prePosX_); }

	static inline float GetMovePosY(void) { return static_cast<float>(currentPosY_ - prePosY_); }
};
