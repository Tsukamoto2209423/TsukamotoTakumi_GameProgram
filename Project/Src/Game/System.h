#pragma once

#include "DxLib.h"
#include "Scene/SceneManager.h"

//ゲーム処理統合クラス
class GameSystem
{
private:
	//ゲーム終了判定
	static inline bool isGameEnd_;

	//場面管理
	static inline SceneManager sceneManager_;

	//コンストラクタ
	GameSystem() = delete;

	//デストラクタ
	~GameSystem() = delete;

public:
	//ゲーム起動関数
	static void Start();

	//本編統括処理関数
	static void MainLoop();

	//破棄関数
	static void Fin();

private:
	//初期化関数
	static void Init();		

	//本編処理関数
	static void Step();			

public:
	//ゲーム終了判定取得
	static inline bool GetGameEnd() { return isGameEnd_; }

	//ゲーム終了
	static inline void SetGameEnd() { isGameEnd_ = true; }
};