#pragma once

#include "DxLib.h"

#define GAMEPAD (int)GAME_PAD::XINPUT
#define PADNUM (int)GAME_PAD::CONNECT_NUM
#define KEY (int)KEYBOARD::KEY_CODE

//ゲーム内で使う入力一覧
enum GAME_INPUT
{
	//ゲーム緊急終了キー
	ESCAPE,

	//決定キー
	ENTER,

	//戻るキー
	BACK,

	//↑キー
	UP,

	//↓キー
	DOWN,

	//ターボ状態キー
	TURBO,

	//総数
	INPUT_NUM
};

//ゲームパッド用名前空間
namespace GAME_PAD
{
	//スティックの傾き係数
	constexpr float STICK_PERCENT = 1.0f / 32767.5f;

	//この値以下のスティックの入力は無視する
	constexpr float STICK_ERROR_NUM = 0.062f;

	//ボタンの最大数
	constexpr unsigned char BUTTON_MAX_NUM = 16Ui8;

	//入力
	enum class XINPUT
	{
		NONE = -1,

		UP = 0,			// 上
		DOWN = 1,		// 下
		LEFT = 2,		// 左
		RIGHT = 3,		// 右
		START = 4,		// Start
		BACK = 5,		// Back
		L_STICK = 6,	// 左スティック押し込み
		R_STICK = 7,	// 右スティック押し込み
		LB = 8,			// LB
		RB = 9,			// RB
		A = 12,			// A
		B = 13,			// B
		X = 14,			// X
		Y = 15,			// Y
		LT = 16,		// 左トリガー
		RT = 17,		// 右トリガー

		NUM,
	};// enum class XInput

}//GAME_PAD

namespace KEYBOARD
{
	//キー最大値
	constexpr int KEY_BUF_LEN = 256;

	enum class KEY_CODE
	{
		NONE = -1,

		BACK = KEY_INPUT_BACK,				// BackSpace
		TAB = KEY_INPUT_TAB,				// Tab
		ENTER = KEY_INPUT_RETURN,			// Enter

		L_SHIFT = KEY_INPUT_LSHIFT,			// 左Shift
		R_SHIFT = KEY_INPUT_RSHIFT,			// 右Shift
		L_CTRL = KEY_INPUT_LCONTROL,		// 左Ctrl
		R_CTRL = KEY_INPUT_RCONTROL,		// 右Ctrl
		ESC = KEY_INPUT_ESCAPE,				// Esc
		SPACE = KEY_INPUT_SPACE,			// Space
		PAGE_UP = KEY_INPUT_PGUP,			// PageUp
		PAGE_DOWN = KEY_INPUT_PGDN,			// PageDown
		END = KEY_INPUT_END,				// End
		HOME = KEY_INPUT_HOME,				// Home
		LEFT = KEY_INPUT_LEFT,				// 左
		UP = KEY_INPUT_UP,					// 上
		RIGHT = KEY_INPUT_RIGHT,			// 右
		DOWN = KEY_INPUT_DOWN,				// 下
		INSERT = KEY_INPUT_INSERT,			// Insert
		DEL = KEY_INPUT_DELETE,				// Delete

		MINUS = KEY_INPUT_MINUS,			// -
		YEN = KEY_INPUT_YEN,				// \キー
		PREVTRACK = KEY_INPUT_PREVTRACK,	// ^
		PERIOD = KEY_INPUT_PERIOD,			// .
		SLASH = KEY_INPUT_SLASH,			// /
		L_ALT = KEY_INPUT_LALT,				// 左ALT
		R_ALT = KEY_INPUT_RALT,				// 右ALT
		SCROLL = KEY_INPUT_SCROLL,			// ScrollLock
		SEMICOLON = KEY_INPUT_SEMICOLON,	// ;
		COLON = KEY_INPUT_COLON,			// :
		LB_RACKET = KEY_INPUT_LBRACKET,		// [
		RB_RACKET = KEY_INPUT_RBRACKET,		// ]
		AT = KEY_INPUT_AT,					// @
		BACK_SLASH = KEY_INPUT_BACKSLASH,	// ＼
		COMMA = KEY_INPUT_COMMA,			// ,
		KANJI = KEY_INPUT_KANJI,			// 漢字キー
		CONVERT = KEY_INPUT_CONVERT,		// 変換キー
		NO_CONVERT = KEY_INPUT_NOCONVERT,	// 無変換キー
		KANA = KEY_INPUT_KANA,				// カナキー
		APPS = KEY_INPUT_APPS,				// アプリケーションキー
		CAPS_LOCK = KEY_INPUT_CAPSLOCK,		// CaspLock
		PRINT_SCREEN = KEY_INPUT_SYSRQ,		// PrintScreen
		PAUSE = KEY_INPUT_PAUSE,			// PauseBreak
		L_WIN = KEY_INPUT_LWIN,				// 左Win
		R_WIN = KEY_INPUT_RWIN,				// 右Win

