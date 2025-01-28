#pragma once

#include <memory>
#include "SceneBase.h"
#include "Scene.h"
#include "Fade/Fade.h"

namespace BOUDAMA
{
	//��ʊǗ��p�N���X
	class SceneManager final
	{
	public:
		//�R���X�g���N�^
		SceneManager(void);

		//�f�X�g���N�^
		~SceneManager(void);

		//�{�ҏ����֐�
		void Loop(void);

		//�����������֐�
		void Init(void);

		//�`�揈���֐�
		void Draw(void);

		//�j�������֐�
		void Fin(void);

	private:
		//��ʍ쐬�֐�
		void SceneCreate(void);

		//��ʐ؂�ւ��֐�
		void SceneChange(void);

		//��ʔ��f�p�ϐ�
		SCENE_STATE currentSceneState_;

		//��ʎ��s�p
		std::unique_ptr<SceneBase> sceneObjectPointer_;

		//�t�F�[�h�p
		Fade fade_;

	};
}
