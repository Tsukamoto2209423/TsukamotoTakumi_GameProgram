#pragma once

#include <memory>
#include <vector>
#include "Vector/Vector3D.h"
#include "Player/Player.h"
#include <Bullet/BulletBase.h>
#include <Enemy/EnemyBase.h>
#include "Enemy/EnemyManager.h"
#include <Item/ItemBase.h>
#include <Substance/SubstanceManager.h>

namespace BOUDAMA
{
	namespace Collision
	{
		//引数の数値を中心とした正方形の当たり判定関数
		bool IsHitSquare(const Vector3D& vec1, const Vector3D& vec2, float vec1radius, float vec2radius);

		//引数の数値を中心とした円の当たり判定
		bool IsHitCircle(const Vector3D& vec1, const Vector3D& vec2, float vec1radius, float vec2radius);

		bool IsHitSphere(const Vector3D& vec1, const Vector3D& vec2, float vec1radius, float vec2radius);

		bool IsHitTriangleXY(const Vector3D& point, const Vector3D& vertexA, const Vector3D& vertexB, const Vector3D& vertexC);

		bool IsHitTriangleXZ(const Vector3D& point, const Vector3D& vertexA, const Vector3D& vertexB, const Vector3D& vertexC);

		bool IsHitTriangleYZ(const Vector3D& point, const Vector3D& vertexA, const Vector3D& vertexB, const Vector3D& vertexC);;

		//プレイヤーと敵の当たり判定
		void IsHitPlayerToEnemy(const std::shared_ptr<Player>& player, EnemyManager& enemyManager, SubstanceManager& substanceManager);

		//物質と敵の当たり判定
		void IsHitSubstanceToEnemy(const std::shared_ptr<Player>& player, EnemyManager& enemyManager, SubstanceManager& substanceManager);

		//アイテムと敵の当たり判定
		void IsHitItemToPlayer(ItemManager& itemManager, const std::shared_ptr<Player>& player);

		void IsHitItemToEnemy(ItemManager& itemManager, EnemyManager& enemyManager);

		//プレイヤーと物質の当たり判定
		void IsHitPlayerToSubstance(const std::shared_ptr<Player>& player, SubstanceManager& substanceManager);

		//物質同士の当たり判定
		void IsHitSubstanceToSubstance(const std::shared_ptr<Player>& player, SubstanceManager& substanceManager);
	};
}
