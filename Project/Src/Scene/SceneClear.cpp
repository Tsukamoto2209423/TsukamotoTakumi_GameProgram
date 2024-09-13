#include "SceneClear.h"
#include <DxLib.h>
#include "Common.h"
#include "Scene.h"
#include <Sound/Sound.h>
#include <Score/Score.h>
#include <NumberGraph/Number.h>
#include <Input/Input.h>
#include <Input/InputParameter.h>
#include "FileLoader/CSVFileLoader.h"

//コンストラクタ
SceneClear::SceneClear(void)
{
	//初期化
	clearState_ = SCENE::CLEAR;
}

//デストラクタ
SceneClear::~SceneClear(void)
{
	//破棄処理
}

//描画処理関数
void SceneClear::Draw(void)
{
	if (handles_.empty())
	{
		return;
	}

	DrawGraph(Common::WINDOW_ORIGIN, Common::WINDOW_ORIGIN, handles_[CLEAR::IMAGE::BACK_GROUND], true);
	DrawGraph(Common::WINDOW_ORIGIN, Common::WINDOW_ORIGIN, handles_[CLEAR::IMAGE::SYOBON_IMAGE], true);

	//クリア画面なら「ゲームクリア」の文字
	if (clearState_ == SCENE::CLEAR)
	{
		DrawRotaGraphF(CLEAR::CHARA_POS.x, CLEAR::CHARA_POS.y, 1.0f, 0.0f, handles_[CLEAR::IMAGE::GAME_CLEAR_CHARA], true);

		Score::DrawScore(SCORE::CLEAR_GAMEOVER::INIT_POS_X, SCORE::CLEAR_GAMEOVER::INIT_POS_Y);
		Score::DrawBestScore();
	}

	//結果画面なら「しゅうりょう！」の文字
	if (clearState_ == SCENE::RESULT)
	{
		DrawRotaGraphF(CLEAR::END_CHARA_POS.x, CLEAR::END_CHARA_POS.y, 0.5f, 0.0f, handles_[CLEAR::IMAGE::END_CHARA], true);

		Score::DrawScore(SCORE::CLEAR_GAMEOVER::INIT_POS_X, SCORE::CLEAR_GAMEOVER::INIT_POS_Y);
		Score::DrawEndlessBestScore();
	}


}

//初期化処理関数
void SceneClear::Init(void)
{
	SoundManager::GetInstance()->PlaySoundData(SOUND::SE::GAME_FINISH, DX_PLAYTYPE_BACK);

	Load();
}

//読み込み処理関数
void SceneClear::Load(void)
{
	if (handles_.empty())
	{
		CSV_LOADER::LoadHandle(CLEAR::PATH, handles_);
	}
}

//行動処理関数
void SceneClear::Step(void)
{
	//処理無し
}

//破棄処理関数
void SceneClear::Fin(void)
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

	Score::Fin();

	NumberGraph::Fin();

	//効果音
	SoundManager::GetInstance()->PlaySoundData(SOUND::SE::DESIDE, DX_PLAYTYPE_BACK);

}

//次場面判断用関数
bool SceneClear::CanGoToNextScene(const SCENE_STATE state) const
{
	return state == SCENE_STATE::STEP ? Input::IsKeyRelease(GAME_INPUT::ENTER) : true;
}

//次場面代入用関数
SCENE SceneClear::GetNextSceneNum(void) const
{
	return SCENE::TITLE;
}