		NUMLOCK = KEY_INPUT_NUMLOCK,		// テンキーNumLock
		NUMPAD_0 = KEY_INPUT_NUMPAD0,		// テンキー0
		NUMPAD_1 = KEY_INPUT_NUMPAD1,		// テンキー1
		NUMPAD_2 = KEY_INPUT_NUMPAD2,		// テンキー2
		NUMPAD_3 = KEY_INPUT_NUMPAD3,		// テンキー3
		NUMPAD_4 = KEY_INPUT_NUMPAD4,		// テンキー4
		NUMPAD_5 = KEY_INPUT_NUMPAD5,		// テンキー5
		NUMPAD_6 = KEY_INPUT_NUMPAD6,		// テンキー6
		NUMPAD_7 = KEY_INPUT_NUMPAD7,		// テンキー7
		NUMPAD_8 = KEY_INPUT_NUMPAD8,		// テンキー8
		NUMPAD_9 = KEY_INPUT_NUMPAD9,		// テンキー9

		F1 = KEY_INPUT_F1,				// F1
		F2 = KEY_INPUT_F2,				// F2
		F3 = KEY_INPUT_F3,				// F3
		F4 = KEY_INPUT_F4,				// F4
		F5 = KEY_INPUT_F5,				// F5
		F6 = KEY_INPUT_F6,				// F6
		F7 = KEY_INPUT_F7,				// F7
		F8 = KEY_INPUT_F8,				// F8
		F9 = KEY_INPUT_F9,				// F9
		F10 = KEY_INPUT_F10,			// F10
		F11 = KEY_INPUT_F11,			// F11
		F12 = KEY_INPUT_F12,			// F12

		A = KEY_INPUT_A,				// A
		B = KEY_INPUT_B,				// B
		C = KEY_INPUT_C,				// C
		D = KEY_INPUT_D,				// D
		E = KEY_INPUT_E,				// E
		F = KEY_INPUT_F,				// F
		G = KEY_INPUT_G,				// G
		H = KEY_INPUT_H,				// H
		I = KEY_INPUT_I,				// I
		J = KEY_INPUT_J,				// J
		K = KEY_INPUT_K,				// K
		L = KEY_INPUT_L,				// L
		M = KEY_INPUT_M,				// M
		N = KEY_INPUT_N,				// N
		O = KEY_INPUT_O,				// O
		P = KEY_INPUT_P,				// P
		Q = KEY_INPUT_Q,				// Q
		R = KEY_INPUT_R,				// R
		S = KEY_INPUT_S,				// S
		T = KEY_INPUT_T,				// T
		U = KEY_INPUT_U,				// U
		V = KEY_INPUT_V,				// V
		W = KEY_INPUT_W,				// W
		X = KEY_INPUT_X,				// X
		Y = KEY_INPUT_Y,				// Y
		Z = KEY_INPUT_Z,				// Z

		_0 = KEY_INPUT_0,				// 0
		_1 = KEY_INPUT_1,				// 1
		_2 = KEY_INPUT_2,				// 2
		_3 = KEY_INPUT_3,				// 3
		_4 = KEY_INPUT_4,				// 4
		_5 = KEY_INPUT_5,				// 5
		_6 = KEY_INPUT_6,				// 6
		_7 = KEY_INPUT_7,				// 7
		_8 = KEY_INPUT_8,				// 8
		_9 = KEY_INPUT_9,				// 9

	};// enum class KEY

}

//マウス
namespace MOUSE
{
	constexpr int RADIUS = 10;
};

