#include "SceneTitle.h"
#include <fstream>
#include <DxLib.h>
#include "Input/KeyBoard/InputKeyBoard.h"
#include "Input/GamePad/GamePad.h"
#include "Common.h"
#include <Sound/Sound.h>
#include "Sound/SoundParameter.h"
#include "ScenePlay.h"
#include "Math/MyMath.h"
#include <FileLoader/CSVFileLoader.h>
#include <Input/Input.h>

namespace BOUDAMA
{
#define IMAGE TITLE::IMAGE

	//コンストラクタ
	SceneTitle::SceneTitle(void)
	{
		//初期化
		theta_ = 0.0f;
		state_ = TITLE::STATE::TITLE;
		selectState_ = IMAGE::STAGE_SELECT;
		returnDifficulty_ = SCENE::NORMAL_PLAY;
		arrowPos_ = { TITLE::STAGE_SELECT_POS.x + TITLE::ARROW_ADD_X_POS ,TITLE::STAGE_SELECT_POS.y };
		explainHandleIndex_ = 0;
		isGotoNextScene_ = false;
	}

	//デストラクタ
	SceneTitle::~SceneTitle(void)
	{
		//破棄処理
	}

	//描画処理関数
	void SceneTitle::Draw(void)
	{
		if (handles_.empty())
		{
			return;
		}

		//タイトル画面表示
		if (state_ == TITLE::STATE::TITLE)
		{
			DrawGraph(Common::WINDOW_ORIGIN, Common::WINDOW_ORIGIN, handles_[IMAGE::BACK_GROUND], true);
			DrawRotaGraphF(Common::WINDOW_WIDTH_HALF_F, Common::WINDOW_HEIGHT_HALF_F + TITLE::AMPLITUDE * sinf(theta_), 1.0f, 0.0f, handles_[IMAGE::MAIN_TITLE], true);
			DrawRotaGraphF(Common::WINDOW_WIDTH_HALF_F, Common::WINDOW_HEIGHT_HALF_F + TITLE::AMPLITUDE * sinf(theta_), 1.0f, 0.0f, handles_[IMAGE::THE_ENTER], true);

			return;
		}

		//「ステージせんたく」か「あそびかた」を選択する画面表示
		if (state_ == TITLE::STATE::MODE_SELECT)
		{
			DrawGraph(Common::WINDOW_ORIGIN, Common::WINDOW_ORIGIN, handles_[IMAGE::BACK_GROUND], true);
			DrawRotaGraphF(TITLE::STAGE_SELECT_POS.x, TITLE::STAGE_SELECT_POS.y, 1.0f, 0.0f, handles_[IMAGE::STAGE_SELECT], true);
			DrawRotaGraphF(TITLE::HOW_TO_PLAY_POS.x, TITLE::HOW_TO_PLAY_POS.y, 1.0f, 0.0f, handles_[IMAGE::HOW_TO_PLAY], true);

			DrawRotaGraphF(TITLE::PROCEED_POS.x, TITLE::PROCEED_POS.y, 1.0f, 0.0f, handles_[IMAGE::PROCEED], true);
			DrawRotaGraphF(TITLE::BACK_POS.x, TITLE::BACK_POS.y, 1.0f, 0.0f, handles_[IMAGE::BACK], true);

			DrawRotaGraphF(arrowPos_.x, arrowPos_.y, 1.0f, 0.0f, handles_[IMAGE::ARROW], true);

			return;
		}

		//「ノーマル」か「ハード」か「エンドレス」を選択する画面表示
		if (state_ == TITLE::STATE::STAGE_SELECT)
		{
			DrawGraph(Common::WINDOW_ORIGIN, Common::WINDOW_ORIGIN, handles_[IMAGE::BACK_GROUND], true);
			DrawRotaGraphF(TITLE::NORMAL_POS.x, TITLE::NORMAL_POS.y, 1.0f, 0.0f, handles_[IMAGE::NORMAL], true);
			DrawRotaGraphF(TITLE::HARD_POS.x, TITLE::HARD_POS.y, 1.0f, 0.0f, handles_[IMAGE::HARD], true);
			DrawRotaGraphF(TITLE::ENDLESS_POS.x, TITLE::ENDLESS_POS.y, 1.0f, 0.0f, handles_[IMAGE::ENDLESS], true);

			DrawRotaGraphF(TITLE::PROCEED_POS.x, TITLE::PROCEED_POS.y, 1.0f, 0.0f, handles_[IMAGE::PROCEED], true);
			DrawRotaGraphF(TITLE::BACK_POS.x, TITLE::BACK_POS.y, 1.0f, 0.0f, handles_[IMAGE::BACK], true);

			DrawRotaGraphF(arrowPos_.x, arrowPos_.y, 1.0f, 0.0f, handles_[IMAGE::ARROW], true);

			return;
		}

		//説明画像表示
		if (state_ == TITLE::STATE::EXPLAIN)
		{
			DrawGraph(Common::WINDOW_ORIGIN, Common::WINDOW_ORIGIN, handles_[explainHandleIndex_], true);

			return;
		}
	}

