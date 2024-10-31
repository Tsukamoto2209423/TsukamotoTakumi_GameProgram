
#include "DxLib.h"
#include "Score.h"
#include "NumberGraph/Number.h"

namespace BOUDAMA
{
	void Score::Init(void)
	{
		score_ = 0;
		endlessBestScore_ = 0;
		scoreCharaHandle_ = -1;
		bestScoreCharaHandle_ = -1;
	}

	//読み込み処理関数
	void Score::Load(void)
	{
		if (scoreCharaHandle_ == -1)
		{
			scoreCharaHandle_ = LoadGraph(SCORE::SCORE_CHARA_PATH);
		}

		if (bestScoreCharaHandle_ == -1)
		{
			bestScoreCharaHandle_ = LoadGraph(SCORE::BEST_SCORE_CHARA_PATH);
		}
	}

	//描画処理
	void Score::Draw(int initPosX, int initPosY, int drawInterval, float drawNumScale)
	{
		NumberGraph::Draw(score_, initPosX, initPosY, drawInterval, drawNumScale);
	}

	//破棄処理関数
	void Score::Fin(void)
	{
		if (scoreCharaHandle_ != -1)
		{
			DeleteGraph(scoreCharaHandle_);
		}
		if (bestScoreCharaHandle_ != -1)
		{
			DeleteGraph(bestScoreCharaHandle_);
		}
	}

	//最高記録更新処理
	void Score::UpdateBestScore(void)
	{
		if (bestScore_ < score_)
		{
			bestScore_ = score_;
		}
	}

	//最高記録更新処理
	void Score::UpdateEndlessBestScore(void)
	{
		if (endlessBestScore_ < score_)
		{
			endlessBestScore_ = score_;
		}
	}

	//記録描画
	void Score::DrawScore(int initPosX, int initPosY)
	{
		//「スコア」の文字の画像の描画位置を変えるために最後に描画した数字の位置を保存する
		int lastDrawPosX = initPosX;

		//描画する数字を保存
		unsigned int tempNum = score_;

		//一の位の数字を調べるための変数
		int remainderNum = 0;

		//右から順に全て描画するまで続ける
		while (-1)
		{
			//10で割り、一の位の数字を調べる
			remainderNum = tempNum % 10;

			//一の位の数字を描画
			DrawRotaGraph(lastDrawPosX, initPosY, 1.0f, 0.0f, NumberGraph::GetGraphHandle(remainderNum), true);

			//十の位の数字を一の位に移動する
			tempNum /= 10;

			//全て描画したら脱出
			if (tempNum <= 0)
			{
				break;
			}

			//次の桁の数字を描画するために位置を移動
			lastDrawPosX -= NUMBER_GRAPH::DRAW_POS_INTERVAL;
		}

		//「スコア」の画像描画
		DrawRotaGraph(lastDrawPosX - SCORE::SCORE_CHARA_SUB_POS_X, initPosY, 0.5f, 0.0f, scoreCharaHandle_, true);

	}

	//ベストスコア描画
	void Score::DrawBestScore(void)
	{
		NumberGraph::Draw(bestScore_, SCORE::CLEAR_GAMEOVER::BEST_SCORE_INIT_POS_X, SCORE::CLEAR_GAMEOVER::BEST_SCORE_INIT_POS_Y);

		DrawRotaGraph(SCORE::CLEAR_GAMEOVER::BEST_SCORE_CHARA_POS_X, SCORE::CLEAR_GAMEOVER::BEST_SCORE_CHARA_POS_Y, 1.0f, 0.0f, bestScoreCharaHandle_, true);
	}

	//最高記録描画
	void Score::DrawEndlessBestScore(void)
	{
		NumberGraph::Draw(endlessBestScore_, SCORE::CLEAR_GAMEOVER::BEST_SCORE_INIT_POS_X, SCORE::CLEAR_GAMEOVER::BEST_SCORE_INIT_POS_Y);

		DrawRotaGraph(SCORE::CLEAR_GAMEOVER::BEST_SCORE_CHARA_POS_X, SCORE::CLEAR_GAMEOVER::BEST_SCORE_CHARA_POS_Y, 1.0f, 0.0f, bestScoreCharaHandle_, true);

	}
}
