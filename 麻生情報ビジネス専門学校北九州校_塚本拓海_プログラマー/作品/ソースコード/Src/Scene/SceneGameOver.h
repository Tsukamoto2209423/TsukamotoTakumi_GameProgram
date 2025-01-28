#pragma once

#include <vector>
#include <memory>
#include "Scene/SceneBase.h"

namespace BOUDAMA
{
	//�Q�[���I�[�o�[��ʃN���X�Ŏg����`
	namespace GAME_OVER
	{
		//�摜�ꗗ�\�̃p�X
		constexpr char PATH[] = "Data/Image/GameOver/GameOverImageList.csv";

		constexpr Vector2D CHARA_POS = { 220.0f,0.0f };

		enum IMAGE
		{
			//�w�i�摜
			BACK_GROUND,

			//�u�Q�[���I�[�o�[�v�̉摜
			GAME_OVER_CHARA,

			//��������ł���L�����N�^�[�̉摜
			SYOBON_IMAGE,

			//�摜�̍ő吔
			ALL_NUM
		};

	}

	//�Q�[���I�[�o�[�N���X
	class SceneGameOver final : public SceneBase
	{
	public:
		//�R���X�g���N�^
		SceneGameOver(void);
		//�f�X�g���N�^
		~SceneGameOver(void);

		//�`�揈��
		void Draw(void) override;

	private:
		std::vector<int> handles_;

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
