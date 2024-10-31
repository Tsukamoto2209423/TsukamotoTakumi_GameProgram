#include "CameraManager.h"
#include "Camera.h"
#include "DebugCamera.h"
#include <Input/KeyBoard/InputKeyBoard.h>

namespace BOUDAMA
{
	//初期化処理関数
	void CameraManager::Init(void)
	{
		//空じゃなければ要素追加
		if (cameras_.empty())
		{
			cameras_.emplace_back(std::make_shared<Camera>());

#ifdef _DEBUG
			cameras_.emplace_back(std::make_shared<DebugCamera>());
#endif // DEBUG

		}

		//ゲームプレイ・デバッグカメラの初期化処理	
		cameras_[CAMERA_STATE::PLAY]->Init();

#ifdef _DEBUG
		cameras_[CAMERA_STATE::DEBUG]->Init();
#endif // DEBUG


	}

	//移動処理関数
	void CameraManager::Step(const Vector3D& playerPos)
	{

#ifdef _DEBUG
		//切り替え
		if (InputKeyBoard::IsKeyRelease(KEY::L))
		{
			if (state_ == CAMERA_STATE::PLAY)
			{
				//デバッグに切り替え
				state_ = CAMERA_STATE::DEBUG;

				cameras_[CAMERA_STATE::DEBUG]->SetPos(cameras_[CAMERA_STATE::PLAY]->GetPos());
				cameras_[CAMERA_STATE::DEBUG]->SetTarget(cameras_[CAMERA_STATE::PLAY]->GetTarget());
				cameras_[CAMERA_STATE::DEBUG]->SetUp(cameras_[CAMERA_STATE::PLAY]->GetUp());
				cameras_[CAMERA_STATE::DEBUG]->SetDir(cameras_[CAMERA_STATE::PLAY]->GetDir());

				return;
			}

			if (state_ == CAMERA_STATE::DEBUG)
			{
				//ゲームプレイに切り替え
				state_ = CAMERA_STATE::PLAY;

				return;
			}
		}

#endif // DEBUG

		//ゲームプレイ・デバッグの分岐処理	
		cameras_[state_]->Step(playerPos);
	}

	//更新関数
	void CameraManager::UpDate(void)
	{
		//ゲームプレイ・デバッグの分岐処理	
		cameras_[state_]->UpDate();
	}

	//破棄処理関数
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
