#pragma once

namespace COMBO
{
	//「コンボ」の画像パス
	constexpr char PATH[] = "Data/Image/combo_chara_normal.PNG";

	//一定以上コンボすると表示される色違いの「コンボ」の画像パス
	constexpr char PRE_PATH[] = "Data/Image/combo_chara_presious.PNG";

	//コンボが途切れるまでの時間
	constexpr int MAX_COUNT_TIME = 300;

	//右端の数字が表示されるXの基準の場所
	constexpr int INIT_POS_X = 150;

	//右端の数字が表示されるYの基準の場所
	constexpr int INIT_POS_Y = 460;

	//描画する画像を大きくするコンボ数
	constexpr int ADD_SCALE_COMBO_NUM = 20;

	//最初の画像倍率
	constexpr float INIT_SCALE = 0.75f;

	//大きくなった時の画像倍率
	constexpr float BIG_SCALE = 1.0f;

}

//コンボ数計測クラス
class Combo
{
private:
	//「コンボ！」の画像ハンドル
	int charaHandle_;

	//一定以上コンボすると表示される色違いの「コンボ！」の画像ハンドル
	int presiousCharaHandle_;

	//コンボ数計測用変数
	int comboNum_;

	//コンボが途切れるまでの時間を計測する変数
	int countTime_;

	//画像を描画する際に空ける幅
	int drawInterval_;

	//画像の大きさ
	float graphScale_;

public:
	//コンストラクタ
	Combo();

	//デストラクタ
	~Combo();

	//初期化処理関数
	void Init(void);

	//読み込み処理
	void Load(void);

	//行動処理関数
	void Step(void);

	//描画処理関数
	void Draw(void);

	//破棄処理関数
	void Fin(void);


	//現在のコンボ数取得
	inline int GetComboNum(void) const { return comboNum_; }

	//現在のコンボ数設定
	inline void SetComboNum(int num) { comboNum_ = num; }

	//現在のコンボ数+1
	inline void AddComboNum(void) 
	{ 
		//コンボ数を追加し、時間も初期化
		++comboNum_;
		countTime_ = COMBO::MAX_COUNT_TIME;
	};


	//コンボが途切れるまでの時間取得
	inline int GetComboCountTime(void) const { countTime_; }

	//コンボが途切れるまでの時間設定
	inline void SetComboCountTime(int num) { countTime_ = num; }

};