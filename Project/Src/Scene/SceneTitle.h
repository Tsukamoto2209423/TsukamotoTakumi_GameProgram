#pragma once

#include <vector>
#include <memory>
#include "Scene/SceneBase.h"
#include <Common.h>

namespace BOUDAMA
{
	//タイトル画面クラスで使う定義
	namespace TITLE
	{
		//画像一覧表のパス
		constexpr char PATH[] = "Data/Image/Title/TitleImageList.csv";

		//上下に揺れる画像が1フレームに進む距離 = AMPLITUDE × sinθ
		constexpr float AMPLITUDE = 21.5f;

		//選択している画像の中心点から〇ピクセル右に「←」の画像を表示させる
		constexpr float ARROW_ADD_X_POS = 350.0f;

		//「ゲームスタート！」の画像の位置
		constexpr Vector2D GAME_START_POS = { Common::WINDOW_WIDTH_HALF_F,Common::WINDOW_HEIGHT_HALF_F };

		//「ステージせんたく」の画像の位置
		constexpr Vector2D STAGE_SELECT_POS = { Common::WINDOW_WIDTH_HALF_F,250.0f };

		//「あそびかた」の画像の位置
		constexpr Vector2D HOW_TO_PLAY_POS = { Common::WINDOW_WIDTH_HALF_F, 500.0f };

		//「ノーマル」の画像
		constexpr Vector2D NORMAL_POS = { Common::WINDOW_WIDTH_HALF_F,120.0f };

		//「ハード」の画像
		constexpr Vector2D HARD_POS = { Common::WINDOW_WIDTH_HALF_F,360.0f };

		//「エンドレス」の画像
		constexpr Vector2D ENDLESS_POS = { Common::WINDOW_WIDTH_HALF_F,600.0f };

		//「エンターですすむ」の画像
		constexpr Vector2D PROCEED_POS = { Common::WINDOW_WIDTH_F - 120.0f, 620.0f };

		//「BACKSPACEでもどる」の画像
		constexpr Vector2D BACK_POS = { Common::WINDOW_ORIGIN + 120.0f, 620.0f };

		//タイトルで使う画像一覧
		enum IMAGE
		{
			//「ボウダマ！」の画像
			MAIN_TITLE,

			//「エンターキーを押すとスタート！」の画像
			THE_ENTER,

			//背景画像
			BACK_GROUND,

			//「ゲームスタート！」の画像
			GAME_START,

			//「ステージせんたく」の画像
			STAGE_SELECT,

			//「あそびかた」の画像
			HOW_TO_PLAY,

			//「ノーマル」の画像
			NORMAL,

			//「ハード」の画像
			HARD,

			//「エンドレス」の画像
			ENDLESS,

			//「エンターですすむ」の画像
			PROCEED,

			//「BACKSPACEでもどる」の画像
			BACK,

			//「←」の画像
			ARROW,

			//説明画像
			EXPLAIN_1,
			EXPLAIN_2,
			EXPLAIN_3,
			EXPLAIN_4,

			//説明画像の最大数
			ALL_NUM
		};

		//タイトル画面の状態
		enum class STATE
		{
			TITLE,
			MODE_SELECT,
			STAGE_SELECT,
			EXPLAIN,

			NUM
		};

	}

	//タイトルクラス
	class SceneTitle final : public SceneBase
	{
	public:
		//コンストラクタ
		SceneTitle(void);
		//デストラクタ
		~SceneTitle(void);

		//描画処理
		void Draw(void) override;

	private:
		//画像ハンドルを保存する配列
		std::vector<int> handles_;

		//タイトル画面の状態
		TITLE::STATE state_;

		//タイトル画面で現在選択している選択肢の状態
		TITLE::IMAGE selectState_;

		//ゲームの難易度を返すときにつかう変数
		SCENE returnDifficulty_;

		//選択肢を指すときに使う「←」の画像の位置
		Vector2D arrowPos_;

		//説明画像の添え字を保存する変数
		int explainHandleIndex_;

		//画像を上下に揺らすときに使う変数
		float theta_;

		//次の場面に行っていいか
		bool isGotoNextScene_;

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