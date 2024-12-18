#pragma once

namespace BOUDAMA
{
	namespace SOUND
	{
		//音番号情報
		enum class BGM
		{
			//タイトル画面
			TITLE,
			//ゲームプレイ中
			PLAY,

			//総数
			NUM
		};

		//効果音
		enum class SE
		{
			//くっつき時の効果音
			ATTACHED = BGM::NUM,

			//ダメージを受けたときの効果音
			DAMAGE,

			//プレイヤーが死んだときの効果音
			RED_DISSOLVE,

			//敵が死んだときの効果音
			ENEMY_DEATH,

			//敵がプレイヤーを発見したときの効果音
			FIND_OUT,

			//決定ボタンを押したときの効果音
			DESIDE,

			//ゲームが終わった時の効果音
			GAME_FINISH,

			//キャンセル音
			CANCEL,

			//フェードイン・フェードアウト中に鳴る効果音
			SCENE_CHANGE,

			//総数
			NUM
		};

		//効果音の合計
		constexpr int ALL_SOUND_NUM = static_cast<int>(SE::NUM);

		//音情報パス
		constexpr char PATH[] = "Data/Sound/SoundList.csv";

	}
}
