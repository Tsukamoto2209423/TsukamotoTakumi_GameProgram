#pragma once

#include <vector>
#include "FadeParameter.h"

//フェードイン・フェードアウト用関数
class Fade
{
private:
	//状態
	FADE::STATE state_;

	//α値(透過度)
	int alphaValue_;

	//位置
	int posX_;

	//画像の添え字
	int handleIndex_;

	//画像ハンドルを保存するベクター
	std::vector<int> syobonHandles_;

	//回転角度
	float rotAngle;

	//フェードイン・フェードアウト処理が終わったか
	bool isEnd_;

public:
	//コンストラクタ
	Fade();

	//デストラクタ
	~Fade();

	//初期化処理関数
	void Init(void);

	//読み込み処理関数
	void Load(void);

	//更新処理関数
	void Step(void);

	//描画処理
	void Draw(void);

	//破棄処理関数
	void Fin(void);

	//フェードの状態変更
	void Change(void);

	//フェードインかフェードアウトが終わったか判定
	bool IsEnd(void) const noexcept;
};