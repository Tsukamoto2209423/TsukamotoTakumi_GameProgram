#pragma once

namespace BOUDAMA
{
	//�t�F�[�h�N���X�Ŏg����`�Q
	namespace FADE
	{
		enum STATE
		{
			NONE,
			F_IN,
			F_OUT,
		};

		//�t�F�[�h�C���E�t�F�[�h�A�E�g���Ɍ�����摜�ꗗ
		constexpr char PATH[] = "Data/Image/Loading/LoadingImageList.csv";

		//�t�F�[�h�C���E�t�F�[�h�A�E�g���Ɍ�����G�t�F�N�g�摜�ꗗ
		constexpr char EFFECT_PATH[] = "Data/Image/Loading/ImageEffect.csv";

		//���ߓx�ɉ��Z���鑬��
		constexpr int ALPHA_SPEED = 3;

		//�摜�𓮂�������
		constexpr int MOVE_SPEED = 15;

		//�摜�̑傫��
		constexpr int IMAGE_SIZE = 512;

		enum EFFECT
		{
			//�W����
			CONCENTRATION_LINE_1,
			CONCENTRATION_LINE_2,
			CONCENTRATION_LINE_3,
			CONCENTRATION_LINE_END,
		};
	}
}
