#pragma once

namespace BOUDAMA
{
	//�S�Ă̕����ɋ��ʂ���l
	namespace ALL_SUBSTANCE
	{
		//�Q�[���J�n���ɗN�����鐔
		constexpr int INIT_APPEAR_NUM = 20;

		//�G��|�����Ƃ��ɗN�����鐔
		constexpr int MAX_APPEAR_NUM = 5;


		//�d��
		constexpr float GRAVITY = 5.5f;

		//�n�ʈʒu
		constexpr float GROUND_POS = 21.0f;

		//��������������Ƃ��ɂ�����l
		constexpr float RESISTANCE_POWER = 0.9f;

		//X����Z���ōs����ő�̈ʒu
		constexpr float MAX_POS_X_Z = 7000.0f;

	}

	//����
	namespace SUBSTANCE
	{
		constexpr char PATH[] = "Data/Model/Substance/Substance.x";

		constexpr int ADD_SCORE_NUM = 150;

		constexpr short int MAX_NUM = 500;

		constexpr Vector3D INIT_POS = { 0.0f,70.0f,500.0f };

		constexpr float RADIUS = 17.0f;

		constexpr float GRAVITY = 5.5f;

	}

	//�h�f�J����
	namespace BIGSUBSTANCE
	{
		constexpr char PATH[] = "Data/Model/Substance/BigSubstance.x";

		constexpr int ADD_SCORE_NUM = 200;

		constexpr short int MAX_NUM = 100;

		constexpr Vector3D INIT_POS = { 0.0f,60.0f,500.0f };

		constexpr float RADIUS = 50.0f;
	}
}
