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
	//�R���X�g���N�^
	SceneGameOver::SceneGameOver(void)
	{
		//������
	}

	//�f�X�g���N�^
	SceneGameOver::~SceneGameOver(void)
	{

	}

	//�`�揈���֐�
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

	//�����������֐�
	void SceneGameOver::Init(void)
	{
		Load();

	}

	//�ǂݍ��ݏ����֐�
	void SceneGameOver::Load(void)
	{
		//�n���h�����ݒ�̏ꍇ�A�ǂݍ���
		if (handles_.empty())
		{
			CSV_LOADER::LoadHandle(GAME_OVER::PATH, handles_);
		}
	}

	//�s�������֐�
	void SceneGameOver::Step(void)
	{

	}

	//�j�������֐�
	void SceneGameOver::Fin(void)
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

		SoundManager::GetInstance()->PlaySoundData(SOUND::SE::DESIDE, DX_PLAYTYPE_BACK);

		Score::Fin();

		NumberGraph::Fin();
	}

	//����ʔ��f�p�֐�
	bool SceneGameOver::CanGoToNextScene(const SCENE_STATE state) const
	{
		return state == SCENE_STATE::STEP ? Input::IsKeyRelease(GAME_INPUT::ENTER) : true;
	}

	//����ʑ���p�֐�
	SCENE SceneGameOver::GetNextSceneNum(void) const noexcept
	{
		return SCENE::TITLE;
	}
}
