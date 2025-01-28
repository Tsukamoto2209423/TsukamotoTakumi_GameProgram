#pragma once

#include "BulletBase.h"

namespace BOUDAMA
{
	namespace BIG_BULLET
	{
		//���f���p�X
		constexpr char PATH[] = "Data/Model/Bullet/Beta_BigBullet.x";

		//�e��
		constexpr float SPEED = 70.5f;

		//�ő吔
		constexpr int MAX_NUM = 20;

		//����
		constexpr int MAX_LIFE_SPAN = 5;

		//���a
		constexpr float RADIUS = 60.0f;

		//X����Z���ōs����ő�̈ʒu
		constexpr float MAX_POS_X_Z = 7000.0f;

	}

	//�e�N���X
	class BigBullet : public BulletBase
	{
	public:
		//�R���X�g���N�^
		BigBullet();
		//�f�X�g���N�^
		~BigBullet();

		//�ǂݍ��ݏ����֐�
		void Load(int origineHandle) override;

		//�s�������֐�
		void Step(void) override;

		//�����蔻�菈��
		void HitCalculation(void) override;

	};
}
