#include "CollisionManager.h"
#include <DxLib.h>
#include <memory>
#include <Enemy/EnemyManager.h>

namespace BOUDAMA
{
	//ˆêŠ‡“–‚½‚è”»’è
	void CollisionManager::CheckHitAll(const std::shared_ptr<Player>& player, EnemyManager& enemyManager, ItemManager& itemManager, SubstanceManager& substanceManager)
	{
		Collision::IsHitSubstanceToSubstance(player, substanceManager);
		//ƒvƒŒƒCƒ„[‚Æ“G‚Ì“–‚½‚è”»’è
		Collision::IsHitPlayerToEnemy(player, enemyManager, substanceManager);
		Collision::IsHitPlayerToSubstance(player, substanceManager);

		Collision::IsHitSubstanceToEnemy(player, enemyManager, substanceManager,itemManager);

		Collision::IsHitItemToPlayer(itemManager, player);
		Collision::IsHitItemToEnemy(itemManager, enemyManager);
	}
}
