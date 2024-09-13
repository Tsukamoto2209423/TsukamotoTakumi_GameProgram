#include "TimeLimit.h"
#include "TimeLimitParameter.h"
#include <DxLib.h>
#include <NumberGraph/Number.h>
#include <FrameRate/FrameRate.h>
#include <Common.h>

//コンストラクタ
TimeLimit::TimeLimit()
{
	count_ = TIME_LIMIT::INIT_TIME;
	characterHandle_ = -1;
	infinityHandle_ = -1;
	isEndless_ = false;
}

//デストラクタ
TimeLimit::~TimeLimit()
{

}

//初期化
void TimeLimit::Init(void)
{
	// 計測開始時間を取得
	start_ = system_clock::now();
	count_ = TIME_LIMIT::INIT_TIME;
	characterHandle_ = -1;
}

void TimeLimit::Load(void)
{
	//エンドレスなら
	if (isEndless_)
	{
		//「∞」の画像読み込み
		infinityHandle_ = LoadGraph(TIME_LIMIT::INFINITY_PATH);
	}

	characterHandle_ = LoadGraph(TIME_LIMIT::CHARA_PATH);
}

void TimeLimit::Step(void)
{
	//エンドレスの場合は処理しない
	if (isEndless_)
	{
		return;
	}

	//デバッグ中は常に理想時間を返す
#ifdef _DEBUG
	count_ -= FRAMERATE::FRAME_TIME;

#else

	//現在の時間取得
	end_ = system_clock::now();

	//ミリ秒で経過時間分、時間を減らす
	count_ -= static_cast<int>(duration_cast<std::chrono::milliseconds>(end_ - start_).count());

	//現在の時間を前の時間に保存
	start_ = end_;

#endif // _DEBUG

}

// 描画処理
void TimeLimit::Draw(void)
{
	//「のこり」を描画
	DrawRotaGraph(TIME_LIMIT::CHARA_POS_X, TIME_LIMIT::CHARA_POS_Y, 0.5f, 0.0f, characterHandle_, true);

	//エンドレスなら
	if (isEndless_)
	{
		//「∞」を描画
		DrawRotaGraph(TIME_LIMIT::INFINITY_POS_X, TIME_LIMIT::INFINITY_POS_Y, 1.0f, 0.0f, infinityHandle_, true);

		//早期リターンする
		return;
	}

	//小数点第一位まで描画するためにcount_はミリ秒なので0.01倍する
	NumberGraph::Draw(static_cast<int>(count_ * 0.01f), TIME_LIMIT::INIT_NUM_POS_X, TIME_LIMIT::INIT_NUM_POS_Y);

	//コンマ描画
	DrawRotaGraph(TIME_LIMIT::COMMA_POS_X, TIME_LIMIT::COMMA_POS_Y, 0.25f, 0.0f, NumberGraph::GetGraphHandle(0), true);

	//10秒未満なら真ん中に透明な数字も描画
	if (count_ < 10000)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 32);
		DrawRotaGraph(Common::WINDOW_WIDTH_HALF, Common::WINDOW_HEIGHT_HALF, 7.0f, 0.0f, NumberGraph::GetGraphHandle(static_cast<int>(count_ * 0.001f)), true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	//1秒未満なら「0.」も描画
	if (count_ < 1000)
	{
		DrawRotaGraph(TIME_LIMIT::INIT_NUM_POS_X - TIME_LIMIT::NUM_POS_INTERVAL, TIME_LIMIT::INIT_NUM_POS_Y, 0.75f, 0.0f, NumberGraph::GetGraphHandle(0), true);
	}
}

//破棄処理
void TimeLimit::Fin(void)
{
	//「のこり」の画像描画用ハンドルを削除
	DeleteGraph(characterHandle_);
}
