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

namespace BOUDAMA
{
	//�R���X�g���N�^
	SceneClear::SceneClear(void)
	{
		//������
		clearState_ = SCENE::CLEAR;
	}

	//�f�X�g���N�^
	SceneClear::~SceneClear(void)
	{
		//�j������
	}

	//�`�揈���֐�
	void SceneClear::Draw(void)
	{
		if (handles_.empty())
		{
			return;
		}

		DrawGraph(Common::WINDOW_ORIGIN, Common::WINDOW_ORIGIN, handles_[CLEAR::IMAGE::BACK_GROUND], true);
		DrawGraph(Common::WINDOW_ORIGIN, Common::WINDOW_ORIGIN, handles_[CLEAR::IMAGE::SYOBON_IMAGE], true);

		//�N���A��ʂȂ�u�Q�[���N���A�v�̕���
		if (clearState_ == SCENE::CLEAR)
		{
			DrawRotaGraphF(CLEAR::CHARA_POS.x, CLEAR::CHARA_POS.y, 1.0f, 0.0f, handles_[CLEAR::IMAGE::GAME_CLEAR_CHARA], true);

			Score::DrawScore(SCORE::CLEAR_GAMEOVER::INIT_POS_X, SCORE::CLEAR_GAMEOVER::INIT_POS_Y);
			Score::DrawBestScore();
		}

		//���ʉ�ʂȂ�u���イ��傤�I�v�̕���
		if (clearState_ == SCENE::RESULT)
		{
			DrawRotaGraphF(CLEAR::END_CHARA_POS.x, CLEAR::END_CHARA_POS.y, 0.5f, 0.0f, handles_[CLEAR::IMAGE::END_CHARA], true);

			Score::DrawScore(SCORE::CLEAR_GAMEOVER::INIT_POS_X, SCORE::CLEAR_GAMEOVER::INIT_POS_Y);
			Score::DrawEndlessBestScore();
		}
	}

	//�����������֐�
	void SceneClear::Init(void)
	{
		SoundManager::GetInstance()->PlaySoundData(SOUND::SE::GAME_FINISH, DX_PLAYTYPE_BACK);

		Load();
	}

	//�ǂݍ��ݏ����֐�
	void SceneClear::Load(void)
	{
		if (handles_.empty())
		{
			CSV_LOADER::LoadHandle(CLEAR::PATH, handles_);
		}
	}

	//�s�������֐�
	void SceneClear::Step(void)
	{
		//��������
	}

	//�j�������֐�
	void SceneClear::Fin(void)
	{
		//�j������
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

		//���ʉ�
		SoundManager::GetInstance()->PlaySoundData(SOUND::SE::DESIDE, DX_PLAYTYPE_BACK);

	}

	//����ʔ��f�p�֐�
	bool SceneClear::CanGoToNextScene(const SCENE_STATE state) const
	{
		return state == SCENE_STATE::STEP ? Input::IsKeyRelease(GAME_INPUT::ENTER) : true;
	}

	//����ʑ���p�֐�
	SCENE SceneClear::GetNextSceneNum(void) const noexcept
	{
		return SCENE::TITLE;
	}
}
