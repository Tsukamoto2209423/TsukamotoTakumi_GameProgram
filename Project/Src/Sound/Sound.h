#pragma once

#include <vector>
#include "SoundParameter.h"

namespace BOUDAMA
{
	//音クラス
	class SoundManager final
	{
	private:
		//インスタンス生成用
		static inline SoundManager* instance_;

		//音ハンドル
		std::vector<int> soundHandle_;

		//コンストラクタ
		SoundManager() {}
		//デストラクタ
		~SoundManager() {}

		//コピーコンストラクタ
		SoundManager(const SoundManager& other) = delete;
		//代入演算子定義
		SoundManager& operator=(const SoundManager& other) = delete;

	public:
		//インスタンス生成
		static SoundManager* GetInstance(void);

		//メモリ容量確保
		static void Alloc(void);

		//インスタンス削除・解放
		static void DeleteInstance(void);

	public:

		//初期化処理関数
		void Init(void);

		//読み込み処理関数
		void Load(void);

		//BGM再生処理関数
		void PlaySoundData(SOUND::BGM ID, int playType);

		//効果音再生処理関数
		void PlaySoundData(SOUND::SE ID, int playType);

		//BGM停止処理関数
		void StopSoundData(SOUND::BGM ID);

		//全ての音ハンドル初期化
		void Reset(void);

		//破棄処理関数
		void Fin(void);

	};
}
