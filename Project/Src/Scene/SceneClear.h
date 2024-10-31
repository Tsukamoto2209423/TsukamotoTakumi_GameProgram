#pragma once

#include <vector>
#include <memory>
#include "Scene/SceneBase.h"
#include "Common/Common.h"

namespace BOUDAMA
{
	namespace CLEAR
	{
		//クリア画面で使う画像のパスを纏めたCSVファイルのパス
		constexpr char PATH[] = "Data/Image/Clear/GameClearImageList.csv";

		//クリア画面に表示する「ゲームクリア」の文字の位置
		constexpr Vector2D CHARA_POS = { Common::WINDOW_WIDTH_HALF_F,260.0f };

		//クリア画面に表示する「しゅうりょう」の文字の位置
		constexpr Vector2D END_CHARA_POS = { Common::WINDOW_WIDTH_HALF_F,80.0f };

		//クリア画面の画像一覧
		enum IMAGE
		{
			//背景画像
			BACK_GROUND,

			//「ゲームクリア」の画像
			GAME_CLEAR_CHARA,

			//喜んでいるキャラクターの画像
			SYOBON_IMAGE,

			//「しゅうりょう！」の文字画像
			END_CHARA,

			//画像の最大数
			ALL_NUM
		};
	}

	//クリアクラス
	class SceneClear final : public SceneBase
	{
	public:
		//コンストラクタ
		SceneClear(void);

		//コンストラクタ
		SceneClear(const SCENE state) : clearState_(state) {}

		//デストラクタ
		~SceneClear(void);

		//描画処理
		void Draw(void) override;

	private:
		//画像ハンドル
		std::vector<int> handles_;

		//クリアしたときの状態
		SCENE clearState_;

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
}
