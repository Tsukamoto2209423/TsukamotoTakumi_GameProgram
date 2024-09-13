#pragma once

//汎用情報名前空間
namespace Common 
{
	//ウィンドウの原点
	constexpr int WINDOW_ORIGIN = 0;

	//ウィンドウの横幅
	constexpr int WINDOW_WIDTH = 1280;

	//ウィンドウの半分の横幅
	constexpr int WINDOW_WIDTH_HALF = 640;

	//ウィンドウの横幅
	constexpr float WINDOW_WIDTH_F = 1280.0f;

	//ウィンドウの半分の横幅
	constexpr float WINDOW_WIDTH_HALF_F = 640.0f;

	//ウィンドウの縦幅
	constexpr int WINDOW_HEIGHT = 720;

	//ウィンドウの半分の縦幅
	constexpr int WINDOW_HEIGHT_HALF = 360;

	//ウィンドウの縦幅
	constexpr float WINDOW_HEIGHT_F = 720.0f;

	//ウィンドウの半分の縦幅
	constexpr float WINDOW_HEIGHT_HALF_F = 360.0f;

	//小さい数
	constexpr float KINDA_SMALL_NUMBER = 1.e-4f;
};
