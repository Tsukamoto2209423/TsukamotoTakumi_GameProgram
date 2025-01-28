#include "CameraManager.h"
#include "Camera.h"
#include "DebugCamera.h"
#include <Input/KeyBoard/InputKeyBoard.h>

namespace BOUDAMA
{
	//�����������֐�
	void CameraManager::Init(void)
	{
		//�󂶂�Ȃ���Ηv�f�ǉ�
		if (cameras_.empty())
		{
			cameras_.emplace_back(std::make_shared<Camera>());

#ifdef _DEBUG
			cameras_.emplace_back(std::make_shared<DebugCamera>());
#endif // DEBUG

		}

		//�Q�[���v���C�E�f�o�b�O�J�����̏���������	
		cameras_[CAMERA_STATE::PLAY]->Init();

#ifdef _DEBUG
		cameras_[CAMERA_STATE::DEBUG]->Init();
#endif // DEBUG


	}

	//�ړ������֐�
	void CameraManager::Step(const Vector3D& playerPos)
	{

#ifdef _DEBUG
		//�؂�ւ�
		if (InputKeyBoard::IsKeyRelease(KEY::L))
		{
			if (state_ == CAMERA_STATE::PLAY)
			{
				//�f�o�b�O�ɐ؂�ւ�
				state_ = CAMERA_STATE::DEBUG;

				cameras_[CAMERA_STATE::DEBUG]->SetPos(cameras_[CAMERA_STATE::PLAY]->GetPos());
				cameras_[CAMERA_STATE::DEBUG]->SetTarget(cameras_[CAMERA_STATE::PLAY]->GetTarget());
				cameras_[CAMERA_STATE::DEBUG]->SetUp(cameras_[CAMERA_STATE::PLAY]->GetUp());
				cameras_[CAMERA_STATE::DEBUG]->SetDir(cameras_[CAMERA_STATE::PLAY]->GetDir());

				return;
			}

			if (state_ == CAMERA_STATE::DEBUG)
			{
				//�Q�[���v���C�ɐ؂�ւ�
				state_ = CAMERA_STATE::PLAY;

				return;
			}
		}

#endif // DEBUG

		//�Q�[���v���C�E�f�o�b�O�̕��򏈗�	
		cameras_[state_]->Step(playerPos);
	}

	//�X�V�֐�
	void CameraManager::UpDate(void)
	{
		//�Q�[���v���C�E�f�o�b�O�̕��򏈗�	
		cameras_[state_]->UpDate();
	}

	//�j�������֐�
	void CameraManager::Fin(void)
	{
		if (cameras_.empty())
		{
			return;
		}

		for (auto&& camera = cameras_.cbegin(); camera != cameras_.cend();)
		{
			camera = cameras_.erase(camera);
		}

		cameras_.shrink_to_fit();
	}
}
