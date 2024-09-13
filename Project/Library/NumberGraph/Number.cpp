#include "Number.h"
#include "DxLib.h"

//初期化処理関数
void NumberGraph::Init(void)
{
	for (int graphHandle : graphHandle_)
	{
		graphHandle = -1;
	}
}

//読み込み処理関数
void NumberGraph::Load(void)
{
	LoadDivGraph(NUMBER_GRAPH::PATH, NUMBER_GRAPH::ALL_NUM, 10, 1, 64, 64, graphHandle_);
}

//一桁目の数字から左へ順に描画する関数
void NumberGraph::Draw(int drawNum, int initPosX, int initPosY, int drawInterval, float drawNumScale)
{
	//描画する数字を保存
	int tempNum = drawNum;

	//一の位の数字を調べるための変数
	int remainderNum = 0;

	//回った回数を保存する変数
	int num = 0;

	//右から順に全て描画するまで続ける
	while(-1)
	{
		//10で割り、一の位の数字を調べる
		remainderNum = tempNum % 10;
		//一の位の数字を描画
		DrawRotaGraph(initPosX - (drawInterval * num), initPosY, drawNumScale, 0.0f, graphHandle_[remainderNum], true);
		//十の位の数字を一の位に移動する
		tempNum /= 10;

		//全て描画したら戻る
		if (tempNum <= 0)
		{
			return;
		}

		//次の場所に描画するためにインクリメント
		++num;
	}
}


void NumberGraph::Fin(void)
{
	//画像破棄処理
	for (int graphHandle : graphHandle_)
	{
		if (graphHandle != -1)
		{
			DeleteGraph(graphHandle);
			graphHandle = -1;
		}
	}
}