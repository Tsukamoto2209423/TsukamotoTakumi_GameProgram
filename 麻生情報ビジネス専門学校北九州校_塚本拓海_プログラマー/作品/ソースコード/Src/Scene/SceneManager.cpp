#include <memory>
#include <functional>
#include <unordered_map>
#include <string>

#include "SceneManager.h"
#include "SceneTitle.h"
#include "ScenePlay.h"
#include "SceneClear.h"
#include "SceneGameOver.h"

namespace BOUDAMA
{
	//コンストラクタ
	SceneManager::SceneManager(void)
	{
		currentSceneState_ = SCENE_STATE::INIT;
	}

	//デストラクタ
	SceneManager::~SceneManager(void)
	{

	}

	//場面主処理関数
	void SceneManager::Loop(void)
	{
		//フェードが終わっていない場合はフェード処理をする
		if (!fade_.IsEnd())
		{
			fade_.Step();

			return;
		}

		//場面に応じた関数ポインタ実行
		sceneObjectPointer_->Loop(currentSceneState_);

		//次場面判定関数が真の場合、場面に応じて切り替え
		if (sceneObjectPointer_->CanGoToNextScene(currentSceneState_))
		{
			//場面状況切り替え処理
			SceneChange();

			if (currentSceneState_ == SCENE_STATE::INIT)
			{
				SceneCreate();
			}

			//STEPに変更された場合は実行しない
			if (currentSceneState_ != SCENE_STATE::STEP)
			{
				fade_.Change();
			}
		}
	}

	//初期化処理関数
	void SceneManager::Init(void)
	{
		sceneObjectPointer_ = std::make_unique<SceneTitle>();
		currentSceneState_ = SCENE_STATE::INIT;

		fade_.Init();
		fade_.Load();

	}

	//描画処理関数
	void SceneManager::Draw(void)
	{
		//場面に応じた描画処理
		sceneObjectPointer_->Draw();

		if (currentSceneState_ != SCENE_STATE::STEP)
		{
			fade_.Draw();
		}
	}

	//破棄処理関数
	void SceneManager::Fin(void)
	{
		sceneObjectPointer_->Fin();
		fade_.Fin();
	}

	//場面作成関数
	void SceneManager::SceneCreate(void)
	{
		//シーン一覧
		static const std::vector<std::function<std::unique_ptr<SceneBase>()>> sceneVector =
		{
			//タイトル
			[]() {return std::make_unique<SceneTitle>(); } ,

			//普通難易度でゲームプレイ
			[]() {return std::make_unique<ScenePlay>(SCENE::NORMAL_PLAY); } ,

			//難しい難易度でゲームプレイ
			[]() {return std::make_unique<ScenePlay>(SCENE::HARD_PLAY);	 },

			//エンドレスでゲームプレイ
			[]() {return std::make_unique<ScenePlay>(SCENE::ENDLESS_PLAY);	} ,

			//クリア
			[]() {return std::make_unique<SceneClear>(); } ,

			//エンドレスモードでの結果表示画面
			[]() {return std::make_unique<SceneClear>(SCENE::RESULT); } ,

			//ゲームオーバー
			[]() {return std::make_unique<SceneGameOver>(); }
		};

		//次のシーンを生成する
		sceneObjectPointer_ = sceneVector[static_cast<int>(sceneObjectPointer_->GetNextSceneNum())]();

	}

	//場面切り替え関数
	void SceneManager::SceneChange(void)
	{
		//INIT→STEP→FIN→INIT→…の順で進める
		currentSceneState_ == SCENE_STATE::FIN ? currentSceneState_ = SCENE_STATE::INIT : ++currentSceneState_;
	}
}