	//初期化処理関数
	void SceneTitle::Init(void)
	{
		Load();

		state_ = TITLE::STATE::TITLE;

		explainHandleIndex_ = IMAGE::EXPLAIN_1;

		SoundManager::GetInstance()->PlaySoundData(SOUND::BGM::TITLE, DX_PLAYTYPE_LOOP);

	}

	//読み込み処理関数
	void SceneTitle::Load(void)
	{
		//ハンドル未設定の場合、読み込む
		if (handles_.empty())
		{
			CSV_LOADER::LoadHandle(TITLE::PATH, handles_);
		}
	}

	//行動処理関数
	void SceneTitle::Step(void)
	{
		//タイトル画面表示
		if (state_ == TITLE::STATE::TITLE)
		{
			//決定が押された場合
			if (Input::IsKeyRelease(GAME_INPUT::ENTER))
			{
				//「ステージせんたく」か「あそびかた」を選択する画面に移動
				state_ = TITLE::STATE::MODE_SELECT;

				//「ステージせんたく」にカーソルを合わせる
				selectState_ = IMAGE::STAGE_SELECT;
				arrowPos_ = { TITLE::STAGE_SELECT_POS.x + TITLE::ARROW_ADD_X_POS ,TITLE::STAGE_SELECT_POS.y };

				SoundManager::GetInstance()->PlaySoundData(SOUND::SE::DESIDE, DX_PLAYTYPE_BACK);
			}

			theta_ = theta_ >= MY_MATH::TWO_PI ? 0.0f : theta_ + (MY_MATH::PI * 0.01f);

			return;
		}

		//「ステージせんたく」か「あそびかた」を選択する画面
		if (state_ == TITLE::STATE::MODE_SELECT)
		{
			//戻るが押された場合
			if (Input::IsKeyRelease(GAME_INPUT::BACK))
			{
				//タイトル画面に戻る
				state_ = TITLE::STATE::TITLE;
				selectState_ = IMAGE::NORMAL;
				arrowPos_ = { TITLE::NORMAL_POS.x + TITLE::ARROW_ADD_X_POS ,TITLE::NORMAL_POS.y };
				SoundManager::GetInstance()->PlaySoundData(SOUND::SE::CANCEL, DX_PLAYTYPE_BACK);
			}

			//「ステージせんたく」にカーソルが合っている場合
			if (selectState_ == IMAGE::STAGE_SELECT)
			{
				//上か下が押された場合
				if (Input::IsKeyRelease(GAME_INPUT::UP) || Input::IsKeyRelease(GAME_INPUT::DOWN))
				{
					//「あそびかた」に移動
					selectState_ = IMAGE::HOW_TO_PLAY;
					arrowPos_ = { TITLE::HOW_TO_PLAY_POS.x + TITLE::ARROW_ADD_X_POS ,TITLE::HOW_TO_PLAY_POS.y };
				}

				//決定が押された場合
				if (Input::IsKeyRelease(GAME_INPUT::ENTER))
				{
					state_ = TITLE::STATE::STAGE_SELECT;
					selectState_ = IMAGE::NORMAL;
					arrowPos_ = { TITLE::NORMAL_POS.x + TITLE::ARROW_ADD_X_POS ,TITLE::NORMAL_POS.y };

					SoundManager::GetInstance()->PlaySoundData(SOUND::SE::DESIDE, DX_PLAYTYPE_BACK);
				}

				return;
			}

			//「あそびかた」にカーソルが合っている場合
			if (selectState_ == IMAGE::HOW_TO_PLAY)
			{
				//上か下が押された場合
				if (Input::IsKeyRelease(GAME_INPUT::UP) || Input::IsKeyRelease(GAME_INPUT::DOWN))
				{
					//「ステージせんたく」に移動
					selectState_ = IMAGE::STAGE_SELECT;
					arrowPos_ = { TITLE::STAGE_SELECT_POS.x + TITLE::ARROW_ADD_X_POS ,TITLE::STAGE_SELECT_POS.y };
				}

				//決定が押された場合
				if (Input::IsKeyRelease(GAME_INPUT::ENTER))
				{
					state_ = TITLE::STATE::EXPLAIN;
					SoundManager::GetInstance()->PlaySoundData(SOUND::SE::DESIDE, DX_PLAYTYPE_BACK);
				}
				return;
			}


			return;
		}

		//「ノーマル」か「ハード」か「エンドレス」を選択する画面
		if (state_ == TITLE::STATE::STAGE_SELECT)
		{
			//戻るが押された場合
			if (Input::IsKeyRelease(GAME_INPUT::BACK))
			{
				//タイトル画面に戻る
				state_ = TITLE::STATE::MODE_SELECT;
				selectState_ = IMAGE::STAGE_SELECT;
				arrowPos_ = { TITLE::STAGE_SELECT_POS.x + TITLE::ARROW_ADD_X_POS ,TITLE::STAGE_SELECT_POS.y };
				SoundManager::GetInstance()->PlaySoundData(SOUND::SE::CANCEL, DX_PLAYTYPE_BACK);
			}

			//「ノーマル」にカーソルが合っている場合
			if (selectState_ == IMAGE::NORMAL)
			{
				//上が押された場合
				if (Input::IsKeyRelease(GAME_INPUT::UP))
				{
					selectState_ = IMAGE::ENDLESS;
					arrowPos_ = { TITLE::ENDLESS_POS.x + TITLE::ARROW_ADD_X_POS ,TITLE::ENDLESS_POS.y };
				}

				//下が押された場合
				if (Input::IsKeyRelease(GAME_INPUT::DOWN))
				{
					selectState_ = IMAGE::HARD;
					arrowPos_ = { TITLE::HARD_POS.x + TITLE::ARROW_ADD_X_POS ,TITLE::HARD_POS.y };
				}

				//決定が押された場合
				if (Input::IsKeyRelease(GAME_INPUT::ENTER))
				{
					returnDifficulty_ = SCENE::NORMAL_PLAY;
					isGotoNextScene_ = true;
					SoundManager::GetInstance()->PlaySoundData(SOUND::SE::DESIDE, DX_PLAYTYPE_BACK);
				}

				return;
			}

			//「ハード」にカーソルが合っている場合
			if (selectState_ == IMAGE::HARD)
			{
				//上が押された場合
				if (Input::IsKeyRelease(GAME_INPUT::UP))
				{
					selectState_ = IMAGE::NORMAL;
					arrowPos_ = { TITLE::NORMAL_POS.x + TITLE::ARROW_ADD_X_POS ,TITLE::NORMAL_POS.y };
				}

				//下が押された場合
				if (Input::IsKeyRelease(GAME_INPUT::DOWN))
				{
					selectState_ = IMAGE::ENDLESS;
					arrowPos_ = { TITLE::ENDLESS_POS.x + TITLE::ARROW_ADD_X_POS ,TITLE::ENDLESS_POS.y };
				}

				//決定が押された場合
				if (Input::IsKeyRelease(GAME_INPUT::ENTER))
				{
					returnDifficulty_ = SCENE::HARD_PLAY;
					isGotoNextScene_ = true;
					SoundManager::GetInstance()->PlaySoundData(SOUND::SE::DESIDE, DX_PLAYTYPE_BACK);
				}

				return;
			}

			//「エンドレス」にカーソルが合っている場合
			if (selectState_ == IMAGE::ENDLESS)
			{
				//上が押された場合
				if (Input::IsKeyRelease(GAME_INPUT::UP))
				{
					selectState_ = IMAGE::HARD;
					arrowPos_ = { TITLE::HARD_POS.x + TITLE::ARROW_ADD_X_POS ,TITLE::HARD_POS.y };
				}

				//下が押された場合
				if (Input::IsKeyRelease(GAME_INPUT::DOWN))
				{
					selectState_ = IMAGE::NORMAL;
					arrowPos_ = { TITLE::NORMAL_POS.x + TITLE::ARROW_ADD_X_POS ,TITLE::NORMAL_POS.y };
				}

				//決定が押された場合
				if (Input::IsKeyRelease(GAME_INPUT::ENTER))
				{
					returnDifficulty_ = SCENE::ENDLESS_PLAY;
					isGotoNextScene_ = true;
					SoundManager::GetInstance()->PlaySoundData(SOUND::SE::DESIDE, DX_PLAYTYPE_BACK);
				}

				return;
			}
		}

		//説明画像表示
		if (state_ == TITLE::STATE::EXPLAIN)
		{
			//戻るが押された場合
			if (Input::IsKeyRelease(GAME_INPUT::BACK))
			{
				//キャンセル音
				SoundManager::GetInstance()->PlaySoundData(SOUND::SE::CANCEL, DX_PLAYTYPE_BACK);

				//1枚目の画像ではなければ戻る
				if (IMAGE::EXPLAIN_1 < explainHandleIndex_)
				{
					--explainHandleIndex_;
				}
				else
				{
					//枚目の画像ならタイトル画面表示に移行する
					state_ = TITLE::STATE::MODE_SELECT;
				}

				//早期リターンする
				return;
			}

			//決定が押された場合
			if (Input::IsKeyRelease(GAME_INPUT::ENTER))
			{
				//次の画像に進める
				++explainHandleIndex_;
				SoundManager::GetInstance()->PlaySoundData(SOUND::SE::DESIDE, DX_PLAYTYPE_BACK);
			}

			if (explainHandleIndex_ > IMAGE::EXPLAIN_4)
			{
				//ここまで来た場合は全ての画像を表示したので戻る
				state_ = TITLE::STATE::MODE_SELECT;
				//初期化
				explainHandleIndex_ = IMAGE::EXPLAIN_1;
			}
		}
	}

	//破棄処理関数
	void SceneTitle::Fin(void)
	{
		//破棄処理
		for (int imageHandle : handles_)
		{
			if (imageHandle != -1)
			{
				DeleteGraph(imageHandle);
			}
		}

		handles_.clear();
		handles_.shrink_to_fit();

		//BGM再生
		SoundManager::GetInstance()->StopSoundData(SOUND::BGM::TITLE);
		SoundManager::GetInstance()->PlaySoundData(SOUND::SE::DESIDE, DX_PLAYTYPE_BACK);
	}

	//次場面判断用関数
	bool SceneTitle::CanGoToNextScene(const SCENE_STATE state) const
	{
		return state == SCENE_STATE::STEP ? isGotoNextScene_ : true;

	}

	//次場面代入用関数
	SCENE SceneTitle::GetNextSceneNum(void) const noexcept
	{
		return returnDifficulty_;
	}
}
