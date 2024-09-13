#pragma once

#include <memory>
#include "Scene.h"
#include <Vector/Vector2D.h>

//場面用抽象クラス
class SceneBase
{
protected:

public:
	SceneBase() {};

	virtual ~SceneBase() {};

	/// <summary>
	/// 初期化・本編・破棄の分岐処理	
	/// </summary>
	/// <param name="sceneState">
	/// 現在のシーンの状態
	/// </param>
	virtual void Loop(const SCENE_STATE sceneState);

	//描画処理
	virtual void Draw(void) = 0;

	//初期化関数
	virtual void Init(void) = 0;

	//読み込み処理関数
	virtual void Load(void) = 0;

	//行動処理関数
	virtual void Step(void) = 0;

	//破棄処理関数
	virtual void Fin(void) = 0;

	/// <summary>
	/// 次のシーンに進むか判定する関数
	/// </summary>
	/// <param name="state">現在のシーンの状態</param>
	/// <returns>true:次のシーンに移行 false:現在のシーンのまま</returns>
	virtual bool CanGoToNextScene(const SCENE_STATE state) const = 0;

	/// <summary>
	/// 次のシーン代入用関数
	/// </summary>
	/// <returns>次のシーン</returns>
	virtual inline SCENE GetNextSceneNum(void) const = 0;
};
