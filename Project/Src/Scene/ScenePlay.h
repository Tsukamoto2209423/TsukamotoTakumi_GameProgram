#pragma once

#include <memory>
#include "SceneBase.h"
#include "Player/Player.h"
#include "Enemy/EnemyManager.h"
#include "Collision/CollisionManager.h"
#include "Sound/Sound.h"
#include "Camera/Camera.h"
#include "Field/Field.h"
#include "SkyBox/SkyBox.h"
#include "Substance/SubstanceManager.h"
#include "Score/Score.h"
#include "TimeLimit/TimeLimit.h"

//ゲームプレイクラス
class ScenePlay : public SceneBase
{
public:
	//コンストラクタ
	ScenePlay(void);
	ScenePlay(const SCENE difficulty) : playDifficulty_(difficulty) { shadowHandle_ = -1; }

	//デストラクタ
	~ScenePlay(void);

	//描画処理
	void Draw(void) override;

private:
	//影を描画するときにつかうハンドル
	int shadowHandle_;

	//難易度選択用変数
	SCENE playDifficulty_;

	//操作するプレイヤー
	std::shared_ptr<Player> player_;

	//プレイヤーが移動するフィールド
	Field field_;

	//天球
	SkyBox sky_;

	//制限時間計測用変数
	TimeLimit timeLimit_;

	//敵管理用変数
	EnemyManager enemyManager_;

	//アイテム管理用変数
	ItemManager itemManager_;

	//物質クラス管理用変数
	SubstanceManager substanceManager_;

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
	inline SCENE GetNextSceneNum(void) const noexcept override;

};
