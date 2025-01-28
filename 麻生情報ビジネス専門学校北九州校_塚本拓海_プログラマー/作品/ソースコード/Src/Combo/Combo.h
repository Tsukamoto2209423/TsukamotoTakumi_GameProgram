#pragma once

namespace BOUDAMA
{
	namespace COMBO
	{
		//�u�R���{�v�̉摜�p�X
		constexpr char PATH[] = "Data/Image/combo_chara_normal.PNG";

		//���ȏ�R���{����ƕ\�������F�Ⴂ�́u�R���{�v�̉摜�p�X
		constexpr char PRE_PATH[] = "Data/Image/combo_chara_presious.PNG";

		//�R���{���r�؂��܂ł̎���
		constexpr int MAX_COUNT_TIME = 300;

		//�E�[�̐������\�������X�̊�̏ꏊ
		constexpr int INIT_POS_X = 150;

		//�E�[�̐������\�������Y�̊�̏ꏊ
		constexpr int INIT_POS_Y = 460;

		//�`�悷��摜��傫������R���{��
		constexpr int ADD_SCALE_COMBO_NUM = 50;

		//�ŏ��̉摜�{��
		constexpr float INIT_SCALE = 0.75f;

		//�傫���Ȃ������̉摜�{��
		constexpr float BIG_SCALE = 1.0f;

	}

	//�R���{���v���N���X
	class Combo
	{
	private:
		//�u�R���{�I�v�̉摜�n���h��
		int charaHandle_;

		//���ȏ�R���{����ƕ\�������F�Ⴂ�́u�R���{�I�v�̉摜�n���h��
		int presiousCharaHandle_;

		//�R���{���v���p�ϐ�
		int comboNum_;

		//�R���{���r�؂��܂ł̎��Ԃ��v������ϐ�
		int countTime_;

		//�摜��`�悷��ۂɋ󂯂镝
		int drawInterval_;

		//�摜�̑傫��
		float graphScale_;

	public:
		//�R���X�g���N�^
		Combo();

		//�f�X�g���N�^
		~Combo();

		//�����������֐�
		void Init(void);

		//�ǂݍ��ݏ���
		void Load(void);

		//�s�������֐�
		void Step(void);

		//�`�揈���֐�
		void Draw(void);

		//�j�������֐�
		void Fin(void);


		//���݂̃R���{���擾
		inline int GetComboNum(void) const { return comboNum_; }

		//���݂̃R���{���ݒ�
		inline void SetComboNum(int num) { comboNum_ = num; }

		//���݂̃R���{��+1
		inline void AddComboNum(void)
		{
			//�R���{����ǉ����A���Ԃ�������
			++comboNum_;
			countTime_ = COMBO::MAX_COUNT_TIME;
		};


		//�R���{���r�؂��܂ł̎��Ԏ擾
		inline int GetComboCountTime(void) const { countTime_; }

		//�R���{���r�؂��܂ł̎��Ԑݒ�
		inline void SetComboCountTime(int num) { countTime_ = num; }

	};
}
