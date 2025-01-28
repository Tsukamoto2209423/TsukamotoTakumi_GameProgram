#pragma once

#include <vector>
#include "SoundParameter.h"

namespace BOUDAMA
{
	//���N���X
	class SoundManager final
	{
	private:
		//�C���X�^���X�����p
		static inline SoundManager* instance_;

		//���n���h��
		std::vector<int> soundHandle_;

		//�R���X�g���N�^
		SoundManager() {}
		//�f�X�g���N�^
		~SoundManager() {}

		//�R�s�[�R���X�g���N�^
		SoundManager(const SoundManager&) = delete;
		//������Z�q��`
		SoundManager& operator=(const SoundManager&) = delete;

	public:
		//�C���X�^���X����
		static SoundManager* GetInstance(void);

		//�������e�ʊm��
		static void Alloc(void);

		//�C���X�^���X�폜�E���
		static void DeleteInstance(void);

	public:

		//�����������֐�
		void Init(void);

		//�ǂݍ��ݏ����֐�
		void Load(void);

		//BGM�Đ������֐�
		void PlaySoundData(SOUND::BGM ID, int playType);

		//���ʉ��Đ������֐�
		void PlaySoundData(SOUND::SE ID, int playType);

		//BGM��~�����֐�
		void StopSoundData(SOUND::BGM ID);
		//���ʉ���~�����֐�
		void StopSoundData(SOUND::SE ID);

		//�S�Ẳ��n���h��������
		void Reset(void);

		//�j�������֐�
		void Fin(void);

	};
}
