#pragma once

#include "CameraBase.h"

namespace BOUDAMA
{
	class DebugCamera final : public CameraBase
	{
	private:

	public:
		//�R���X�g���N�^
		DebugCamera() {}

		//�f�X�g���N�^
		~DebugCamera() {}

		//�����������֐�
		void Init(void) override;

		//�ړ������֐�
		void Step(const Vector3D& playerPos) override;

		//�X�V�֐�
		void UpDate(void) override;
	};
}
