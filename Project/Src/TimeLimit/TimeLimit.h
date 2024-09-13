#pragma once

#include <chrono>

//システムクロック使用簡略化
using std::chrono::system_clock;

//制限時間クラス
class TimeLimit
{
private:
	//制限時間計測用(ミリ秒)
	int count_;

	//「のこり」の画像描画用ハンドル
	int characterHandle_;

	//「∞」の画像ハンドル
	int infinityHandle_;

	// 計測開始時間
	system_clock::time_point start_;

	// 計測終了時間
	system_clock::time_point end_;

	//エンドレスか
	bool isEndless_;

public:
	//コンストラクタ
	TimeLimit();

	//デストラクタ
	~TimeLimit();

	//初期化処理関数
	void Init(void);

	//読み込み処理関数
	void Load(void);

	//行動処理関数
	void Step(void);

	//描画処理関数
	void Draw(void);

	//破棄処理関数
	void Fin(void);

	//制限時間計測用の変数取得
	inline int GetTimeLimitCount(void) const { return count_; }

	//制限時間計測用の変数設定
	inline void SetTimeLimitCount(int time) { characterHandle_ = time; }

	//「のこり」の画像描画用ハンドル取得
	inline int GetTimeLimitCharacter(void) const { return characterHandle_; }

	//「のこり」の画像描画用ハンドル設定
	inline void SetTimeLimitCharacter(int handle) { characterHandle_ = handle; }

	//エンドレスモードか
	inline void IsEndless(bool isEndless) { isEndless_ = isEndless; }
};