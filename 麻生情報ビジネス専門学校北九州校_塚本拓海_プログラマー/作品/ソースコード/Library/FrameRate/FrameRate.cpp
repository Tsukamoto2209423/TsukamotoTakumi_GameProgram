#include "FrameRate.h"
#include <DxLib.h>

//処理実行判定関数
bool FrameRate::IsPassedFrameRateTime(void)
{
	//現在の時間が前回のフレーム時より
	//1000/60ミリ秒(1/60秒)以上経過していたら処理を実行する
	return (currentTime_ - lastFrameTime_ >= FRAMERATE::FRAME_TIME);
}

void FrameRate::Step(void)
{
	//現在の時間を取得
	currentTime_ = GetNowCount();

	//最初のループなら
	//現在の時間を、FPS計算をした時間に設定
	if (calcFpsTime_ == 0.0f)
	{
		calcFpsTime_ = currentTime_;
		fps_ = static_cast<float>(FRAMERATE::FRAME_RATE);
	}
}

//FPS計算更新関数
void FrameRate::Update(void)
{
	//フレーム実行時の時間を更新
	lastFrameTime_ = currentTime_;

	//フレーム数をカウント
	++count_;
}

//FPS計算
void FrameRate::CalcFPS()
{
	//前回のFPSを計算した時間からの経過時間を求める
	int difTime = currentTime_ - calcFpsTime_;

	//前回のFPSを計算した時間から
	//1秒以上経過していたらFPSを計算する
	if (difTime > 1000)
	{
		//フレーム回数をミリ秒に合わせる
		//小数まで出したいのでfloatにキャスト
		float frameCount = static_cast<float>(count_ * 1000.0f);

		//FPSを求める
		//理想の数値は 60000 / 1000 で 60 となる
		fps_ = frameCount / difTime;

		//フレームレートカウントをクリア
		count_ = 0;

		//FPSを計算した時間を更新
		calcFpsTime_ = currentTime_;
	}
}

//FPS表示 (デバック用)
void FrameRate::DrawFPS()
{
	unsigned int color = GetColor(255, 30, 30);
	DrawFormatString(1175, 700, color, "FPS[%.2f]", fps_);
}
