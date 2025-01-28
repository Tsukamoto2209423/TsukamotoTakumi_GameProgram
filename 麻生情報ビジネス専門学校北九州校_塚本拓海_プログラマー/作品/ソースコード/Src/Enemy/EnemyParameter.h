#pragma once

#include "Vector/Vector3D.h"
#include <type_traits>

namespace BOUDAMA
{
	//�G�̒�`���

	//�_���}
	namespace DARUMA
	{
		//�G�̃p�X
		constexpr char PATH[] = "Data/Model/Enemy/darumaEnemy.x";

		//�G�̍ő吔
		constexpr int MAX_NUM = 40;

		//�n�[�h���[�h���G���h���X���[�h�̓G�̍ő吔
		constexpr int HARD_MAX_NUM = 80;

		//�̗�
		constexpr int HP = 5;

		//���a
		constexpr float RADIUS = 50.0f;

		//����
		constexpr float SPEED = 7.5f;

		//�d��
		constexpr float GRAVITY = 4.5f;

		//�����ʒu
		constexpr Vector3D INIT_POS = { 0.0f,100.0f,3750.0f };

		//�G��X���̏����ʒu
		constexpr float INIT_POS_X = 500.0f;

		//�G��Z���̏����ʒu
		constexpr float INIT_POS_Z = 3150.0f;

		//X����Z���ōs����ő�̈ʒu
		constexpr float MAX_POS_X_Z = 7000.0f;

		//�G��X���̏o���͈�
		constexpr int INIT_MAX_APPEAR_RANGE_X = 1000;

		//�G��Z���̏o���͈�
		constexpr int INIT_MAX_APPEAR_RANGE_Z = 100;

		//�ZF���Ƃɏo������
		constexpr int APPEAR_MAX_TIME = 30;

		//�|���ꂽ�Ƃ��ɃX�R�A�ɉ��Z�����_��
		constexpr unsigned int ADD_SCORE_NUM = 300;

	}

	//����
	namespace MONSTER
	{
		//�G�̃p�X
		constexpr char PATH[] = "Data/Model/Enemy/MonsterEnemy.x";


		//�G�̍ő吔
		constexpr int MAX_NUM = 5;

		//�n�[�h���[�h���G���h���X���[�h�̓G�̍ő吔
		constexpr int HARD_MAX_NUM = 10;

		//�̗�
		constexpr int HP = 5;

		//�ړ�����p�x�؂�ւ�����
		constexpr int DIRECTION_CHANGE_INTERVAL = 180;

		//�ړ�����p�x�؂�ւ�����
		constexpr int REACTION_MAX_TIME = 120;

		//�U�����ߍő厞��
		constexpr int ATTACK_CHARGE_MAX_TIME = 60;

		//�U�����Ԃ̍ő�l
		constexpr int ATTACK_MAX_TIME = 120;

		//�U����̍d������
		constexpr int ATTACK_STUN_TIME = 60;

		//�ZF���Ƃɏo������
		constexpr int APPEAR_MAX_TIME = 90;


		//�|���ꂽ�Ƃ��ɃX�R�A�ɉ��Z�����_��
		constexpr unsigned int ADD_SCORE_NUM = 500;


		//X����Z���ōs����ő�̈ʒu
		constexpr float MAX_POS_X_Z = 7000.0f;

		//�n�ʂɒ��n�����Ƃ��̈ʒu
		constexpr float GROUND_POS_Y = 35.0f;

		//�m�b�N�o�b�N�̂Ƃ��ɁZ���㏸������
		constexpr float KNOCKBACK_Y_POWER = 6.5f;

		//���a
		constexpr float RADIUS = 80.0f;

		//����
		constexpr float SPEED = 2.0f;

		//�ǂ������鑬��
		constexpr float CHASE_SPEED = 11.75f;

		//�U������Ƃ��̑���
		constexpr float ATTACK_SPEED = 50.0f;

		//�ړ����̍ő�̑���
		constexpr float MAX_SPEED = 25.0f;

		//�G�𔭌��ł���͈�
		constexpr float FIND_OUT_RANGE = 1000.0f;

		//�G�𔭌��ł���͈͂̓��
		constexpr float SQUARE_FIND_OUT_RANGE = FIND_OUT_RANGE * FIND_OUT_RANGE;

		//�d��
		constexpr float GRAVITY = 7.5f;


		//������ʒu
		constexpr Vector3D INIT_POS = { 0.0f,100.0f,1450.0f };

		//�G�̏�ɏo������u�I�v�̋���(X��,Y��,Z��)
		constexpr Vector3D ADD_EXCLAMATION_DISTANCE = { 0.0f, 75.0f, 0.0f };

	}

	//���e��
	namespace BOMBER
	{
		//�G�̃p�X
		constexpr char PATH[] = "Data/Model/Enemy/BomberEnemy.x";

		//�G�̍ő吔
		constexpr int MAX_NUM = 3;

		//�n�[�h���[�h���G���h���X���[�h�̓G�̍ő吔
		constexpr int HARD_MAX_NUM = 5;


		//�ړ�����p�x�؂�ւ�����
		constexpr int DIRECTION_CHANGE_INTERVAL = 180;

