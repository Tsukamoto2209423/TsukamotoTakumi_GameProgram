#include "CollisionManager.h"
#include <DxLib.h>
#include <memory>
#include <Enemy/EnemyManager.h>

//一括当たり判定
void CollisionManager::CheckHitAll(const std::shared_ptr<Player> &player,  EnemyManager& enemymanager, ItemManager& itemManager, SubstanceManager &substanceManager)
{
	Collision::IsHitSubstanceToSubstance(player,substanceManager);
	//プレイヤーと敵の当たり判定
	Collision::IsHitPlayerToEnemy(player, enemymanager,substanceManager);
	Collision::IsHitPlayerToSubstance(player, substanceManager);

	Collision::IsHitSubstanceToEnemy(player,enemymanager, substanceManager);
}