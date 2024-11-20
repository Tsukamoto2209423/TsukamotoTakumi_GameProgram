#pragma once

namespace FRAMERATE
{
	//設定フレームレート
	constexpr int FRAME_RATE = 60;

	//１フレームの時間(ミリ秒)
	constexpr int FRAME_TIME = (1000 / FRAME_RATE);
}

//フレームレート情報
class FrameRate
{
private:
	static inline int currentTime_;			//現在の時間
	static inline int lastFrameTime_;		//前回のフレーム実行時の時間
	static inline int count_;				//フレームカウント用
	static inline int calcFpsTime_;			//FPSを計算した時間
	static inline float fps_;				//計測したFPS(表示用)

public:
	//処理関数
	static void Step();

	//更新関数
	static void Update(void);

	//処理実行判定関数
	static bool IsPassedFrameRateTime(void);

	//FPS計算関数
	static void CalcFPS(void);

	//FPS表示関数
	static void DrawFPS(void);
};
