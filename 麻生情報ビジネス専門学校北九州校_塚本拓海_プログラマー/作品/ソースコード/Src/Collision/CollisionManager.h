#pragma once

#include "Collision.h"
#include <vector>
#include "Object/Object.h"
#include "Player/Player.h"
#include "Enemy/Enemy.h"
#include "Item/ItemManager.h"
#include "Sound/Sound.h"

namespace BOUDAMA
{
	//“–‚½‚è”»’èŠÇ—ƒNƒ‰ƒX
	class CollisionManager final
	{
	public:
		//ˆêŠ‡“–‚½‚è”»’è
		static void CheckHitAll(const std::shared_ptr<Player>& player, EnemyManager& enemymanager, ItemManager& itemManager, SubstanceManager& substanceManager);
	};
}
