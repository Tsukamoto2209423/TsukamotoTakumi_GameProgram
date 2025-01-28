#pragma once

#include "Vector/Vector3D.h"

namespace BOUDAMA
{
	namespace BOMB
	{
		//���f���p�X
		constexpr char PATH[] = "Data/Model/Bomb/Beta_Bomb.x";

		//�����ꂽ�Ƃ��ɏ�Ɉړ�������l
		constexpr Vector3D HOLD_UP_DISTANCE = { 0.0f,115.0f,0.0f };

		//�n�ʂ̈ʒu
		constexpr float GROUND_POS = 40.5f;

		//�d��
		constexpr float GRAVITY = 7.75f;

		//�������̑���
		constexpr float THROW_SPEED = 55.0f;

		//���a
		constexpr float RADIUS = 55.0f;

		//���������Ƃ��̔��a
		constexpr float EXPLODE_RADIUS = 500.0f;

		//���������Ƃ��ɔ�e����ɗ^���鑬���̃u�[�X�g
		constexpr float EXPLOSION_BOOST = 35.0f;


		//������ʒu
		constexpr float INIT_POS_X_Z = -1000.0f;

		//X����Z���ōs����ő�̈ʒu
		constexpr float MAX_POS_X_Z = 7000.0f;

		//�U����
		constexpr int ATTACK_POWER = 5;

		//�����_���Ŕz�u����Ƃ��ɏ�����ʒu�ɑ����ő�l
		constexpr int INIT_POS_XZ_RAND_MAX_NUM = 2 * static_cast<int>(-INIT_POS_X_Z);

		//�����ɏo���ł���ő吔
		constexpr int MAX_NUM = 5;

		//��������܂ł̎���
		constexpr int MAX_EXPLODE_TIME_LIMIT = 200;

		//�������Ă��鎞��
		constexpr int MAX_EXPLOSION_TIME = 75;

		//�����x���_��
		constexpr int WARNING_BLINK_TIME = 80;

		enum STATE
		{
			NORMAL,
			IGNITION,
			TRIGGER,
			EXPLOSION,


			NUM
		};
	}

	using BOMB_STATE = BOMB::STATE;


	namespace HEAL
	{
		//�摜�p�X
		constexpr char PATH[] = "Data/Model/Heal/HealItem.x";

		//�ő吔
		constexpr int MAX_NUM = 3;

		//�񕜂�����l
		constexpr int HEAL_VALUE = 5;

		//���a
		constexpr float RADIUS = 85.0f;

		//�n�ʂ̈ʒu
		constexpr float GROUND_POS = 95.5f;

		//�d��
		constexpr float GRAVITY = 6.0f;

		//������ʒu
		constexpr float INIT_POS_X_Z = -1000.0f;

		//�����_���Ŕz�u����Ƃ��ɏ�����ʒu�ɑ����ő�l
		constexpr int INIT_POS_XZ_RAND_MAX_NUM = 2 * static_cast<int>(-INIT_POS_X_Z);


		//�Y�������������邽�߂ɐ����g�ɂ�����W��
		constexpr float FLOAT_MOTION_BOOST = 1.5f;

		//��Ɉړ�������l
		constexpr Vector3D UP_DISTANCE = { 0.0f,60.0f,0.0f };

	}

	namespace ITEM
	{
		enum class ITEM_LIST
		{
			BOMB,

			HEAL
		};


		constexpr int ITEM_MAX_NUM_LIST[] =
		{
			BOMB::MAX_NUM,
			HEAL::MAX_NUM
		};
	}

	using ITEM_LIST = ITEM::ITEM_LIST;
}
