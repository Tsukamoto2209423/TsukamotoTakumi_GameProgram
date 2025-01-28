#include "DebugCamera.h"
#include "Camera.h"
#include <Input/Mouse/Mouse.h>
#include "Input/KeyBoard/InputKeyBoard.h"
#include "Math/MyMath.h"
#include "Matrix/Matrix3D.h"
#include <Common.h>

namespace BOUDAMA
{
	//�J�����������֐�
	void DebugCamera::Init(void)
	{
		//// �J�����̐ݒ�
		//SetCameraNearFar(1.0f, 27000.0f);

		//SetupCamera_Perspective(MyMath::PI_OVER_THREE);

		pos_ = { 0.0f, CAMERA::POS_Y_DISTANCE, CAMERA::POS_Z_DISTANCE };		//�J�����ʒu
		target_ = { 0.0f, 0.0f, 0.0f };										//�����_
		up_ = { 0.0f, 1.0f, 0.0f };												//�����
		rot_ = { MyMath::PI_OVER_SIX, 0.0f, 0.0f };							//�J�����p�x

		dir_ = { 0.0f,0.0f,1.0f };

		//�J�����ʒu�ݒ�
		SetCameraPositionAndTargetAndUpVec(pos_, target_, up_);

	}

	//�J�����s�������֐�
	void DebugCamera::Step(const Vector3D& playerPos)
	{
		//�J�����̏ꏊ�ݒ�

		//���V�t�g�L�[�������Ă���Ɖ���
		float speed = InputKeyBoard::IsKeyDown(KEY::L_SHIFT) ? CAMERA::FAST_SPEED : CAMERA::SPEED;
		Vector3D cameraSpeed = dir_ * speed;
		cameraSpeed.y = 0.0f;

		//�㏸
		if (InputKeyBoard::IsKeyDown(KEY::Q))
		{
			target_.y -= CAMERA::UP_DOWN_SPEED;
		}

		//���~
		if (InputKeyBoard::IsKeyDown(KEY::E))
		{
			target_.y += CAMERA::UP_DOWN_SPEED;
		}

		//�O�ړ�
		if (InputKeyBoard::IsKeyDown(KEY::W))
		{
			target_ += cameraSpeed;
		}
		//��ړ�
		if (InputKeyBoard::IsKeyDown(KEY::S))
		{
			target_ -= cameraSpeed;
		}

		//���V�t�g�L�[�������Ă���Ɖ���
		//���E�ɐ����ړ�����̂� ��/2 ����
		float left_right_speed = InputKeyBoard::IsKeyDown(KEY::L_SHIFT) ? CAMERA::FAST_SPEED : CAMERA::SPEED;
		Vector3D left_right_cameraSpeed = dir_ * Matrix3D::GetYawMatrix( MyMath::HALF_PI) * speed;
		left_right_cameraSpeed.y = 0.0f;

		//���ړ�
		if (InputKeyBoard::IsKeyDown(KEY::A))
		{
			//���Ȃ̂ō��Ɉړ�
			target_ -= left_right_cameraSpeed;
		}
		//�E�ړ�
		if (InputKeyBoard::IsKeyDown(KEY::D))
		{
			//�a�Ȃ̂ŉE�Ɉړ�
			target_ += left_right_cameraSpeed;
		}



		//���]
		if (InputKeyBoard::IsKeyDown(KEY::UP))
		{
			// rot_�̏㉺�̊p�x�Ƃ̒�`��� (-��/2) + ��/100 <= �� <= (��/2) - ��/100
			if (rot_.x > -MyMath::HALF_PI + CAMERA::ROT_UP_DOWN_SPEED)
			{
				rot_.x -= CAMERA::ROT_UP_DOWN_SPEED;
			}
		}

		//����]
		if (InputKeyBoard::IsKeyDown(KEY::DOWN))
		{
			// rot_�̏㉺�̊p�x�Ƃ̒�`��́@(��/2) + ��/100 <= �� <= (��/2) - ��/100
			if (rot_.x < MyMath::HALF_PI - CAMERA::ROT_UP_DOWN_SPEED)
			{
				rot_.x += CAMERA::ROT_UP_DOWN_SPEED;
			}

		}

		// �E��]
		if (InputKeyBoard::IsKeyDown(KEY::RIGHT))
		{
			rot_.y += CAMERA::ROT_RIGHT_LEFT_SPEED;
		}

		// ����]
		if (InputKeyBoard::IsKeyDown(KEY::LEFT))
		{
			rot_.y -= CAMERA::ROT_RIGHT_LEFT_SPEED;

		}

		//�}�E�X���_����
		const Vector3D MouseMoveValue(InputMouse::GetMoveValueVertical(), InputMouse::GetMoveValueHorizontal(), 0.0f);

		if (MyMath::Abs(MouseMoveValue.x) > Common::KINDA_SMALL_NUMBER || MyMath::Abs(MouseMoveValue.y) > Common::KINDA_SMALL_NUMBER)
		{
			rot_ += MouseMoveValue * CAMERA::MOUSE_SENSITIVITY;
		}

		//rot_.x < 0
		if (rot_.x < 0.0f)
		{
			rot_.x = 0.0f;
		}

		//rot_.x > ��/2
		if (rot_.x >= MyMath::HALF_PI)
		{
			rot_.x = MyMath::HALF_PI - MyMath::INVERSE_TWO_PI;
		}

		//rot_.y < -��/2
		if (rot_.y < -MyMath::PI)
		{
			rot_.y = MyMath::PI;
		}

		//rot_.y > ��/2
		if (rot_.y > MyMath::PI)
		{
			rot_.y = -MyMath::PI;
		}
	}

	//�J�����X�V�֐�
	void DebugCamera::UpDate(void)
	{
		//�s��ɂ��J�����ʒu�v�Z
		Matrix3D RetCameraMat = Matrix3D::GetTranslateMatrix(target_)
			* Matrix3D::GetYawMatrix(rot_.y)
			* Matrix3D::GetPitchMatrix(rot_.x)
			* Matrix3D::GetTranslateMatrix(-target_.x, -target_.y, -target_.z - 1.0f);

		pos_ = RetCameraMat * target_;


		//�J���������Ă�������v�Z
		dir_ = (target_ - pos_).Normalize();

		//�J�����ʒu�ݒ�
		SetCameraPositionAndTargetAndUpVec(pos_, target_, up_);
	}
}
