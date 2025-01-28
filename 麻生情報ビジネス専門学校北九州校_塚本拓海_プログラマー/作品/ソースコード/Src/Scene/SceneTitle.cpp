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

	//�R���X�g���N�^
	SceneTitle::SceneTitle(void)
	{
		//������
		theta_ = 0.0f;
		state_ = TITLE::STATE::TITLE;
		selectState_ = IMAGE::STAGE_SELECT;
		returnDifficulty_ = SCENE::NORMAL_PLAY;
		arrowPos_ = { TITLE::STAGE_SELECT_POS.x + TITLE::ARROW_ADD_X_POS ,TITLE::STAGE_SELECT_POS.y };
		explainHandleIndex_ = 0;
		isGotoNextScene_ = false;
	}

	//�f�X�g���N�^
	SceneTitle::~SceneTitle(void)
	{
		//�j������
	}

	//�`�揈���֐�
	void SceneTitle::Draw(void)
	{
		if (handles_.empty())
		{
			return;
		}

		//�^�C�g����ʕ\��
		if (state_ == TITLE::STATE::TITLE)
		{
			DrawGraph(Common::WINDOW_ORIGIN, Common::WINDOW_ORIGIN, handles_[IMAGE::BACK_GROUND], true);
			DrawRotaGraphF(Common::WINDOW_WIDTH_HALF_F, Common::WINDOW_HEIGHT_HALF_F + TITLE::AMPLITUDE * sinf(theta_), 1.0f, 0.0f, handles_[IMAGE::MAIN_TITLE], true);
			DrawRotaGraphF(Common::WINDOW_WIDTH_HALF_F, Common::WINDOW_HEIGHT_HALF_F + TITLE::AMPLITUDE * sinf(theta_), 1.0f, 0.0f, handles_[IMAGE::THE_ENTER], true);
			
			return;
		}

		//�u�X�e�[�W���񂽂��v���u�����т����v��I�������ʕ\��
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

		//�u�m�[�}���v���u�n�[�h�v���u�G���h���X�v��I�������ʕ\��
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

		//�����摜�\��
		if (state_ == TITLE::STATE::EXPLAIN)
		{
			DrawGraph(Common::WINDOW_ORIGIN, Common::WINDOW_ORIGIN, handles_[explainHandleIndex_], true);

			return;
		}
	}

	//�����������֐�
	void SceneTitle::Init(void)
	{
		Load();

		state_ = TITLE::STATE::TITLE;

		explainHandleIndex_ = IMAGE::EXPLAIN_1;

		SoundManager::GetInstance()->PlaySoundData(SOUND::BGM::TITLE, DX_PLAYTYPE_LOOP);

	}

	//�ǂݍ��ݏ����֐�
	void SceneTitle::Load(void)
	{
		//�n���h�����ݒ�̏ꍇ�A�ǂݍ���
		if (handles_.empty())
		{
			CSV_LOADER::LoadHandle(TITLE::PATH, handles_);
		}
	}

	//�s�������֐�
	void SceneTitle::Step(void)
	{
		//�^�C�g����ʕ\��
		if (state_ == TITLE::STATE::TITLE)
		{
			//���肪�����ꂽ�ꍇ
			if (Input::IsKeyRelease(GAME_INPUT::ENTER))
			{
				//�u�X�e�[�W���񂽂��v���u�����т����v��I�������ʂɈړ�
				state_ = TITLE::STATE::MODE_SELECT;

				//�u�X�e�[�W���񂽂��v�ɃJ�[�\�������킹��
				selectState_ = IMAGE::STAGE_SELECT;
				arrowPos_ = { TITLE::STAGE_SELECT_POS.x + TITLE::ARROW_ADD_X_POS ,TITLE::STAGE_SELECT_POS.y };

				SoundManager::GetInstance()->PlaySoundData(SOUND::SE::DESIDE, DX_PLAYTYPE_BACK);
			}

			theta_ = theta_ >= MyMath::TWO_PI ? 0.0f : theta_ + (MyMath::PI * 0.01f);

			return;
		}

		//�u�X�e�[�W���񂽂��v���u�����т����v��I��������
		if (state_ == TITLE::STATE::MODE_SELECT)
		{
			//�߂邪�����ꂽ�ꍇ
			if (Input::IsKeyRelease(GAME_INPUT::BACK))
			{
				//�^�C�g����ʂɖ߂�
				state_ = TITLE::STATE::TITLE;
				selectState_ = IMAGE::NORMAL;
				arrowPos_ = { TITLE::NORMAL_POS.x + TITLE::ARROW_ADD_X_POS ,TITLE::NORMAL_POS.y };
				SoundManager::GetInstance()->PlaySoundData(SOUND::SE::CANCEL, DX_PLAYTYPE_BACK);
			}

			//�u�X�e�[�W���񂽂��v�ɃJ�[�\���������Ă���ꍇ
			if (selectState_ == IMAGE::STAGE_SELECT)
			{
				//�ォ���������ꂽ�ꍇ
				if (Input::IsKeyRelease(GAME_INPUT::UP) || Input::IsKeyRelease(GAME_INPUT::DOWN))
				{
					//�u�����т����v�Ɉړ�
					selectState_ = IMAGE::HOW_TO_PLAY;
					arrowPos_ = { TITLE::HOW_TO_PLAY_POS.x + TITLE::ARROW_ADD_X_POS ,TITLE::HOW_TO_PLAY_POS.y };
				}

				//���肪�����ꂽ�ꍇ
				if (Input::IsKeyRelease(GAME_INPUT::ENTER))
				{
					state_ = TITLE::STATE::STAGE_SELECT;
					selectState_ = IMAGE::NORMAL;
					arrowPos_ = { TITLE::NORMAL_POS.x + TITLE::ARROW_ADD_X_POS ,TITLE::NORMAL_POS.y };

					SoundManager::GetInstance()->PlaySoundData(SOUND::SE::DESIDE, DX_PLAYTYPE_BACK);
				}

				return;
			}

			//�u�����т����v�ɃJ�[�\���������Ă���ꍇ
			if (selectState_ == IMAGE::HOW_TO_PLAY)
			{
				//�ォ���������ꂽ�ꍇ
				if (Input::IsKeyRelease(GAME_INPUT::UP) || Input::IsKeyRelease(GAME_INPUT::DOWN))
				{
					//�u�X�e�[�W���񂽂��v�Ɉړ�
					selectState_ = IMAGE::STAGE_SELECT;
					arrowPos_ = { TITLE::STAGE_SELECT_POS.x + TITLE::ARROW_ADD_X_POS ,TITLE::STAGE_SELECT_POS.y };
				}

				//���肪�����ꂽ�ꍇ
				if (Input::IsKeyRelease(GAME_INPUT::ENTER))
				{
					state_ = TITLE::STATE::EXPLAIN;
					SoundManager::GetInstance()->PlaySoundData(SOUND::SE::DESIDE, DX_PLAYTYPE_BACK);
				}
				return;
			}


			return;
		}

		//�u�m�[�}���v���u�n�[�h�v���u�G���h���X�v��I��������
		if (state_ == TITLE::STATE::STAGE_SELECT)
		{
			//�߂邪�����ꂽ�ꍇ
			if (Input::IsKeyRelease(GAME_INPUT::BACK))
			{
				//�^�C�g����ʂɖ߂�
				state_ = TITLE::STATE::MODE_SELECT;
				selectState_ = IMAGE::STAGE_SELECT;
				arrowPos_ = { TITLE::STAGE_SELECT_POS.x + TITLE::ARROW_ADD_X_POS ,TITLE::STAGE_SELECT_POS.y };
				SoundManager::GetInstance()->PlaySoundData(SOUND::SE::CANCEL, DX_PLAYTYPE_BACK);
			}

			//�u�m�[�}���v�ɃJ�[�\���������Ă���ꍇ
			if (selectState_ == IMAGE::NORMAL)
			{
				//�オ�����ꂽ�ꍇ
				if (Input::IsKeyRelease(GAME_INPUT::UP))
				{
					selectState_ = IMAGE::ENDLESS;
					arrowPos_ = { TITLE::ENDLESS_POS.x + TITLE::ARROW_ADD_X_POS ,TITLE::ENDLESS_POS.y };
				}

				//���������ꂽ�ꍇ
				if (Input::IsKeyRelease(GAME_INPUT::DOWN))
				{
					selectState_ = IMAGE::HARD;
					arrowPos_ = { TITLE::HARD_POS.x + TITLE::ARROW_ADD_X_POS ,TITLE::HARD_POS.y };
				}

				//���肪�����ꂽ�ꍇ
				if (Input::IsKeyRelease(GAME_INPUT::ENTER))
				{
					returnDifficulty_ = SCENE::NORMAL_PLAY;
					isGotoNextScene_ = true;
					SoundManager::GetInstance()->PlaySoundData(SOUND::SE::DESIDE, DX_PLAYTYPE_BACK);
				}

				return;
			}

			//�u�n�[�h�v�ɃJ�[�\���������Ă���ꍇ
			if (selectState_ == IMAGE::HARD)
			{
				//�オ�����ꂽ�ꍇ
				if (Input::IsKeyRelease(GAME_INPUT::UP))
				{
					selectState_ = IMAGE::NORMAL;
					arrowPos_ = { TITLE::NORMAL_POS.x + TITLE::ARROW_ADD_X_POS ,TITLE::NORMAL_POS.y };
				}

				//���������ꂽ�ꍇ
				if (Input::IsKeyRelease(GAME_INPUT::DOWN))
				{
					selectState_ = IMAGE::ENDLESS;
					arrowPos_ = { TITLE::ENDLESS_POS.x + TITLE::ARROW_ADD_X_POS ,TITLE::ENDLESS_POS.y };
				}

				//���肪�����ꂽ�ꍇ
				if (Input::IsKeyRelease(GAME_INPUT::ENTER))
				{
					returnDifficulty_ = SCENE::HARD_PLAY;
					isGotoNextScene_ = true;
					SoundManager::GetInstance()->PlaySoundData(SOUND::SE::DESIDE, DX_PLAYTYPE_BACK);
				}

				return;
			}

			//�u�G���h���X�v�ɃJ�[�\���������Ă���ꍇ
			if (selectState_ == IMAGE::ENDLESS)
			{
				//�オ�����ꂽ�ꍇ
				if (Input::IsKeyRelease(GAME_INPUT::UP))
				{
					selectState_ = IMAGE::HARD;
					arrowPos_ = { TITLE::HARD_POS.x + TITLE::ARROW_ADD_X_POS ,TITLE::HARD_POS.y };
				}

				//���������ꂽ�ꍇ
				if (Input::IsKeyRelease(GAME_INPUT::DOWN))
				{
					selectState_ = IMAGE::NORMAL;
					arrowPos_ = { TITLE::NORMAL_POS.x + TITLE::ARROW_ADD_X_POS ,TITLE::NORMAL_POS.y };
				}

				//���肪�����ꂽ�ꍇ
				if (Input::IsKeyRelease(GAME_INPUT::ENTER))
				{
					returnDifficulty_ = SCENE::ENDLESS_PLAY;
					isGotoNextScene_ = true;
					SoundManager::GetInstance()->PlaySoundData(SOUND::SE::DESIDE, DX_PLAYTYPE_BACK);
				}

				return;
			}
		}

		//�����摜�\��
		if (state_ == TITLE::STATE::EXPLAIN)
		{
			//�߂邪�����ꂽ�ꍇ
			if (Input::IsKeyRelease(GAME_INPUT::BACK))
			{
				//�L�����Z����
				SoundManager::GetInstance()->PlaySoundData(SOUND::SE::CANCEL, DX_PLAYTYPE_BACK);

				//1���ڂ̉摜�ł͂Ȃ���Ζ߂�
				if (IMAGE::EXPLAIN_1 < explainHandleIndex_)
				{
					--explainHandleIndex_;
				}
				else
				{
					//���ڂ̉摜�Ȃ�^�C�g����ʕ\���Ɉڍs����
					state_ = TITLE::STATE::MODE_SELECT;
				}

				//�������^�[������
				return;
			}

			//���肪�����ꂽ�ꍇ
			if (Input::IsKeyRelease(GAME_INPUT::ENTER))
			{
				//���̉摜�ɐi�߂�
				++explainHandleIndex_;
				SoundManager::GetInstance()->PlaySoundData(SOUND::SE::DESIDE, DX_PLAYTYPE_BACK);
			}

			if (explainHandleIndex_ > IMAGE::EXPLAIN_4)
			{
				//�����܂ŗ����ꍇ�͑S�Ẳ摜��\�������̂Ŗ߂�
				state_ = TITLE::STATE::MODE_SELECT;
				//������
				explainHandleIndex_ = IMAGE::EXPLAIN_1;
			}
		}
	}

	//�j�������֐�
	void SceneTitle::Fin(void)
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

		//BGM�Đ�
		SoundManager::GetInstance()->StopSoundData(SOUND::BGM::TITLE);
	}

	//����ʔ��f�p�֐�
	bool SceneTitle::CanGoToNextScene(const SCENE_STATE state) const
	{
		return state == SCENE_STATE::STEP ? isGotoNextScene_ : true;

	}

	//����ʑ���p�֐�
	SCENE SceneTitle::GetNextSceneNum(void) const noexcept
	{
		return returnDifficulty_;
	}
}
