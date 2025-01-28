#pragma once

#include "DxLib.h"
#include "Scene/SceneManager.h"

namespace BOUDAMA
{
	//�Q�[�����������N���X
	class GameSystem
	{
	private:
		//�Q�[���I������
		static inline bool isGameEnd_;

		//��ʊǗ�
		static inline SceneManager sceneManager_;

		//�R���X�g���N�^
		GameSystem() = delete;

		//�f�X�g���N�^
		~GameSystem() = delete;

	public:
		//�Q�[���N���֐�
		static void Start();

		//�{�ғ��������֐�
		static void MainLoop();

		//�j���֐�
		static void Fin();

	private:
		//�������֐�
		static void Init();

		//�{�ҏ����֐�
		static void Step();

	public:
		//�Q�[���I������擾
		static inline bool GetGameEnd() { return isGameEnd_; }

		//�Q�[���I��
		static inline void SetGameEnd() { isGameEnd_ = true; }
	};
}