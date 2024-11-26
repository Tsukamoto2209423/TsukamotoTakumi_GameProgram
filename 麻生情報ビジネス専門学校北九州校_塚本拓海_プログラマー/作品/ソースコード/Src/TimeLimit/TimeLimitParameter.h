#pragma once

namespace BOUDAMA
{
	//制限時間クラスで使う定数
	namespace TIME_LIMIT
	{
		//最初に設定する制限時間(ミリ秒)
		constexpr int INIT_TIME = 91000;

		//最初に描画する右端の数字のX軸の位置
		constexpr int INIT_NUM_POS_X = 1252;

		//最初に描画する右端の数字のY軸の位置
		constexpr int INIT_NUM_POS_Y = 40;

		//数字を描画する間隔
		constexpr int NUM_POS_INTERVAL = 48;


		//「のこり」の画像のパス
		constexpr char CHARA_PATH[] = { "Data/Image/Limit_Time_Character.png" };

		//「のこり」の画像を描画するX軸の位置
		constexpr int CHARA_POS_X = 1060;

		//「のこり」の画像を描画するY軸の位置
		constexpr int CHARA_POS_Y = 44;


		//「∞」の画像のパス
		constexpr char INFINITY_PATH[] = { "Data/Image/Infinity.PNG" };

		//「∞」の画像を描画するX軸の位置
		constexpr int INFINITY_POS_X = 1200;

		//「∞」の画像を描画するY軸の位置
		constexpr int INFINITY_POS_Y = 44;


		//コンマの画像を描画するX軸の位置
		constexpr int COMMA_POS_X = 1225;

		//コンマの画像を描画するY軸の位置
		constexpr int COMMA_POS_Y = 51;
	}
}
