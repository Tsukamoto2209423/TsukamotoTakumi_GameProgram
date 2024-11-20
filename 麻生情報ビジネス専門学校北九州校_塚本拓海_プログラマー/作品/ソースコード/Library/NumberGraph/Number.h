#pragma once

//定義群
namespace NUMBER_GRAPH
{
	//画像パス
	constexpr char PATH[] = { "Data/Image/Number_0_to_9.png" };

	//0～9の合計10個
	constexpr int ALL_NUM = 10;

	//画像1枚の大きさ
	constexpr int SIZE = 64;

	//1桁ずつ描画するときに空ける間隔
	constexpr int DRAW_POS_INTERVAL = 48;

}

//0～9の数字の画像を保存するクラス
class NumberGraph final
{
private:
	//0～9の数字の画像を保存するハンドル
	static inline int graphHandle_[NUMBER_GRAPH::ALL_NUM];

public:
	/// <summary>
	/// 一桁目の数字から順に描画する関数
	/// </summary>
	/// <param name="drawNum">描画する数</param>
	/// <param name="initPosX">一桁目の数字のX軸の位置</param>
	/// <param name="initPosY">一桁目の数字のY軸の位置</param>
	/// <param name="drawInterval">描画する数字の間隔</param>
	/// <param name="drawNumScale">描画する数字の大きさ</param>
	static void Draw(int drawNum, int initPosX, int initPosY,int drawInterval = NUMBER_GRAPH::DRAW_POS_INTERVAL,float drawNumScale = 0.75f);

	//初期化処理関数
	static void Init(void);

	//読み込み処理関数
	static void Load(void);

	//破棄処理関数
	static void Fin(void);

	//0～9の数字の画像を保存するハンドルを取得
	static inline int* GetGraphHandle(void) { return graphHandle_; }

	//0～9の数字の画像を保存するハンドルの要素取得
	static inline int GetGraphHandle(int index) { return graphHandle_[index]; }

};
