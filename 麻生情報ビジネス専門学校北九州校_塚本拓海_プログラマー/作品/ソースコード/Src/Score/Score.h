#pragma once

namespace BOUDAMA
{
	namespace SCORE
	{
		//�u�X�R�A�v�̉摜�p�X
		constexpr char SCORE_CHARA_PATH[] = "Data/Image/ScoreChara.png";

		//�u�x�X�g�X�R�A�v�̉摜�p�X
		constexpr char BEST_SCORE_CHARA_PATH[] = "Data/Image/BestScoreChara.png";

		//�Z�s�N�Z�����Ƃɐ�����`�悷��
		constexpr int DRAW_POS_INTERVAL = 48;


		//�u�X�R�A�v�̕������`�悳���Ƃ��Ɍ��Z����l
		constexpr int SCORE_CHARA_SUB_POS_X = 250;

		//�v���C���Ɏg������
		namespace PLAY
		{
			//�E�[�̐������\�������X�̊�̏ꏊ
			constexpr int INIT_POS_X = 1250;

			//�E�[�̐������\�������Y�̊�̏ꏊ
			constexpr int INIT_POS_Y = 690;
		}

		//�N���A�ƃQ�[���I�[�o�[���Ɏg������
		namespace CLEAR_GAMEOVER
		{
			//�E�[�̐������\�������X�̊�̏ꏊ
			constexpr int INIT_POS_X = 760;

			//�E�[�̐������\�������Y�̊�̏ꏊ
			constexpr int INIT_POS_Y = 200;


			//�u�x�X�g�X�R�A�v�̕������`�悳���X���̏ꏊ
			constexpr int BEST_SCORE_CHARA_POS_X = 280;

			//�u�x�X�g�X�R�A�v�̕������`�悳���Y���̏ꏊ
			constexpr int BEST_SCORE_CHARA_POS_Y = 280;

			//�x�X�g�X�R�A�̉E�[�̐������\�������X�̊�̏ꏊ
			constexpr int BEST_SCORE_INIT_POS_X = 760;

			//�x�X�g�X�R�A�̉E�[�̐������\�������Y�̊�̏ꏊ
			constexpr int BEST_SCORE_INIT_POS_Y = 280;

		}
	}

	//�Q�[�����̓��_�N���X
	class Score final
	{
	private:
		//���݊l�����Ă��链�_
		static inline unsigned int score_;

		//�ō����_��ۑ�����ϐ�
		static inline unsigned int bestScore_;

		//�G���h���X�̍ō����_��ۑ�����ϐ�
		static inline unsigned int endlessBestScore_;

		//�u�X�R�A�v�̕����̉摜��ۑ�����ϐ�
		static inline int scoreCharaHandle_;

		//�u�x�X�g�X�R�A�v�̕����̉摜��ۑ�����ϐ�
		static inline int bestScoreCharaHandle_;

	public:
		//�R���X�g���N�^
		Score() { score_ = 0; bestScore_ = 0; };

		//�f�X�g���N�^
		~Score() {}

		//�����������֐�
		static void Init(void);

		//�ǂݍ��ݏ����֐�
		static void Load(void);

		/// <summary>
		/// �`�揈���֐�
		/// </summary>
		/// <param name="initPosX">�ꌅ�ڂ̐�����`�悷��X��(��)�̏ꏊ</param>
		/// <param name="initPosY">�ꌅ�ڂ̐�����`�悷��Y��(�c)�̏ꏊ</param>
		/// <param name="drawInterval">�`�悷�鐔���̊Ԋu</param>
		/// <param name="drawNumScale">�`�悷�鐔���̑傫��</param>
		static void Draw(int initPosX, int initPosY, int drawInterval = SCORE::DRAW_POS_INTERVAL, float drawNumScale = 0.75f);

		//�j�������֐�
		static void Fin(void);

		//�ō��L�^�X�V����
		static void UpdateBestScore(void);

		//�ō��L�^�X�V����
		static void UpdateEndlessBestScore(void);

		/// <summary>
		/// �L�^�`��֐�
		/// </summary>
		/// <param name="initPosX">�ꌅ�ڂ̐�����`�悷��X��(��)�̏ꏊ</param>
		/// <param name="initPosY">�ꌅ�ڂ̐�����`�悷��Y��(�c)�̏ꏊ</param>
		static void DrawScore(int initPosX, int initPosY);

		//�ō��L�^�`��
		static void DrawBestScore(void);

		//�ō��L�^�`��
		static void DrawEndlessBestScore(void);

		/// <summary>
		/// �X�R�A�����Z����
		/// </summary>
		/// <param name="addScore">�ǉ�����X�R�A</param>
		static inline void AddScore(int addScore)
		{
			score_ += addScore;
		}

		/// <summary>
		/// �X�R�A�������I�ɐݒ肷��
		/// </summary>
		/// <param name="setScore">�ݒ肷��X�R�A</param>
		static inline void SetScore(int setScore)
		{
			score_ = setScore;
		}

		/// <summary>
		/// �X�R�A���擾����
		/// </summary>
		/// <returns>���݂̃X�R�A</returns>
		static inline int GetScore(void)
		{
			return score_;
		}

		static inline int GetBestScore(void) { return bestScore_; }

		static inline void SetBestScore(int setScore) { bestScore_ = setScore; }

	};
}