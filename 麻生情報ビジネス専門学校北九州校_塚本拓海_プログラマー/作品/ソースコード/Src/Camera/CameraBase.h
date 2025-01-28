#pragma once

#include <Vector/Vector3D.h>
#include "Transform/Transform.h"

namespace BOUDAMA
{
	//�J�������N���X
	class CameraBase : public Transform
	{
	protected:
		//�����_
		Vector3D target_;

		//�����
		Vector3D up_;

	public:
		//�R���X�g���N�^
		CameraBase() {}

		//�f�X�g���N�^
		virtual ~CameraBase() {}

		//�����������֐�
		virtual void Init(void) = 0;

		//�ړ������֐�
		virtual void Step(const Vector3D& playerPos) = 0;

		//�X�V�֐�
		virtual void UpDate(void) = 0;


		//�����_�擾
		inline Vector3D GetTarget(void) const { return target_; }

		//�����_�擾
		inline void SetTarget(const Vector3D& target) { target_ = target; }


		//������擾
		inline Vector3D GetUp(void) const { return up_; }

		//������ݒ�
		inline void SetUp(const Vector3D& up) { up_ = up; }


	};
}
