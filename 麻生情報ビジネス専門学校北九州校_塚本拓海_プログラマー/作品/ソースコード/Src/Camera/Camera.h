#pragma once

#include "CameraBase.h"
#include "Vector/Vector3D.h"
#include "Math/MyMath.h"

namespace BOUDAMA
{
	namespace CAMERA
	{
		//�J�����ʒu��X��Z�����̔{��
		constexpr int POS_LEFT_RIGHT_DISTANCE_MULTIPLE = 40;

		//�J�����ʒu��Y����
		constexpr int POS_UP_DISTANCE = 30;

		//�J�����̃^�[�Q�b�g��Y����
		constexpr int TARGET_POS_Y_DISTANCE = 20;

		//�J��������ɏ㏸�����鋗��
		constexpr float POS_Y_DISTANCE = 590.0f;

		//�J��������O�Ɍ�ނ����鋗��
		constexpr float POS_Z_DISTANCE = -450.0f;

		//�J�����ړ����x
		constexpr float SPEED = 15.0f;
		
		//�㉺�����̃J�����ړ����x
		constexpr float UP_DOWN_SPEED = 10.0f;

		//�����J�����ړ����x
		constexpr float FAST_SPEED = 25.5f;

		//�J�������E��]���x
		constexpr float ROT_RIGHT_LEFT_SPEED = MyMath::PI / 30.0f;

		//�J�����㉺��]���x
		constexpr float ROT_UP_DOWN_SPEED = MyMath::PI * 0.01f;

		//�J���������_���E���x
		constexpr float TARGET_POS_LEFT_RIGHT_SPEED = 2.5f;

		//�J���������_�㉺���x
		constexpr float TARGET_POS_UP_DOWN_SPEED = 0.35f;

		//�Q�[���p�b�h�ŃJ��������]������Ƃ��ɂ�����␳�W��
		constexpr float GAMEPAD_ROT_COEFFICIENT = 0.04f;

		//�}�E�X�ŃJ��������]������Ƃ��ɂ�����␳�W��
		constexpr float MOUSE_SENSITIVITY = 0.01f;

		//�v���C���[�ɋ߂Â����Ƃ��ł���ŏ��̒�������
		constexpr float MIN_DISTANCE = 300.0f;

		//�v���C���[���牓�����邱�Ƃ��ł���ő�̒�������
		constexpr float MAX_DISTANCE = 750.0f;
	}

	//�J�����N���X
	class Camera : public CameraBase
	{
	private:
		//�J��������v���C���[�܂ł̋���
		float distanceToPlayer_;

	public:
		//�R���X�g���N�^
		Camera() { distanceToPlayer_ = 0.0f; }

		//�f�X�g���N�^
		~Camera() {}

		//�����������֐�
		void Init(void) override;

		//�ړ������֐�
		void Step(const Vector3D& playerPos) override;

		//�X�V�֐�
		void UpDate(void) override;
	};
}
