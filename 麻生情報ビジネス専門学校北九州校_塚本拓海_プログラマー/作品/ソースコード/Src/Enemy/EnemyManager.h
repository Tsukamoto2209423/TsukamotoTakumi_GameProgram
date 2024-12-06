#pragma once

#include <vector>
#include <memory>
#include "EnemyParameter.h"
#include "EnemyBase.h"
#include <Item/ItemManager.h>
#include <Scene/Scene.h>

namespace BOUDAMA
{
	//敵情報管理クラス
	class EnemyManager
	{
	private:
		//敵の配列
		std::vector<std::shared_ptr<EnemyBase>> enemies_;

		//敵の最大数
		std::vector<int> enemiesMaxNum_;

		//敵出現時間計測
		int appearCountTime_[static_cast<int>(ENEMY_MANAGER::ENEMY_LIST::ALL_NUM)];

		//死亡数
		int deathCount_;

		//フィーバータイム計測
		int feverTimeCount_;

		//敵が次々と出現する「フィーバータイム」かどうか
		bool isFeverTime_;

	public:
		//コンストラクタ
		EnemyManager();

		//デストラクタ
		~EnemyManager();

		//初期化処理関数
		void Init(const SCENE difficulty, const ItemManager& itemManager);

		//読み込み処理関数
		void Load(const SCENE difficulty);

		//行動処理関数
		void Step(const Vector3D& playerPos);

		//描画処理関数
		void Draw(void);

		//破棄処理関数
		void Fin(void);

		//敵情報取得
		inline const std::vector<std::shared_ptr<EnemyBase>>& GetEnemy(void) { return enemies_; }

		inline int GetEnemyDeathCount(void) const { return deathCount_; }

		inline void AddEnemyDeathCount(void) { ++deathCount_; }

	private:
		template<class EnemyType, class... Args>
		void CreateEnemy(Args... args)
		{
			enemies_.emplace_back(std::make_shared<EnemyType>(args...));
		}

		//出現処理時間計測関数
		void AppearanceCountProcess(void);

		//敵を実際にゲーム内に出現させる関数
		void AppearanceRequest(int kindNum = 0, int enemyArrayIndex = 0);
	};
}
