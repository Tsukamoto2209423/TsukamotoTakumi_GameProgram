#include "GameSystem.h"
#include "DxLib.h"
#include "Common.h"
#include "FrameRate/FrameRate.h"
#include "Camera/CameraManager.h"
#include <Effekseer/Effekseer.h>
#include "Effekseer/EffekseerParameter.h"
#include <Math/MyMath.h>
#include <Sound/Sound.h>
#include <Input/Input.h>
#include "Input/InputParameter.h"

namespace BOUDAMA
{
	//�������֐�
	void GameSystem::Init()
	{
		//�X�N���[�����[�h�ŋN��
		ChangeWindowMode(true);

		//�E�B���h�E�̑傫���ݒ�
		SetGraphMode(Common::WINDOW_WIDTH, Common::WINDOW_HEIGHT, 32);

		//�ő剻�t���̃X�N���[�����[�h
		SetWindowStyleMode(7);

		//�傫���ύX�\�ɐݒ�
		SetWindowSizeChangeEnableFlag(true);

		//�E�B���h�E���ݒ�
		SetWindowText("�{�E�_�}�I");
	}

	//�Q�[���N���֐�
	void GameSystem::Start()
	{
		//DxLib���N������O�ɍs������
		Init();

		//DX���C�u����������
		if (DxLib_Init() == -1)
		{
			//�ُ�l���Ԃ��Ă�����Q�[�����I��
			SetGameEnd();
			return;
		}

		//�`�悷��X�N���[����ݒ�
		SetDrawScreen(DX_SCREEN_BACK);

		SetUseZBuffer3D(TRUE);
		SetWriteZBuffer3D(TRUE);

		//���͏�����
		Input::Init();

		//�V�[��������
		sceneManager_.Init();

		//�G�t�F�N�g������
		CEffekseerCtrl::Init(EFFECT::ALL_NUM, 5000);
		CEffekseerCtrl::SetEffectLoadID(CEffekseerCtrl::LoadData("Data/Effect/HitEffect.efk"));
		CEffekseerCtrl::SetEffectLoadID(CEffekseerCtrl::LoadData("Data/Effect/EnemySpawn.efk"));
		CEffekseerCtrl::SetEffectLoadID(CEffekseerCtrl::LoadData("Data/Effect/RedDissolve.efk"));
		CEffekseerCtrl::SetEffectLoadID(CEffekseerCtrl::LoadData("Data/Effect/Heal.efk"));
		CEffekseerCtrl::SetEffectLoadID(CEffekseerCtrl::LoadData("Data/Effect/Accelerator.efk"));
		CEffekseerCtrl::SetEffectLoadID(CEffekseerCtrl::LoadData("Data/Effect/Explosion.efk"));
		CEffekseerCtrl::SetEffectLoadID(CEffekseerCtrl::LoadData("Data/Effect/GleamEffect.efk"));

		
		CEffekseerCtrl::SetProjectionMtx(MyMath::PI_OVER_THREE, 16.0f / 9.0f, 1.0f, 27000.0f);

		//����񏉊���
		SoundManager::GetInstance()->Init();
		SoundManager::GetInstance()->Load();

	}

	//�Q�[���{�ғ��������֐�
	void GameSystem::MainLoop()
	{
		//�Q�[���{�ҏ���
		while (ProcessMessage() != -1)
		{
			//ESC�L�[���Q�[���I���t���O�������Ă���ΏI��
			if (Input::IsKeyDown(GAME_INPUT::ESCAPE) || GetGameEnd())
			{
				break;
			}

			//�{�ҏ���
			Step();
		}
	}

	//�Q�[���{�ҏ����֐�
	void GameSystem::Step()
	{
		//�V�X�e���ɏ�����Ԃ�
		Sleep(1);

		//=====================

		//�t���[�����[�g�ʏ폈��
		FrameRate::Step();

		//���s�\�Ȃ烁�C���̏����ɒʂ�
		if (FrameRate::IsPassedFrameRateTime())
		{
			//��ʂɕ\�����ꂽ���̂��������i�P���[�v�̂P�x�����s���j
			ClearDrawScreen();

			//���͏���
			Input::Step();

			//�t���[�����[�g�X�V����
			FrameRate::Update();

			//================================

			//�Q�[������
			sceneManager_.Loop();
			sceneManager_.Draw();

			//===============

			//FPS�v�Z
			FrameRate::CalcFPS();
#ifdef _DEBUG
			//FPS�\��
			FrameRate::DrawFPS();
#endif // _DEBUG

			//�t���b�v�֐��i���[�v�̏I���ɂP�x�����s���j
			ScreenFlip();
		}
	}

	//���j���֐�
	void GameSystem::Fin()
	{
		//�G�t�F�N�g�S��~
		CEffekseerCtrl::StopAll();
		//�G�t�F�N�g���j��
		CEffekseerCtrl::Exit();

		//�J�������j��
		CameraManager::GetInstance()->Fin();

		//��ʏ��j��
		sceneManager_.Fin();

		//�����j��
		SoundManager::GetInstance()->Fin();
		SoundManager::GetInstance()->DeleteInstance();

		//DX���C�u�����̏I������
		//�Ō�ɂP�񂾂���鏈���������ɏ���
		DxLib_End();
	}
}
