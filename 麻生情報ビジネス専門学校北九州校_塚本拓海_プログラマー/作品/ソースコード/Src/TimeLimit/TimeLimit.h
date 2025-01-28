#pragma once

#include <chrono>

//�V�X�e���N���b�N�g�p�ȗ���
using std::chrono::system_clock;

namespace BOUDAMA
{
	//�������ԃN���X
	class TimeLimit final
	{
	private:
		//�������Ԍv���p(�~���b)
		int count_;

		//�u�̂���v�̉摜�`��p�n���h��
		int characterHandle_;

		//�u���v�̉摜�n���h��
		int infinityHandle_;

		// �v���J�n����
		system_clock::time_point start_;

		// �v���I������
		system_clock::time_point end_;

		//�G���h���X��
		bool isEndless_;

	public:
		//�R���X�g���N�^
		TimeLimit();

		//�f�X�g���N�^
		~TimeLimit();

		//�����������֐�
		void Init(void);

		//�ǂݍ��ݏ����֐�
		void Load(void);

		//�s�������֐�
		void Step(void);

		//�`�揈���֐�
		void Draw(void);

		//�j�������֐�
		void Fin(void);

		//�������Ԍv���p�̕ϐ��擾
		inline int GetTimeLimitCount(void) const { return count_; }

		//�������Ԍv���p�̕ϐ��ݒ�
		inline void SetTimeLimitCount(int time) { characterHandle_ = time; }

		//�u�̂���v�̉摜�`��p�n���h���擾
		inline int GetTimeLimitCharacter(void) const { return characterHandle_; }

		//�u�̂���v�̉摜�`��p�n���h���ݒ�
		inline void SetTimeLimitCharacter(int handle) { characterHandle_ = handle; }

		//�G���h���X���[�h��
		inline void IsEndless(bool isEndless) { isEndless_ = isEndless; }
	};
}
