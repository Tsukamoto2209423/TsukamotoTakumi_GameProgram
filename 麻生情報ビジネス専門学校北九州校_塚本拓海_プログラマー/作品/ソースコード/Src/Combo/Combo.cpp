#include "Combo.h"
#include <DxLib.h>
#include <NumberGraph/Number.h>

namespace BOUDAMA
{
	//コンストラクタ
	Combo::Combo()
	{
		charaHandle_ = -1;
		presiousCharaHandle_ = -1;
		comboNum_ = 0;
		countTime_ = 0;
		drawInterval_ = 0;
		graphScale_ = 0.0f;
	}

	//デストラクタ
	Combo::~Combo()
	{

	}

	//初期化処理関数
	void Combo::Init(void)
	{
		charaHandle_ = -1;
		comboNum_ = 0;
		countTime_ = COMBO::MAX_COUNT_TIME;
		drawInterval_ = static_cast<int>(NUMBER_GRAPH::SIZE * COMBO::INIT_SCALE);
		graphScale_ = COMBO::INIT_SCALE;
	}

	//読み込み処理
	void Combo::Load(void)
	{
		if (charaHandle_ == -1)
		{
			charaHandle_ = LoadGraph(COMBO::PATH);
			presiousCharaHandle_ = LoadGraph(COMBO::PRE_PATH);
		}
	}

	//行動処理関数
	void Combo::Step(void)
	{
		//コンボ中なら
		if (comboNum_ > 0)
		{
			//時間を減らす
			--countTime_;
		}

		//0になったら
		if (countTime_ <= 0)
		{
			//初期化
			comboNum_ = 0;
			countTime_ = COMBO::MAX_COUNT_TIME;
		}


		//ある程度コンボしたら画像を大きくする
		if (COMBO::ADD_SCALE_COMBO_NUM <= comboNum_)
		{
			graphScale_ = COMBO::BIG_SCALE;
			//画像を大きくしたので間隔を大きくする
			drawInterval_ = static_cast<int>(NUMBER_GRAPH::SIZE * graphScale_);
		}
		//コンボしていない場合は通常の大きさ
		else
		{
			graphScale_ = COMBO::INIT_SCALE;
			drawInterval_ = static_cast<int>(NUMBER_GRAPH::SIZE * graphScale_);
		}

	}

	//描画処理関数
	void Combo::Draw(void)
	{
		//コンボが発生していないなら描画しない
		if (comboNum_ > 0)
		{
			NumberGraph::Draw(comboNum_, COMBO::INIT_POS_X, COMBO::INIT_POS_Y, drawInterval_, graphScale_);

			//コンボ数に応じて描画する文字を決める
			comboNum_ >= 20 ?
				DrawRotaGraph(COMBO::INIT_POS_X + 100, COMBO::INIT_POS_Y, graphScale_, 0.0f, presiousCharaHandle_, true)
				: DrawRotaGraph(COMBO::INIT_POS_X + 100, COMBO::INIT_POS_Y, graphScale_, 0.0f, charaHandle_, true);
		}
	}

	//破棄処理関数
	void Combo::Fin(void)
	{
		DeleteGraph(charaHandle_);
		DeleteGraph(presiousCharaHandle_);

		comboNum_ = 0;
		countTime_ = COMBO::MAX_COUNT_TIME;
	}
}
