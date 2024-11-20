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
	class Collision final
	{
	public:
		//引数の数値を中心とした正方形の当たり判定関数
		static bool IsHitSquare(const Vector3D& vec1, const Vector3D& vec2, float vec1radius, float vec2radius);

		//引数の数値を中心とした円の当たり判定
		static bool IsHitCircle(const Vector3D& vec1, const Vector3D& vec2, float vec1radius, float vec2radius);

		static bool IsHitSphere(const Vector3D& vec1, const Vector3D& vec2, float vec1radius, float vec2radius);

		static bool IsHitTriangleXY(const Vector3D& point, const Vector3D& vertexA, const Vector3D& vertexB, const Vector3D& vertexC);

		static bool IsHitTriangleXZ(const Vector3D& point, const Vector3D& vertexA, const Vector3D& vertexB, const Vector3D& vertexC);

		static bool IsHitTriangleYZ(const Vector3D& point, const Vector3D& vertexA, const Vector3D& vertexB, const Vector3D& vertexC);;

		//弾とプレイヤーの当たり判定
		static void IsHitBulletToPlayer(std::vector<BulletBase*>& bullet, std::shared_ptr<Player>& player);

		//弾と敵の当たり判定
		static void IsHitBulletToEnemy(std::vector<BulletBase*>& bullet, std::vector<EnemyBase*>& enemy, EnemyManager& enemymanager);

		//プレイヤーと敵の当たり判定
		static void IsHitPlayerToEnemy(const std::shared_ptr<Player>& player, EnemyManager& enemyManager, SubstanceManager& substanceManager);

		//物質と敵の当たり判定
		static void IsHitSubstanceToEnemy(const std::shared_ptr<Player>& player, EnemyManager& enemyManager, SubstanceManager& substanceManager);

		//アイテムと敵の当たり判定
		static void IsHitItemToPlayer(std::vector<ItemBase*>& item, std::vector<Player*>& player);

		//プレイヤーと物質の当たり判定
		static void IsHitPlayerToSubstance(const std::shared_ptr<Player>& player, SubstanceManager& substanceManager);

		//物質同士の当たり判定
		static void IsHitSubstanceToSubstance(const std::shared_ptr<Player>& player, SubstanceManager& substanceManager);
	};
}
