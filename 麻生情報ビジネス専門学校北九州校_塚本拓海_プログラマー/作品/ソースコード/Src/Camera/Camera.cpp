#include "DxLib.h"
#include "Camera.h"
#include "Player/Player.h"
#include "Math/MyMath.h"
#include "Matrix/Matrix3D.h"
#include <math.h>
#include <Effekseer/Effekseer.h>
#include "Input/KeyBoard/InputKeyBoard.h"
#include <Input/GamePad/GamePad.h>
#include <Input/Mouse/Mouse.h>
#include <Input/Input.h>
#include <Common.h>


namespace BOUDAMA
{
	//�J�����������֐�
	void Camera::Init(void)
	{
		// �J�����̐ݒ�
		SetCameraNearFar(1.0f, 27000.0f);

		SetupCamera_Perspective(MyMath::PI_OVER_THREE);

		pos_ = { 0.0f, CAMERA::POS_Y_DISTANCE, CAMERA::POS_Z_DISTANCE };	//�J�����ʒu
		target_ = { 0.0f, 0.0f, 0.0f };												//�����_
		up_ = { 0.0f, 1.0f, 0.0f };												//�����
		rot_ = { MyMath::PI_OVER_SIX, 0.0f, 0.0f };						//�J�����p�x

		dir_ = { 0.0f,0.0f,1.0f };

		distanceToPlayer_ = CAMERA::POS_Z_DISTANCE;

		//�J�����ʒu�ݒ�
		SetCameraPositionAndTargetAndUpVec(pos_, target_, up_);

	}

	//�J�����s�������֐�
	void Camera::Step(const Vector3D& playerPos)
	{
		//�J�����̑Ώە�
		target_ = playerPos;

		if (Input::IsKeyKeep(GAME_INPUT::TURBO))
		{
			//�J�������������ő�̋����ɂ���
			distanceToPlayer_ = CAMERA::MAX_DISTANCE;

		}
		else
		{
			//�v���C���[�̈ʒu����J�����̈ʒu�܂ł̃x�N�g���쐬
			dir_ = playerPos - pos_;

			//�x�N�g���̒����擾
			distanceToPlayer_ = dir_.L2Norm();


			//�J����������ȏ�߂Â��Ȃ����������߂��ꍇ
			if (distanceToPlayer_ - CAMERA::SPEED <= CAMERA::MIN_DISTANCE)
			{
				// �J�������߂Â��鋗���܂ŉ�������
				distanceToPlayer_ = CAMERA::MIN_DISTANCE;

			}
			//�J����������ȏ㗣����Ȃ������𒴂����ꍇ
			else if (distanceToPlayer_ >= CAMERA::MAX_DISTANCE)
			{
				//�J�������������ő�̋����ɂ���
				distanceToPlayer_ = CAMERA::MAX_DISTANCE;
			}
			else
			{
				//�ǂ�ɂ����Ă͂܂�Ȃ��ꍇ�ǂ�������
				distanceToPlayer_ -= CAMERA::SPEED;
			}
		}

		//�������猩�ĉ������ɉ�]
		if (InputKeyBoard::IsKeyDown(KEY::UP))
		{
			rot_.x -= CAMERA::ROT_UP_DOWN_SPEED;

			// rot_�̏㉺�̊p�x�Ƃ̒�`��́@0 <= �� <= (��/2) - ��/100
			if (rot_.x < 0.0f)
			{
				rot_.x = 0.0f;
			}
		}

		//�������猩�ď�����ɉ�]
		if (InputKeyBoard::IsKeyDown(KEY::DOWN))
		{
			rot_.x += CAMERA::ROT_UP_DOWN_SPEED;

			// rot_�̏㉺�̊p�x�Ƃ̒�`��� (-��/2) + ��/100 <= �� <= (��/2) - ��/100
			if (rot_.x > MyMath::HALF_PI - CAMERA::ROT_UP_DOWN_SPEED)
			{
				rot_.x = MyMath::HALF_PI - CAMERA::ROT_UP_DOWN_SPEED;
			}
		}

		//�������猩�ĉE�����ɉ�]
		if (InputKeyBoard::IsKeyDown(KEY::LEFT))
		{
			rot_.y -= CAMERA::ROT_RIGHT_LEFT_SPEED;

			// rot_�̍��E�̊p�x�Ƃ̒�`��� -�� < �� <= ��
			if (rot_.y < -MyMath::PI)
			{
				rot_.y = MyMath::PI;
			}

		}

		//�������猩�č������ɉ�]
		if (InputKeyBoard::IsKeyDown(KEY::RIGHT))
		{
			rot_.y += CAMERA::ROT_RIGHT_LEFT_SPEED;

			// rot_�̍��E�̊p�x�Ƃ̒�`��� -�� <= �� < ��
			if (rot_.y > MyMath::PI)
			{
				rot_.y = -MyMath::PI;
			}

		}

		//�Q�[���p�b�h��R�X�e�B�b�N�擾
		const Vector3D GamePadRStick = InputGamePad::GetRStickVector();

		if (MyMath::Abs(GamePadRStick.x) > Common::KINDA_SMALL_NUMBER || MyMath::Abs(GamePadRStick.y) > Common::KINDA_SMALL_NUMBER)
		{
			rot_ += GamePadRStick * CAMERA::GAMEPAD_ROT_COEFFICIENT;
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
	void Camera::UpDate(void)
	{
		//�s��ɂ��J�����ʒu�v�Z
		Matrix3D RetCameraMat = Matrix3D::GetTranslateMatrix(target_)
			* Matrix3D::GetYawMatrix(rot_.y)
			* Matrix3D::GetPitchMatrix(rot_.x)
			* Matrix3D::GetTranslateMatrix(-target_.x, -target_.y, -target_.z - distanceToPlayer_);

		pos_ = RetCameraMat * target_;

		//�J���������Ă�������v�Z
		dir_ = target_ - pos_;

		//�J�����ʒu�ݒ�
		SetCameraPositionAndTargetAndUpVec(pos_, target_, up_);
	}
}
