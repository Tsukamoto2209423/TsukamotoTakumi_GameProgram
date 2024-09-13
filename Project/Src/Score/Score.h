#pragma once

namespace SCORE
{
	//「スコア」の画像パス
	constexpr char SCORE_CHARA_PATH[] = "Data/Image/ScoreChara.png";

	//「ベストスコア」の画像パス
	constexpr char BEST_SCORE_CHARA_PATH[] = "Data/Image/BestScoreChara.png";

	//〇ピクセルごとに数字を描画する
	constexpr int DRAW_POS_INTERVAL = 48;


	//「スコア」の文字が描画されるときに減算する値
	constexpr int SCORE_CHARA_SUB_POS_X = 250;

	//プレイ中に使うもの
	namespace PLAY
	{
		//右端の数字が表示されるXの基準の場所
		constexpr int INIT_POS_X = 1250;

		//右端の数字が表示されるYの基準の場所
		constexpr int INIT_POS_Y = 690;
	}

	//クリアとゲームオーバー中に使うもの
	namespace CLEAR_GAMEOVER
	{
		//右端の数字が表示されるXの基準の場所
		constexpr int INIT_POS_X = 760;

		//右端の数字が表示されるYの基準の場所
		constexpr int INIT_POS_Y = 200;


		//「ベストスコア」の文字が描画されるX軸の場所
		constexpr int BEST_SCORE_CHARA_POS_X = 280;

		//「ベストスコア」の文字が描画されるY軸の場所
		constexpr int BEST_SCORE_CHARA_POS_Y = 280;

		//ベストスコアの右端の数字が表示されるXの基準の場所
		constexpr int BEST_SCORE_INIT_POS_X = 760;

		//ベストスコアの右端の数字が表示されるYの基準の場所
		constexpr int BEST_SCORE_INIT_POS_Y = 280;

	}
}

//ゲーム中の得点クラス
class Score
{
private:
	//現在獲得している得点
	static inline unsigned int score_;

	//最高得点を保存する変数
	static inline unsigned int bestScore_;

	//エンドレスの最高得点を保存する変数
	static inline unsigned int endlessBestScore_;

	//「スコア」の文字の画像を保存する変数
	static inline int scoreCharaHandle_;

	//「ベストスコア」の文字の画像を保存する変数
	static inline int bestScoreCharaHandle_;

public:
	//コンストラクタ
	Score() { score_ = 0; bestScore_ = 0; };

	//デストラクタ
	~Score() {}

	//初期化処理関数
	static void Init(void);

	//読み込み処理関数
	static void Load(void);

	/// <summary>
	/// 描画処理関数
	/// </summary>
	/// <param name="initPosX">一桁目の数字を描画するX軸(横)の場所</param>
	/// <param name="initPosY">一桁目の数字を描画するY軸(縦)の場所</param>
	/// <param name="drawInterval">描画する数字の間隔</param>
	/// <param name="drawNumScale">描画する数字の大きさ</param>
	static void Draw(int initPosX, int initPosY, int drawInterval = SCORE::DRAW_POS_INTERVAL, float drawNumScale = 0.75f);

	//破棄処理関数
	static void Fin(void);

	//最高記録更新処理
	static void UpdateBestScore(void);

	//最高記録更新処理
	static void UpdateEndlessBestScore(void);

	/// <summary>
	/// 記録描画関数
	/// </summary>
	/// <param name="initPosX">一桁目の数字を描画するX軸(横)の場所</param>
	/// <param name="initPosY">一桁目の数字を描画するY軸(縦)の場所</param>
	static void DrawScore(int initPosX, int initPosY);

	//最高記録描画
	static void DrawBestScore(void);

	//最高記録描画
	static void DrawEndlessBestScore(void);

	/// <summary>
	/// スコアを加算する
	/// </summary>
	/// <param name="addScore">追加するスコア</param>
	static inline void AddScore(int addScore)
	{
		score_ += addScore;
	}

	/// <summary>
	/// スコアを強制的に設定する
	/// </summary>
	/// <param name="setScore">設定するスコア</param>
	static inline void SetScore(int setScore)
	{
		score_ = setScore;
	}

	/// <summary>
	/// スコアを取得する
	/// </summary>
	/// <returns>現在のスコア</returns>
	static inline int GetScore(void)
	{
		return score_;
	}

	static inline int GetBestScore(void) { return bestScore_; }

	static inline void SetBestScore(int setScore) { bestScore_ = setScore; }

};