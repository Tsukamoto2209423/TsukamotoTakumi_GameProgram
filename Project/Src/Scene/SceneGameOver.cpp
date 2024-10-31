#include "SceneGameOver.h"
#include <DxLib.h>
#include "Common/Common.h"
#include <Sound/Sound.h>
#include <Score/Score.h>
#include <NumberGraph/Number.h>
#include <Input/Input.h>
#include <Input/InputParameter.h>
#include "FileLoader/CSVFileLoader.h"

namespace BOUDAMA
{
	//コンストラクタ
	SceneGameOver::SceneGameOver(void)
	{
		//初期化
	}

	//デストラクタ
	SceneGameOver::~SceneGameOver(void)
	{

	}

	//描画処理関数
	void SceneGameOver::Draw(void)
	{
		if (handles_.empty())
		{
			return;
		}

		DrawGraph(Common::WINDOW_ORIGIN, Common::WINDOW_ORIGIN, handles_[GAME_OVER::BACK_GROUND], true);
		DrawGraph(Common::WINDOW_ORIGIN, Common::WINDOW_ORIGIN, handles_[GAME_OVER::SYOBON_IMAGE], true);
		DrawGraphF(GAME_OVER::CHARA_POS.x, GAME_OVER::CHARA_POS.y, handles_[GAME_OVER::GAME_OVER_CHARA], true);

		Score::DrawScore(SCORE::CLEAR_GAMEOVER::INIT_POS_X, SCORE::CLEAR_GAMEOVER::INIT_POS_Y);
	}

	//初期化処理関数
	void SceneGameOver::Init(void)
	{
		Load();

	}

	//読み込み処理関数
	void SceneGameOver::Load(void)
	{
		//ハンドル未設定の場合、読み込む
		if (handles_.empty())
		{
			CSV_LOADER::LoadHandle(GAME_OVER::PATH, handles_);
		}
	}

	//行動処理関数
	void SceneGameOver::Step(void)
	{

	}

	//破棄処理関数
	void SceneGameOver::Fin(void)
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

		SoundManager::GetInstance()->PlaySoundData(SOUND::SE::DESIDE, DX_PLAYTYPE_BACK);

		Score::Fin();

		NumberGraph::Fin();
	}

	//次場面判断用関数
	bool SceneGameOver::CanGoToNextScene(const SCENE_STATE state) const
	{
		return state == SCENE_STATE::STEP ? Input::IsKeyRelease(GAME_INPUT::ENTER) : true;
	}

	//次場面代入用関数
	SCENE SceneGameOver::GetNextSceneNum(void) const noexcept
	{
		return SCENE::TITLE;
	}
}