		//�G�𔭌������Ƃ��̋����Ĕ������鎞��
		constexpr int REACTION_MAX_TIME = 120;


		//�U����̍d������
		constexpr int ATTACK_STUN_TIME = 210;

		//�ZF���Ƃɏo������
		constexpr int APPEAR_MAX_TIME = 90;

		//�̗�
		constexpr int HP = 10;


		//�|���ꂽ�Ƃ��ɃX�R�A�ɉ��Z�����_��
		constexpr unsigned int ADD_SCORE_NUM = 1000;

		//�����ʒu
		constexpr Vector3D INIT_POS = { 0.0f,150.0f,3150.0f };

		//�G�̏�ɏo������u�I�v�̋���(X��,Y��,Z��)
		constexpr Vector3D ADD_EXCLAMATION_DISTANCE = { 0.0f, 75.0f, 0.0f };

		//X����Z���ōs����ő�̈ʒu
		constexpr float MAX_POS_X_Z = 7000.0f;

		//1�t���[���ňړ����鑬��
		constexpr float SPEED = 1.75f;

		//�ő�̑���
		constexpr float MAX_SPEED = 11.5f;

		//�ǂ������鑬��
		constexpr float RUN_AWAY_SPEED = 10.5f;
		
		//�Y�������������邽�߂ɐ����g�ɂ�����W��
		constexpr float FLOAT_MOTION_BOOST = 3.5f;

		//�n�ʂɒ��n�����Ƃ��̈ʒu
		constexpr float GROUND_POS_Y = 100.0f;

		//�d��
		constexpr float GRAVITY = 1.5f;

		//���a
		constexpr float RADIUS = 50.0f;


		//�G�𔭌��ł���͈�
		constexpr float FIND_OUT_RANGE = 1250.0f;

		//�G�𔭌��ł���͈͂̓��
		constexpr float SQUARE_FIND_OUT_RANGE = FIND_OUT_RANGE * FIND_OUT_RANGE;


		//�G�𔭌������Ƃ��ɋ߂Â��ŏ��͈̔�
		constexpr float CHASE_MIN_RANGE = 950.0f;

		//�G�𔭌������Ƃ��ɋ߂Â��ŏ��͈̔͂̓��
		constexpr float SQUARE_CHASE_MIN_RANGE = CHASE_MIN_RANGE * CHASE_MIN_RANGE;

	}

	
	//�G�Ǘ��N���X�̏��
	namespace ENEMY_MANAGER
	{
		//�Q�[���J�n���ɗN�����鐔
		constexpr int INIT_APPEAR_NUM = 15;

		//�G�́ZF���Ƃɏo������
		constexpr int APPEAR_TIME_INTERVAL = 20;

		//�t�B�[�o�[�^�C���̍ő厞��
		constexpr int MAX_FEVER_TIME = 1200;

		//X����Z���ōs����ő�̈ʒu
		constexpr float MAX_POS_X_Z = 7000.0f;

		//�G�̏�ɏo������u�I�v�̋���(X��,Y��,Z��)
		constexpr Vector3D ADD_EXCLAMATION_DISTANCE = { 0.0f, 75.0f, 0.0f };

		//�G�ꗗ
		enum class ENEMY_LIST
		{
			DARUMA,
			MONSTER,
			BOMBER,

			ALL_NUM
		};

		//�ʏ�̓G�̐�
		constexpr int MAX_NUM_LIST[static_cast<int>(ENEMY_LIST::ALL_NUM)] =
		{
			DARUMA::MAX_NUM,
			MONSTER::MAX_NUM,
			BOMBER::MAX_NUM
		};

		//�n�[�h���[�h���G���h���X���[�h�̓G�̐�
		constexpr int HARD_MAX_NUM_LIST[static_cast<int>(ENEMY_LIST::ALL_NUM)] =
		{
			DARUMA::HARD_MAX_NUM,
			MONSTER::HARD_MAX_NUM,
			BOMBER::HARD_MAX_NUM
		};

		//�G�̏o���Ԋu�ꗗ�\
		constexpr int APPEAR_MAX_TIME_LIST[static_cast<int>(ENEMY_LIST::ALL_NUM)] =
		{
			DARUMA::APPEAR_MAX_TIME,
			MONSTER::APPEAR_MAX_TIME,
			BOMBER::APPEAR_MAX_TIME
		};

		//�G�̃p�X�ꗗ�\
		constexpr const char* PATH_LIST[static_cast<int>(ENEMY_LIST::ALL_NUM)] =
		{
			DARUMA::PATH,
			MONSTER::PATH,
			BOMBER::PATH
		};



		//�͈�for���ł�������
		constexpr ENEMY_LIST begin(ENEMY_LIST) { return ENEMY_LIST::DARUMA; }

		constexpr ENEMY_LIST end(ENEMY_LIST) { return ENEMY_LIST::ALL_NUM; }

		constexpr ENEMY_LIST operator*(ENEMY_LIST dir) { return dir; }

		constexpr ENEMY_LIST operator++(ENEMY_LIST& dir)
		{
			return dir = ENEMY_LIST(std::underlying_type_t<ENEMY_LIST>(dir) + 1);
		}

	}
}
