#pragma once

#include <memory>
#include "EnemyBase.h"

namespace BOUDAMA
{
	//�G�N���X
	class Enemy : public EnemyBase
	{
	private:

	public:
		//�R���X�g���N�^
		constexpr Enemy(void) {}

		//�f�X�g���N�^
		~Enemy() override {}

		//�����������֐�
		void Init(void) override;

		//�s�������֐�
		void Step(const Vector3D& playerPos) override;

		//�`�揈���֐�
		void Draw(void) override;

		//�o�������֐�
		void AppearanceRequest(void) override;


	};
}
