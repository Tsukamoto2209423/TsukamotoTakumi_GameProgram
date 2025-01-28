#pragma once

namespace BOUDAMA
{
	//�������ԃN���X�Ŏg���萔
	namespace TIME_LIMIT
	{
		//�ŏ��ɐݒ肷�鐧������(�~���b)
		constexpr int INIT_TIME = 91000;

		//�ŏ��ɕ`�悷��E�[�̐�����X���̈ʒu
		constexpr int INIT_NUM_POS_X = 1252;

		//�ŏ��ɕ`�悷��E�[�̐�����Y���̈ʒu
		constexpr int INIT_NUM_POS_Y = 40;

		//������`�悷��Ԋu
		constexpr int NUM_POS_INTERVAL = 48;


		//�u�̂���v�̉摜�̃p�X
		constexpr char CHARA_PATH[] = { "Data/Image/Limit_Time_Character.png" };

		//�u�̂���v�̉摜��`�悷��X���̈ʒu
		constexpr int CHARA_POS_X = 1060;

		//�u�̂���v�̉摜��`�悷��Y���̈ʒu
		constexpr int CHARA_POS_Y = 44;


		//�u���v�̉摜�̃p�X
		constexpr char INFINITY_PATH[] = { "Data/Image/Infinity.PNG" };

		//�u���v�̉摜��`�悷��X���̈ʒu
		constexpr int INFINITY_POS_X = 1200;

		//�u���v�̉摜��`�悷��Y���̈ʒu
		constexpr int INFINITY_POS_Y = 44;


		//�R���}�̉摜��`�悷��X���̈ʒu
		constexpr int COMMA_POS_X = 1225;

		//�R���}�̉摜��`�悷��Y���̈ʒu
		constexpr int COMMA_POS_Y = 51;
	}
}
