#include "CollisionManager.h"
#include <DxLib.h>
#include <memory>
#include <Enemy/EnemyManager.h>

namespace BOUDAMA
{
	//一括当たり判定
	void CollisionManager::CheckHitAll(const std::shared_ptr<Player>& player, EnemyManager& enemyManager, ItemManager& itemManager, SubstanceManager& substanceManager)
	{
		Collision::IsHitSubstanceToSubstance(player, substanceManager);
		//プレイヤーと敵の当たり判定
		Collision::IsHitPlayerToEnemy(player, enemyManager, substanceManager);
		Collision::IsHitPlayerToSubstance(player, substanceManager);

		Collision::IsHitSubstanceToEnemy(player, enemyManager, substanceManager,itemManager);

		Collision::IsHitItemToPlayer(itemManager, player);
		Collision::IsHitItemToEnemy(itemManager, enemyManager);
	}
}
