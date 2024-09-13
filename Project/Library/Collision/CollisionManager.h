#pragma once

#include "Collision.h"
#include <vector>
#include "Object/Object.h"
#include "Player/Player.h"
#include "Enemy/Enemy.h"
#include "Item/ItemManager.h"
#include "Sound/Sound.h"

//当たり判定管理クラス
class CollisionManager
{
public:
	//一括当たり判定
	static void CheckHitAll(const std::shared_ptr<Player>& player, EnemyManager& enemymanager, ItemManager& itemManager, SubstanceManager& substanceManager);
};
