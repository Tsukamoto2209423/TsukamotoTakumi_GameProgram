#pragma once

#include <memory>
#include "SceneBase.h"
#include "Scene.h"
#include "Fade/Fade.h"

namespace BOUDAMA
{
	//場面管理用クラス
	class SceneManager final
	{
	public:
		//コンストラクタ
		SceneManager(void);

		//デストラクタ
		~SceneManager(void);

		//本編処理関数
		void Loop(void);

		//初期化処理関数
		void Init(void);

		//描画処理関数
		void Draw(void);

		//破棄処理関数
		void Fin(void);

	private:
		//場面作成関数
		void SceneCreate(void);

		//場面切り替え関数
		void SceneChange(void);

		//場面判断用変数
		SCENE_STATE currentSceneState_;

		//場面実行用
		std::unique_ptr<SceneBase> sceneObjectPointer_;

		//フェード用
		Fade fade_;

	};
}
