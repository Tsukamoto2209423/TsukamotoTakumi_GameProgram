#pragma once

#include "EnemyBase.h"

namespace BOUDAMA
{
	//�G�N���X
	class EnemyMonster : public EnemyBase
	{
	private:

	public:
		//�R���X�g���N�^
		EnemyMonster();

		//�f�X�g���N�^
		~EnemyMonster() override;

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
