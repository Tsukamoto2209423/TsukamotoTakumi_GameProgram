#pragma once

#include <vector>
#include <memory>
#include "Scene/SceneBase.h"

//ゲームオーバー画面クラスで使う定義
namespace GAME_OVER
{
	//画像一覧表のパス
	constexpr char PATH[] = "Data/Image/GameOver/GameOverImageList.csv";

	constexpr Vector2D CHARA_POS = { 220.0f,0.0f };

	enum IMAGE
	{
		//背景画像
		BACK_GROUND,

		//「ゲームオーバー」の画像
		GAME_OVER_CHARA,

		//落ち込んでいるキャラクターの画像
		SYOBON_IMAGE,

		//画像の最大数
		ALL_NUM
	};

}

//ゲームオーバークラス
class SceneGameOver : public SceneBase
{
public:
	//コンストラクタ
	SceneGameOver(void);
	//デストラクタ
	~SceneGameOver(void);

	//描画処理
	void Draw(void) override;

private:
	std::vector<int> handles_;

	//初期化処理関数
	void Init(void) override;

	//読み込み処理関数
	void Load(void) override;

	//行動処理関数
	void Step(void) override;

	//破棄処理関数
	void Fin(void) override;

	/// <summary>
	/// 次のシーンに進むか判定する関数
	/// </summary>
	/// <param name="state">現在のシーンの状態</param>
	/// <returns>true:次のシーンに移行 false:現在のシーンのまま</returns>
	bool CanGoToNextScene(const SCENE_STATE state) const override;

	/// <summary>
	/// 次のシーン代入用関数
	/// </summary>
	/// <returns>次のシーン</returns>
	inline SCENE GetNextSceneNum(void) const override;
};
