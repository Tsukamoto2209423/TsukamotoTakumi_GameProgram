#pragma once

#include <vector>
#include <memory>
#include "Scene/SceneBase.h"
#include "Common/Common.h"

namespace BOUDAMA
{
	namespace CLEAR
	{
		//�N���A��ʂŎg���摜�̃p�X��Z�߂�CSV�t�@�C���̃p�X
		constexpr char PATH[] = "Data/Image/Clear/GameClearImageList.csv";

		//�N���A��ʂɕ\������u�Q�[���N���A�v�̕����̈ʒu
		constexpr Vector2D CHARA_POS = { Common::WINDOW_WIDTH_HALF_F,260.0f };

		//�N���A��ʂɕ\������u���イ��傤�v�̕����̈ʒu
		constexpr Vector2D END_CHARA_POS = { Common::WINDOW_WIDTH_HALF_F,80.0f };

		//�N���A��ʂ̉摜�ꗗ
		enum IMAGE
		{
			//�w�i�摜
			BACK_GROUND,

			//�u�Q�[���N���A�v�̉摜
			GAME_CLEAR_CHARA,

			//���ł���L�����N�^�[�̉摜
			SYOBON_IMAGE,

			//�u���イ��傤�I�v�̕����摜
			END_CHARA,

			//�摜�̍ő吔
			ALL_NUM
		};
	}

	//�N���A�N���X
	class SceneClear final : public SceneBase
	{
	public:
		//�R���X�g���N�^
		SceneClear(void);

		//�R���X�g���N�^
		explicit SceneClear(const SCENE state) noexcept : clearState_(state) {}

		//�f�X�g���N�^
		~SceneClear(void);

		//�`�揈��
		void Draw(void) override;

	private:
		//�摜�n���h��
		std::vector<int> handles_;

		//�N���A�����Ƃ��̏��
		SCENE clearState_;

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
