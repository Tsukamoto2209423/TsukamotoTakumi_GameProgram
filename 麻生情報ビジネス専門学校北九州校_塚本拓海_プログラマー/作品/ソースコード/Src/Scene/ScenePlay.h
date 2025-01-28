#pragma once

#include <memory>
#include "SceneBase.h"
#include "Player/Player.h"
#include "Enemy/EnemyManager.h"
#include "Collision/CollisionManager.h"
#include "Sound/Sound.h"
#include "Camera/Camera.h"
#include "Field/Field.h"
#include "SkyBox/SkyBox.h"
#include "Substance/SubstanceManager.h"
#include "Score/Score.h"
#include "TimeLimit/TimeLimit.h"

namespace BOUDAMA
{
	//�Q�[���v���C�N���X
	class ScenePlay final : public SceneBase
	{
	public:
		//�R���X�g���N�^
		ScenePlay(void);
		explicit ScenePlay(const SCENE difficulty) noexcept : playDifficulty_(difficulty), shadowHandle_(-1) {}

		//�f�X�g���N�^
		~ScenePlay(void);

		//�`�揈��
		void Draw(void) override;

	private:
		//�e��`�悷��Ƃ��ɂ����n���h��
		int shadowHandle_;

		//��Փx�I��p�ϐ�
		SCENE playDifficulty_;

		//���삷��v���C���[
		std::shared_ptr<Player> player_;

		//�v���C���[���ړ�����t�B�[���h
		Field field_;

		//�V��
		SkyBox sky_;

		//�������Ԍv���p�ϐ�
		TimeLimit timeLimit_;

		//�G�Ǘ��p�ϐ�
		EnemyManager enemyManager_;

		//�A�C�e���Ǘ��p�ϐ�
		ItemManager itemManager_;

		//�����N���X�Ǘ��p�ϐ�
		SubstanceManager substanceManager_;

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
