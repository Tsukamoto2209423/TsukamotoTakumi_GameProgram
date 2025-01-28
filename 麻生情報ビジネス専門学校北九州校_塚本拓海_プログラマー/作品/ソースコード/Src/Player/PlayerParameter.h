#pragma once

#include <Vector/Vector3D.h>

namespace BOUDAMA
{
	namespace PLAYER
	{
		//�v���C���[�̃p�X
		constexpr char PATH[] = { "Data/Model/Player/PlayerSyobon.x" };

		//�v���C���[�̍ő�HP
		constexpr int MAX_HP = 50;

		//�v���C���[�����񂾂Ƃ��̃G�t�F�N�g�\������
		constexpr int DEATH_EFFECT_TIME = 140;

		//�v���C���[�����ʒu
		constexpr Vector3D INIT_POS = { 0.0f,100.0f,0.0f };

		//�v���C���[�̃G�t�F�N�g���o���ʒu
		constexpr Vector3D EFFECT_POS = { 20.0f,50.0f,-10.0f };

		//���a
		constexpr float RADIUS = 25.0f;

		//�v���C���[���s����ő��X����Z���̈ʒu
		constexpr float MAX_POS_X_Z = 7000.0f;

		//�v���C���[�̑���
		constexpr float SPEED = 1.5f;

		//�v���C���[�̍ő�̑���
		constexpr float MAX_SPEED = 50.0f;

		//�v���C���[�̍ő�̑����̓��
		constexpr float MAX_SPEED_SQUARE = MAX_SPEED * MAX_SPEED;

		//�^�[�{��Ԃ̂Ƃ��A�Z�������ɉ��Z����
		constexpr float TURBO_CHARGE_POWER = 5.5f;

		//�G��|����悤�ɂȂ鑬�x�̓��
		constexpr float KILL_SPEED = 1000.0f;

		//�v���C���[�ɂ�����d��
		constexpr float GRAVITY = 8.5f;

		//�n�ʂɒ��n�����Ƃ��̈ʒu
		constexpr float GROUND_POS_Y = 35.0f;

		//��]�����Ƃ��ɂ�����␳�W��
		constexpr float ROTATION_COEFFICIENT = 0.0625f;

		//��]�����Ƃ��̖��C�W��
		constexpr float KINETIC_FRICTION_COEFFICIENT = 0.984375f;

	}
}
