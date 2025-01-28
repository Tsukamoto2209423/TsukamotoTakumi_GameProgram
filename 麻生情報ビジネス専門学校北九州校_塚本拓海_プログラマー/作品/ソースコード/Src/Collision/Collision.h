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
		//�����̐��l�𒆐S�Ƃ��������`�̓����蔻��֐�
		bool IsHitSquare(const Vector3D& vec1, const Vector3D& vec2, float vec1radius, float vec2radius);

		//�����̐��l�𒆐S�Ƃ����~�̓����蔻��
		bool IsHitCircle(const Vector3D& vec1, const Vector3D& vec2, float vec1radius, float vec2radius);

		bool IsHitSphere(const Vector3D& vec1, const Vector3D& vec2, float vec1radius, float vec2radius);

		bool IsHitTriangleXY(const Vector3D& point, const Vector3D& vertexA, const Vector3D& vertexB, const Vector3D& vertexC);

		bool IsHitTriangleXZ(const Vector3D& point, const Vector3D& vertexA, const Vector3D& vertexB, const Vector3D& vertexC);

		bool IsHitTriangleYZ(const Vector3D& point, const Vector3D& vertexA, const Vector3D& vertexB, const Vector3D& vertexC);;

		//�v���C���[�ƓG�̓����蔻��
		void IsHitPlayerToEnemy(const std::shared_ptr<Player>& player, EnemyManager& enemyManager, SubstanceManager& substanceManager);

		//�����ƓG�̓����蔻��
		void IsHitSubstanceToEnemy(const std::shared_ptr<Player>& player, EnemyManager& enemyManager, SubstanceManager& substanceManager, ItemManager& itemManager);

		//�A�C�e���ƓG�̓����蔻��
		void IsHitItemToPlayer(ItemManager& itemManager, const std::shared_ptr<Player>& player);

		void IsHitItemToEnemy(ItemManager& itemManager, EnemyManager& enemyManager);

		//�v���C���[�ƕ����̓����蔻��
		void IsHitPlayerToSubstance(const std::shared_ptr<Player>& player, SubstanceManager& substanceManager);

		//�������m�̓����蔻��
		void IsHitSubstanceToSubstance(const std::shared_ptr<Player>& player, SubstanceManager& substanceManager);
	};
}
