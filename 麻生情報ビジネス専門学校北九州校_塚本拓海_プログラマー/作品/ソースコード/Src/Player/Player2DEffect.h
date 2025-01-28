#pragma once

#include <vector>
#include "Vector/Vector3D.h"

namespace BOUDAMA
{
	namespace PLAYER_EFFECT
	{
		//�v���C���[�����܂Ƃ߂�CSV�t�@�C��
		constexpr char PATH[] = "Data/Image/Player/ImageList.csv";

		//�摜�p
		enum IMAGE
		{
			//HP�\���p�̃n���h��
			HP,

			//"HP"�̉摜�̃n���h��
			HP_CHARA,

			//�W����
			CONCENTRATION_LINE_1,
			CONCENTRATION_LINE_2,
			CONCENTRATION_LINE_3,
			CONCENTRATION_LINE_END,

			//�_���[�W���󂯂��Ƃ��ɉ�ʂɕ\������_���[�W�G�t�F�N�g�摜
			DAMAGE,

			//�񕜂����Ƃ��ɉ�ʂɕ\������G�t�F�N�g�摜
			HEAL,

			//�摜�̑���
			ALL_NUM
		};

		//HP�o�[�̑傫��
		constexpr int HP_SIZE = 16;

		//HP�o�[�̕\���ʒu
		constexpr int HP_POS_X = 96;
		constexpr int HP_POS_Y = 32;

		//HP�̕\���ʒu
		constexpr int HP_CHARA_POS_X = 48;
		constexpr int HP_CHARA_POS_Y = 32;
	}

	//�v���C���[�Ɋւ���摜��`�悷��N���X
	class Player2DEffect final
	{
	private:
		//�摜�ꗗ�\
		std::vector<int> handles_;

		//���`�悵�Ă���W�����̔ԍ�
		int concentrationLineIndex_;

		//�摜�̓��ߓx(���l)
		int effectAlpha_;

		//���ʉ摜�̎��
		PLAYER_EFFECT::IMAGE effectState_;

	public:
		//�R���X�g���N�^
		constexpr Player2DEffect() : concentrationLineIndex_(0), effectAlpha_(0), effectState_() {};

		//�f�X�g���N�^	
		~Player2DEffect() {};

		//�����������֐�
		void Init(void);

		//�ǂݍ��ݏ����֐�
		void Load(void);

		//�s�������֐�
		void Step(void);

		//�`�揈���֐�
		void Draw(int playerHP, const Vector3D& velocity);

		//�j�������֐�
		void Fin(void);

		void EffectRequest(const PLAYER_EFFECT::IMAGE requestNum);

	};
}
