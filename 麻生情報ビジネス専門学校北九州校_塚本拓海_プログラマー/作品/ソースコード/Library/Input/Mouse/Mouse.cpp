#include "Mouse.h"

//初期化処理関数
void InputMouse::Init(void)
{
	currentPosX_ = 0;
	currentPosY_ = 0;
	prePosX_ = 0;
	prePosY_ = 0;
	isCurrentClick_ = false;
	isPreClick_ = false;
}

//行動処理関数
void InputMouse::Step(void)
{
	//1フレーム前の情報を記憶
	isPreClick_ = isCurrentClick_;

	//1フレーム前の位置情報を記憶
	prePosX_ = currentPosX_;
	prePosY_ = currentPosY_;

	//現在のフレームで左クリックされているか
	isCurrentClick_ = GetMouseInput() == MOUSE_INPUT_LEFT;

	//現在のマウスの位置を記憶
	GetMousePoint(&currentPosX_, &currentPosY_);

}