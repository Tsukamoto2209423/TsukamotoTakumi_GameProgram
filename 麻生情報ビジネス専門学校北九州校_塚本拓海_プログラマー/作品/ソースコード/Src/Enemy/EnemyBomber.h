#pragma once

#include "EnemyBase.h"
#include "EnemyParameter.h"
#include "Item/Bomb/Bomb.h"
#include "Math/MyMath.h"

namespace BOUDAMA
{
	//���e���N���X
	class EnemyBomber : public EnemyBase
	{
	private:
		//�Q�Ƃ��锚�e
		std::shared_ptr<ItemBase> bomb_;

		//���e�𓊂������̃X�^������
		int bombThrowStunTime_;

		//�Y��(float)�������g�p����Ƃ��Ɏg���p�x��
		float floatMotionTheta_;

	public:
		//�R���X�g���N�^
		constexpr EnemyBomber() : bombThrowStunTime_(0), floatMotionTheta_(0.0f) {}

		EnemyBomber(const auto& bomb) : bomb_(bomb), bombThrowStunTime_(0), floatMotionTheta_(0.0f) {}
		
		//�f�X�g���N�^
		~EnemyBomber() override {}

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
