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
	//�����蔻��Ǘ��N���X
	class CollisionManager final
	{
	public:
		//�ꊇ�����蔻��
		static void CheckHitAll(const std::shared_ptr<Player>& player, EnemyManager& enemyManager, ItemManager& itemManager, SubstanceManager& substanceManager);
	};
}
