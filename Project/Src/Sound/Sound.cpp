#include "Sound.h"
#include "DxLib.h"
#include "FileLoader/CSVFileLoader.h"

#ifdef _DEBUG

#define New new(_NORMAL_BLOCK,__FILE__,__LINE__)

#else

#define New new

#endif // !DEBUG


//インスタンス生成
SoundManager* SoundManager::GetInstance(void)
{
	return instance_ ? instance_ : instance_ = New SoundManager;
}

//メモリ容量確保
void SoundManager::Alloc(void)
{
	if (!instance_)
	{
		instance_ = New SoundManager;
		instance_->Fin();
	}
}

//インスタンス削除・メモリ解放
void SoundManager::DeleteInstance(void)
{
	if (instance_) { delete instance_; instance_ = nullptr; }
}

//初期化処理関数
void SoundManager::Init(void)
{
	soundHandle_.clear();
	soundHandle_.shrink_to_fit();
}

//読み込み処理関数
void SoundManager::Load(void)
{
	//読み込み処理
	CSV_LOADER::LoadSoundHandle(SOUND::PATH, soundHandle_);
}

//音再生処理関数
void SoundManager::PlaySoundData(SOUND::BGM ID,int playType)
{
	int soundIndex = static_cast<int>(ID);

	if (soundIndex < soundHandle_.size())
	{
		//音再生
		PlaySoundMem(soundHandle_[soundIndex], playType, true);
	}
}

//BGM停止処理関数
void SoundManager::StopSoundData(SOUND::BGM ID)
{
	StopSoundMem(soundHandle_[static_cast<int>(ID)]);
}

void SoundManager::PlaySoundData(SOUND::SE ID, int playType)
{
	int soundIndex = static_cast<int>(ID);

	if (soundIndex < soundHandle_.size())
	{
		//音再生
		PlaySoundMem(soundHandle_[soundIndex], playType, true);
	}
}

//全ての音ハンドル初期化
void SoundManager::Reset(void)
{
	for (auto& sound : soundHandle_)
	{
		StopSoundMem(sound);
		DeleteSoundMem(sound);

		sound = -1;
	}
}

//破棄処理関数
void SoundManager::Fin(void)
{
	if (soundHandle_.empty())
	{
		return;
	}

	//破棄処理
	for (auto&& sound = soundHandle_.cbegin(); sound != soundHandle_.cend();)
	{
		StopSoundMem(*sound);
		DeleteSoundMem(*sound);

		sound = soundHandle_.erase(sound);
	}

	soundHandle_.clear();
	soundHandle_.shrink_to_fit();
}