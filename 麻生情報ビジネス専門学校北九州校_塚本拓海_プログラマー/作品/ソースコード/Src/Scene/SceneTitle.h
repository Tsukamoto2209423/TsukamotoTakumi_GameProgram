#pragma once

#include <vector>
#include <memory>
#include "Scene/SceneBase.h"
#include <Common.h>

namespace BOUDAMA
{
	//�^�C�g����ʃN���X�Ŏg����`
	namespace TITLE
	{
		//�摜�ꗗ�\�̃p�X
		constexpr char PATH[] = "Data/Image/Title/TitleImageList.csv";

		//�㉺�ɗh���摜��1�t���[���ɐi�ދ��� = AMPLITUDE �~ sin��
		constexpr float AMPLITUDE = 21.5f;

		//�I�����Ă���摜�̒��S�_����Z�s�N�Z���E�Ɂu���v�̉摜��\��������
		constexpr float ARROW_ADD_X_POS = 350.0f;

		//�u�Q�[���X�^�[�g�I�v�̉摜�̈ʒu
		constexpr Vector2D GAME_START_POS = { Common::WINDOW_WIDTH_HALF_F,Common::WINDOW_HEIGHT_HALF_F };

		//�u�X�e�[�W���񂽂��v�̉摜�̈ʒu
		constexpr Vector2D STAGE_SELECT_POS = { Common::WINDOW_WIDTH_HALF_F,250.0f };

		//�u�����т����v�̉摜�̈ʒu
		constexpr Vector2D HOW_TO_PLAY_POS = { Common::WINDOW_WIDTH_HALF_F, 500.0f };

		//�u�m�[�}���v�̉摜
		constexpr Vector2D NORMAL_POS = { Common::WINDOW_WIDTH_HALF_F,120.0f };

		//�u�n�[�h�v�̉摜
		constexpr Vector2D HARD_POS = { Common::WINDOW_WIDTH_HALF_F,360.0f };

		//�u�G���h���X�v�̉摜
		constexpr Vector2D ENDLESS_POS = { Common::WINDOW_WIDTH_HALF_F,600.0f };

		//�u�G���^�[�ł����ށv�̉摜
		constexpr Vector2D PROCEED_POS = { Common::WINDOW_WIDTH_F - 120.0f, 620.0f };

		//�uBACKSPACE�ł��ǂ�v�̉摜
		constexpr Vector2D BACK_POS = { Common::WINDOW_ORIGIN + 120.0f, 620.0f };

		//�^�C�g���Ŏg���摜�ꗗ
		enum IMAGE
		{
			//�u�{�E�_�}�I�v�̉摜
			MAIN_TITLE,

			//�u�G���^�[�L�[�������ƃX�^�[�g�I�v�̉摜
			THE_ENTER,

			//�w�i�摜
			BACK_GROUND,

			//�u�Q�[���X�^�[�g�I�v�̉摜
			GAME_START,

			//�u�X�e�[�W���񂽂��v�̉摜
			STAGE_SELECT,

			//�u�����т����v�̉摜
			HOW_TO_PLAY,

			//�u�m�[�}���v�̉摜
			NORMAL,

			//�u�n�[�h�v�̉摜
			HARD,

			//�u�G���h���X�v�̉摜
			ENDLESS,

			//�u�G���^�[�ł����ށv�̉摜
			PROCEED,

			//�uBACKSPACE�ł��ǂ�v�̉摜
			BACK,

			//�u���v�̉摜
			ARROW,

			//�����摜
			EXPLAIN_1,
			EXPLAIN_2,
			EXPLAIN_3,
			EXPLAIN_4,

			//�����摜�̍ő吔
			ALL_NUM
		};

		//�^�C�g����ʂ̏��
		enum class STATE
		{
			TITLE,
			MODE_SELECT,
			STAGE_SELECT,
			EXPLAIN,

			NUM
		};

	}

	//�^�C�g���N���X
	class SceneTitle final : public SceneBase
	{
	public:
		//�R���X�g���N�^
		SceneTitle(void);
		//�f�X�g���N�^
		~SceneTitle(void);

		//�`�揈��
		void Draw(void) override;

	private:
		//�摜�n���h����ۑ�����z��
		std::vector<int> handles_;

		//�^�C�g����ʂ̏��
		TITLE::STATE state_;

		//�^�C�g����ʂŌ��ݑI�����Ă���I�����̏��
		TITLE::IMAGE selectState_;

		//�Q�[���̓�Փx��Ԃ��Ƃ��ɂ����ϐ�
		SCENE returnDifficulty_;

		//�I�������w���Ƃ��Ɏg���u���v�̉摜�̈ʒu
		Vector2D arrowPos_;

		//�����摜�̓Y������ۑ�����ϐ�
		int explainHandleIndex_;

		//�摜���㉺�ɗh�炷�Ƃ��Ɏg���ϐ�
		float theta_;

		//���̏�ʂɍs���Ă�����
		bool isGotoNextScene_;

		//�����������֐�
		void Init(void) override;

		//�ǂݍ��ݏ����֐�
		void Load(void) override;

		//�s�������֐�
		void Step(void) override;

		//�j�������֐�
		void Fin(void) override;

		/// <summary>
		/// ���̃V�[���ɐi�ނ����肷��֐�
		/// </summary>
		/// <param name="state">���݂̃V�[���̏��</param>
		/// <returns>true:���̃V�[���Ɉڍs false:���݂̃V�[���̂܂�</returns>
		bool CanGoToNextScene(const SCENE_STATE state) const override;

		/// <summary>
		/// ���̃V�[������p�֐�
		/// </summary>
		/// <returns>���̃V�[��</returns>
		inline SCENE GetNextSceneNum(void) const noexcept override;
	};
}