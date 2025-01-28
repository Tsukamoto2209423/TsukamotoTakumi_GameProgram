#include "Sound.h"
#include "DxLib.h"
#include "FileLoader/CSVFileLoader.h"

#ifdef _DEBUG

#define New new(_NORMAL_BLOCK,__FILE__,__LINE__)

#else

#define New new

#endif // !DEBUG


namespace BOUDAMA
{
	//�C���X�^���X����
	SoundManager* SoundManager::GetInstance(void)
	{
		return instance_ ? instance_ : instance_ = New SoundManager;
	}

	//�������e�ʊm��
	void SoundManager::Alloc(void)
	{
		if (!instance_)
		{
			instance_ = New SoundManager;
			instance_->Fin();
		}
	}

	//�C���X�^���X�폜�E���������
	void SoundManager::DeleteInstance(void)
	{
		if (instance_) { delete instance_; instance_ = nullptr; }
	}

	//�����������֐�
	void SoundManager::Init(void)
	{
		soundHandle_.clear();
		soundHandle_.shrink_to_fit();
	}

	//�ǂݍ��ݏ����֐�
	void SoundManager::Load(void)
	{
		//�ǂݍ��ݏ���
		CSV_LOADER::LoadSoundHandle(SOUND::PATH, soundHandle_);
	}

	//���Đ������֐�
	void SoundManager::PlaySoundData(SOUND::BGM ID, int playType)
	{
		int soundIndex = static_cast<int>(ID);

		if (soundIndex < soundHandle_.size())
		{
			//���Đ�
			PlaySoundMem(soundHandle_[soundIndex], playType, true);
		}
	}

	void SoundManager::PlaySoundData(SOUND::SE ID, int playType)
	{
		int soundIndex = static_cast<int>(ID);

		if (soundIndex < soundHandle_.size())
		{
			//���Đ�
			PlaySoundMem(soundHandle_[soundIndex], playType, true);
		}
	}

	//BGM��~�����֐�
	void SoundManager::StopSoundData(SOUND::BGM ID)
	{
		StopSoundMem(soundHandle_[static_cast<int>(ID)]);
	}

	//���ʉ���~�����֐�
	void SoundManager::StopSoundData(SOUND::SE ID)
	{
		StopSoundMem(soundHandle_[static_cast<int>(ID)]);
	}

	//�S�Ẳ��n���h��������
	void SoundManager::Reset(void)
	{
		for (auto& sound : soundHandle_)
		{
			StopSoundMem(sound);
			DeleteSoundMem(sound);

			sound = -1;
		}
	}

	//�j�������֐�
	void SoundManager::Fin(void)
	{
		if (soundHandle_.empty())
		{
			return;
		}

		//�j������
		for (auto&& sound = soundHandle_.cbegin(); sound != soundHandle_.cend();)
		{
			StopSoundMem(*sound);
			DeleteSoundMem(*sound);

			sound = soundHandle_.erase(sound);
		}

		soundHandle_.clear();
		soundHandle_.shrink_to_fit();
	}
}
