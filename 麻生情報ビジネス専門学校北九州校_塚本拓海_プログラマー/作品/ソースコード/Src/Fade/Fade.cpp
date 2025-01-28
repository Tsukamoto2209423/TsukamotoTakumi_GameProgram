#include "Fade.h"
#include <fstream>
#include <DxLib.h>
#include "Common.h"
#include <Math/MyMath.h>
#include "FileLoader/CSVFileLoader.h"
#include "Input/Input.h"
#include <Input/InputParameter.h>
#include "Sound/Sound.h"

namespace BOUDAMA
{
	Fade::Fade()
	{
		//��ԏ�����
		state_ = FADE::NONE;

		//���l
		alphaValue_ = 0;

		posX_ = 0;

		handleIndex_ = 0;

		concentrationLineIndex_ = 0;

		rotAngle_ = 0.0f;

		isEnd_ = false;
	};

	Fade::~Fade()
	{

	};

	//�����������֐�
	void Fade::Init(void)
	{

		state_ = FADE::NONE;

		//���l
		alphaValue_ = 255;

		posX_ = Common::WINDOW_WIDTH_HALF;

		handleIndex_ = 0;

		rotAngle_ = 0.0f;

		isEnd_ = true;
	}

	//�ǂݍ��ݏ����֐�
	void Fade::Load(void)
	{
		CSV_LOADER::LoadHandle(FADE::PATH, syobonHandles_);
		CSV_LOADER::LoadHandle(FADE::EFFECT_PATH, lineHandles_);
	}

	//�X�V�����֐�
	void Fade::Step(void)
	{
		//��Ԗ����̏ꍇ�͉������Ȃ�
		if (state_ == FADE::NONE)
		{
			return;
		}

		//�t�F�[�h�C���̏ꍇ
		if (state_ == FADE::F_IN)
		{
			if (alphaValue_ <= 255)
			{
				alphaValue_ += FADE::ALPHA_SPEED;

				posX_ -= FADE::MOVE_SPEED;
				rotAngle_ -= MyMath::PI_OVER_TWENTY;

				return;
			}

			isEnd_ = (GetASyncLoadNum() == 0);

			return;
		}

		//�t�F�[�h�A�E�g�̏ꍇ
		if (state_ == FADE::F_OUT)
		{
			if (alphaValue_ >= 0)
			{
				alphaValue_ -= FADE::ALPHA_SPEED;

				posX_ -= FADE::MOVE_SPEED;
				rotAngle_ -= MyMath::PI_OVER_TWENTY;

				return;
			}

			if (GetASyncLoadNum() == 0)
			{
				//�I���t���O�𗧂Ă�
				isEnd_ = true;

				state_ = FADE::NONE;

				//�����ǂݍ��ݐݒ�ɕύX
				SetUseASyncLoadFlag(false);
			}

			return;
		}
	}

	//�`�揈���֐�
	void Fade::Draw(void)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alphaValue_);
		DrawBox(0, 0, Common::WINDOW_WIDTH, Common::WINDOW_HEIGHT, GetColor(255, 255, 255), true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawRotaGraph(posX_, Common::WINDOW_HEIGHT_HALF, 1.0f, rotAngle_, syobonHandles_[handleIndex_], true);

		//�l�^�摜���\������Ă���Ƃ��̂ݏW�����`��
		if (handleIndex_ == syobonHandles_.size() - 1)
		{
			DrawConcentrationLine();
		}
	}

	//�j�������֐�
	void Fade::Fin(void)
	{
		for (int handle : syobonHandles_)
		{
			if (handle != -1)
			{
				DeleteGraph(handle);
				handle = -1;
			}
		}

		syobonHandles_.clear();
		syobonHandles_.shrink_to_fit();
	}

	//�t�F�[�h�̏�ԕύX
	void Fade::Change(void)
	{
		//��Ԗ����̏ꍇ�̓t�F�[�h�A�E�g�ɂ���
		if (state_ == FADE::NONE)
		{
			alphaValue_ = 0;
			state_ = FADE::F_IN;

			posX_ = Common::WINDOW_WIDTH + FADE::IMAGE_SIZE;

			if (Input::IsKeyDown(GAME_INPUT::DEBUG))
			{
				//�l�^�摜��K���\��������
				handleIndex_ = static_cast<int>(syobonHandles_.size() - 1);
			}
			else
			{
				handleIndex_ = GetRand(static_cast<int>(syobonHandles_.size() - 1));
			}

			//��ʑJ�ڎ��̌��ʉ�
			SoundManager::GetInstance()->PlaySoundData(SOUND::SE::SCENE_CHANGE, DX_PLAYTYPE_BACK);

			//�t�F�[�h�I���t���O������
			isEnd_ = false;

			//�񓯊��ǂݍ��ݐݒ�ɕύX
			SetUseASyncLoadFlag(true);

			return;
		}

		//�t�F�[�h�C���̏ꍇ
		if (state_ == FADE::F_IN)
		{
			alphaValue_ = 255;
			state_ = FADE::F_OUT;

			//��ʑJ�ڎ��̌��ʉ�
			SoundManager::GetInstance()->PlaySoundData(SOUND::SE::SCENE_CHANGE, DX_PLAYTYPE_BACK);

			//�t�F�[�h�I���t���O������
			isEnd_ = false;

			return;
		}

		//�t�F�[�h�A�E�g�̏ꍇ
		if (state_ == FADE::F_OUT)
		{
			alphaValue_ = 0;
			state_ = FADE::NONE;

			//�����ǂݍ��ݐݒ�ɕύX
			SetUseASyncLoadFlag(false);

			isEnd_ = true;

			return;
		}
	}

	//�t�F�[�h�C�����t�F�[�h�A�E�g���I�����������
	bool Fade::IsEnd(void) const noexcept
	{
		return isEnd_;
	}

	//�W�����`��
	void Fade::DrawConcentrationLine(void)
	{
		//�W�����`��
		DrawGraph(0, 0, lineHandles_[concentrationLineIndex_], true);

		//�W�����̌J��Ԃ�����
		concentrationLineIndex_ >= FADE::CONCENTRATION_LINE_END ?
			concentrationLineIndex_ = FADE::CONCENTRATION_LINE_1 : ++concentrationLineIndex_;
	}
}
