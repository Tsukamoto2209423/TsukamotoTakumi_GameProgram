#include <memory>
#include <functional>
#include <unordered_map>
#include <string>

#include "SceneManager.h"
#include "SceneTitle.h"
#include "ScenePlay.h"
#include "SceneClear.h"
#include "SceneGameOver.h"

namespace BOUDAMA
{
	//�R���X�g���N�^
	SceneManager::SceneManager(void)
	{
		currentSceneState_ = SCENE_STATE::INIT;
	}

	//�f�X�g���N�^
	SceneManager::~SceneManager(void)
	{

	}

	//��ʎ又���֐�
	void SceneManager::Loop(void)
	{
		//�t�F�[�h���I����Ă��Ȃ��ꍇ�̓t�F�[�h����������
		if (!fade_.IsEnd())
		{
			fade_.Step();

			return;
		}

		//��ʂɉ������֐��|�C���^���s
		sceneObjectPointer_->Loop(currentSceneState_);

		//����ʔ���֐����^�̏ꍇ�A��ʂɉ����Đ؂�ւ�
		if (sceneObjectPointer_->CanGoToNextScene(currentSceneState_))
		{
			//��ʏ󋵐؂�ւ�����
			SceneChange();

			if (currentSceneState_ == SCENE_STATE::INIT)
			{
				SceneCreate();
			}

			//STEP�ɕύX���ꂽ�ꍇ�͎��s���Ȃ�
			if (currentSceneState_ != SCENE_STATE::STEP)
			{
				fade_.Change();
			}
		}
	}

	//�����������֐�
	void SceneManager::Init(void)
	{
		sceneObjectPointer_ = std::make_unique<SceneTitle>();
		currentSceneState_ = SCENE_STATE::INIT;

		fade_.Init();
		fade_.Load();

	}

	//�`�揈���֐�
	void SceneManager::Draw(void)
	{
		//��ʂɉ������`�揈��
		sceneObjectPointer_->Draw();

		if (currentSceneState_ != SCENE_STATE::STEP)
		{
			fade_.Draw();
		}
	}

	//�j�������֐�
	void SceneManager::Fin(void)
	{
		sceneObjectPointer_->Fin();
		fade_.Fin();
	}

	//��ʍ쐬�֐�
	void SceneManager::SceneCreate(void)
	{
		//�V�[���ꗗ
		static const std::vector<std::function<std::unique_ptr<SceneBase>()>> sceneVector =
		{
			//�^�C�g��
			[]() {return std::make_unique<SceneTitle>(); } ,

			//���ʓ�Փx�ŃQ�[���v���C
			[]() {return std::make_unique<ScenePlay>(SCENE::NORMAL_PLAY); } ,

			//�����Փx�ŃQ�[���v���C
			[]() {return std::make_unique<ScenePlay>(SCENE::HARD_PLAY);	 },

			//�G���h���X�ŃQ�[���v���C
			[]() {return std::make_unique<ScenePlay>(SCENE::ENDLESS_PLAY);	} ,

			//�N���A
			[]() {return std::make_unique<SceneClear>(); } ,

			//�G���h���X���[�h�ł̌��ʕ\�����
			[]() {return std::make_unique<SceneClear>(SCENE::RESULT); } ,

			//�Q�[���I�[�o�[
			[]() {return std::make_unique<SceneGameOver>(); }
		};

		//���̃V�[���𐶐�����
		sceneObjectPointer_ = sceneVector[static_cast<int>(sceneObjectPointer_->GetNextSceneNum())]();

	}

	//��ʐ؂�ւ��֐�
	void SceneManager::SceneChange(void)
	{
		//INIT��STEP��FIN��INIT���c�̏��Ői�߂�
		currentSceneState_ == SCENE_STATE::FIN ? currentSceneState_ = SCENE_STATE::INIT : ++currentSceneState_;
	}
}
