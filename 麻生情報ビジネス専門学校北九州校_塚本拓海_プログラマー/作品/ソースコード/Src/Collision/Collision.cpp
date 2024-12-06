#include "Collision.h"
#include <Enemy/EnemyManager.h>
#include <Player/PlayerParameter.h>
#include <Effekseer/Effekseer.h>
#include <Score/Score.h>
#include <Sound/Sound.h>

namespace BOUDAMA
{
	//引数の数値を中心とした正方形の当たり判定関数
	bool Collision::IsHitSquare(const Vector3D& vec1, const Vector3D& vec2, float vec1radius, float vec2radius)
	{
		//正方形の当たり判定関数
		return vec2.x - vec2radius < vec1.x + vec1radius &&
			vec2.x + vec2radius > vec1.x - vec1radius &&
			vec2.y + vec2radius > vec1.y - vec1radius &&
			vec2.y - vec2radius < vec1.y + vec1radius;
	}

	//引数の数値を中心とした円の当たり判定
	bool Collision::IsHitCircle(const Vector3D& vec1, const Vector3D& vec2, float vec1radius, float vec2radius)
	{
		//円の当たり判定
		return (vec1radius + vec2radius) * (vec1radius + vec2radius) >
			(vec1.x - vec2.x) * (vec1.x - vec2.x) + (vec1.y - vec2.y) * (vec1.y - vec2.y);
	}

	bool Collision::IsHitSphere(const Vector3D& vec1, const Vector3D& vec2, float vec1radius, float vec2radius)
	{
		// 2点間を引き算する
		Vector3D dist = vec1 - vec2;
		// 2点間の距離の2乗を計算する
		float length = (dist.x * dist.x) + (dist.y * dist.y)
			+ (dist.z * dist.z);
		// 二つの球の半径を足して2乗する
		float radius = (vec1radius + vec2radius) * (vec1radius + vec2radius);

		// 最終的な当たり判定
		return length < radius;
	}


	bool Collision::IsHitTriangleXY(const Vector3D& point, const Vector3D& vertexA, const Vector3D& vertexB, const Vector3D& vertexC)
	{
		// 三角形の辺に沿ったベクトル
		Vector3D vecAB = vertexB - vertexA; vecAB.z = 0.0f;
		Vector3D vecBC = vertexC - vertexB; vecBC.z = 0.0f;
		Vector3D vecCA = vertexA - vertexC; vecCA.z = 0.0f;

		// 各頂点から対象までのベクトル
		Vector3D vecAP = point - vertexA; vecAP.z = 0.0f;
		Vector3D vecBP = point - vertexB; vecBP.z = 0.0f;
		Vector3D vecCP = point - vertexC; vecCP.z = 0.0f;

		// 対応するベクトルどうして外積を計算する
		Vector3D vecABAP = Vector3D::Cross(vecAB, vecAP);
		Vector3D vecBCBP = Vector3D::Cross(vecBC, vecBP);
		Vector3D vecCACP = Vector3D::Cross(vecCA, vecCP);

		// 各外積のZ成分が0以下であれば当たっている
		if (vecABAP.z >= 0 && vecBCBP.z >= 0 && vecCACP.z >= 0)
		{
			return true;
		}

		if (vecABAP.z <= 0 && vecBCBP.z <= 0 && vecCACP.z <= 0)
		{
			return true;
		}

		return false;
	}

	bool Collision::IsHitTriangleXZ(const Vector3D& point, const Vector3D& vertexA, const Vector3D& vertexB, const Vector3D& vertexC)
	{
		// 三角形の辺に沿ったベクトル
		Vector3D vecAB = vertexB - vertexA; vecAB.y = 0.0f;
		Vector3D vecBC = vertexC - vertexB; vecBC.y = 0.0f;
		Vector3D vecCA = vertexA - vertexC; vecCA.y = 0.0f;

		// 各頂点から対象までのベクトル
		Vector3D vecAP = point - vertexA; vecAP.y = 0.0f;
		Vector3D vecBP = point - vertexB; vecBP.y = 0.0f;
		Vector3D vecCP = point - vertexC; vecCP.y = 0.0f;

		// 対応するベクトルどうして外積を計算する
		Vector3D vecABAP = Vector3D::Cross(vecAB, vecAP);
		Vector3D vecBCBP = Vector3D::Cross(vecBC, vecBP);
		Vector3D vecCACP = Vector3D::Cross(vecCA, vecCP);

		// 各外積のY成分が0以下であれば当たっている
		if (vecABAP.y >= 0 && vecBCBP.y >= 0 && vecCACP.y >= 0)
		{
			return true;
		}

		if (vecABAP.y <= 0 && vecBCBP.y <= 0 && vecCACP.y <= 0)
		{
			return true;
		}


		return false;
	}

	bool Collision::IsHitTriangleYZ(const Vector3D& point, const Vector3D& vertexA, const Vector3D& vertexB, const Vector3D& vertexC)
	{
		// 三角形の辺に沿ったベクトル
		Vector3D vecAB = vertexB - vertexA; vecAB.x = 0.0f;
		Vector3D vecBC = vertexC - vertexB; vecBC.x = 0.0f;
		Vector3D vecCA = vertexA - vertexC; vecCA.x = 0.0f;

		// 各頂点から対象までのベクトル
		Vector3D vecAP = point - vertexA; vecAP.x = 0.0f;
		Vector3D vecBP = point - vertexB; vecBP.x = 0.0f;
		Vector3D vecCP = point - vertexC; vecCP.x = 0.0f;

		// 対応するベクトルどうして外積を計算する
		Vector3D vecABAP = Vector3D::Cross(vecAB, vecAP);
		Vector3D vecBCBP = Vector3D::Cross(vecBC, vecBP);
		Vector3D vecCACP = Vector3D::Cross(vecCA, vecCP);

		// 各外積のX成分が0以下であれば当たっている
		if (vecABAP.x >= 0 && vecBCBP.x >= 0 && vecCACP.x >= 0)
		{
			return true;
		}

		if (vecABAP.x <= 0 && vecBCBP.x <= 0 && vecCACP.x <= 0)
		{
			return true;
		}

		return false;
	}

	//プレイヤーと敵の当たり判定
	void Collision::IsHitPlayerToEnemy(const std::shared_ptr<Player>& player, EnemyManager& enemyManager, SubstanceManager& substanceManager)
	{
		if (!player->GetIsActive())
		{
			return;
		}

		for (const auto& enemy : enemyManager.GetEnemy())
		{
			//生存していないなら実行しない
			if (!enemy->GetIsActive())
			{
				continue;
			}

			//無効状態なら次へ
			if (!enemy->IsCollisionEnabled())
			{
				continue;
			}

			if (Collision::IsHitSphere(player->GetPos(), enemy->GetPos(), player->GetRadius(), enemy->GetRadius()))
			{
				//接触した敵が攻撃状態ならプレイヤーを吹き飛ばす
				if (enemy->IsInvincible())
				{
					player->HitCalculation();

					player->AddVelocity(0.625f * enemy->GetVelocity());

					enemy->HitCalculation();

					continue;
				}

				if (player->GetVelocity().SquareL2Norm() < PLAYER::KILL_SPEED || !player->IsInvincible())
				{
					player->HitCalculation();
					enemy->HitCalculation();

					continue;
				}

				SoundManager::GetInstance()->PlaySoundData(SOUND::SE::ENEMY_DEATH, DX_PLAYTYPE_BACK);

				player->AddComboNum();
				Score::AddScore(enemy->GetScoreNum());

				enemy->DeathCalculation(player->GetVelocity());

				substanceManager.FlyAppearCalculation(enemy->GetPos());
			}
		}

	}

	void Collision::IsHitItemToPlayer(ItemManager& itemManager, const std::shared_ptr<Player>& player)
	{
		for (const auto& item : itemManager.GetItem())
		{
			if (!item->GetIsActive())
			{
				continue;
			}

			if (!player->GetIsActive())
			{
				continue;
			}

			if (Collision::IsHitSphere(item->GetPos(), player->GetPos(), item->GetRadius(), player->GetRadius()))
			{
				item->HitCalculation();
				item->EffectExecute(player);
			}
		}
	}

	void Collision::IsHitItemToEnemy(ItemManager& itemManager, EnemyManager& enemyManager)
	{
		for (const auto& item : itemManager.GetItem())
		{
			if (!item->GetIsActive())
			{
				continue;
			}

			for (const auto& enemy : enemyManager.GetEnemy())
			{
				if (!enemy->GetIsActive())
				{
					continue;
				}

				if (Collision::IsHitSphere(item->GetPos(), enemy->GetPos(), item->GetRadius(), enemy->GetRadius()))
				{
					item->HitCalculation();
					item->EffectExecute(enemy);
				}
			}
		}
	}

	void Collision::IsHitPlayerToSubstance(const std::shared_ptr<Player>& player, SubstanceManager& substanceManager)
	{
		for (const auto& substance : substanceManager.GetSubstance())
		{
			//くっついていたら実行しない
			if (!substance->IsOwnerExpired())
			{
				continue;
			}

			if (!substance->GetIsActive())
			{
				continue;
			}


			if (Collision::IsHitSphere(substance->GetPos(), player->GetPos(), substance->GetRadius(), player->GetRadius()))
			{
				substance->AttachToObject(player);

				player->AddAttachedSubstance(substance);

				Score::AddScore(substance->GetAddScoreNum());

				continue;
			}


			if (Collision::IsHitSphere(substance->GetPos(), player->GetPos(), 2.5f * substance->GetRadius(), player->GetRadius()))
			{
				substance->ChasePosCalculation(player->GetPos());

				continue;
			}
		}
	}

	void Collision::IsHitSubstanceToEnemy(const std::shared_ptr<Player>& player, EnemyManager& enemyManager, SubstanceManager& substanceManager)
	{
		for (const auto& substance : substanceManager.GetSubstance())
		{
			//くっついていないなら処理しない
			if (substance->IsOwnerExpired())
			{
				continue;
			}

			//生存していないなら実行しない
			if (!substance->GetIsActive())
			{
				continue;
			}

			for (const auto& enemy : enemyManager.GetEnemy())
			{
				if (!enemy->GetIsActive())
				{
					continue;
				}

				//無効状態なら当たり判定の処理しない
				if (!enemy->IsCollisionEnabled())
				{
					continue;
				}

				if (!Collision::IsHitSphere(substance->GetPos(), enemy->GetPos(), substance->GetRadius(), enemy->GetRadius()))
				{
					continue;
				}

				//敵が無敵状態なら
				if (enemy->IsInvincible())
				{
					player->HitCalculation();

					player->SubVelocity(enemy->GetVelocity());

					enemy->HitCalculation();

					continue;
				}

				//プレイヤーが無敵状態ではない場合
				if (substance->IsOwnerNotInvincible())
				{
					player->HitCalculation();
					enemy->HitCalculation();

					continue;
				}

				SoundManager::GetInstance()->PlaySoundData(SOUND::SE::ENEMY_DEATH, DX_PLAYTYPE_BACK);

				player->AddComboNum();
				Score::AddScore(enemy->GetScoreNum());

				enemy->DeathCalculation(substance->GetOwner()->GetVelocity());

				substanceManager.RandomFlyAppearCalculation(enemy->GetPos());

				return;

			}
		}
	}

	void Collision::IsHitSubstanceToSubstance(const std::shared_ptr<Player>& player, SubstanceManager& substanceManager)
	{
		for (const auto& playerSubstance : player->GetAttachedSubstance())
		{
			if (const auto& substance = playerSubstance.lock())
			{
				for (const auto& hitSubstance : substanceManager.GetSubstance())
				{
					//同じものを比較しようとしている場合は次に行く
					if (substance == hitSubstance)
					{
						continue;
					}

					//くっついていたら飛ばす
					if (!hitSubstance->IsOwnerExpired())
					{
						continue;
					}

					if (!hitSubstance->GetIsActive())
					{
						continue;
					}

					if (Collision::IsHitSphere(substance->GetPos(), hitSubstance->GetPos(), substance->GetRadius(), hitSubstance->GetRadius()))
					{
						//位置が重ならないようにする
						Vector3D substanceToSubstanceVector = hitSubstance->GetPos() - substance->GetPos();
						hitSubstance->SetPos(substance->GetPos() + substanceToSubstanceVector.Normalize() * (substance->GetRadius() + hitSubstance->GetRadius()));

						//くっついていたら
						if (substance->IsOwnerExpired())
						{
							hitSubstance->AttachToObject(substance);
						}
						else
						{
							hitSubstance->AttachToObject(substance->GetOwner());
						}

						Score::AddScore(100);
					}


					if (Collision::IsHitSphere(substance->GetPos(), hitSubstance->GetPos(), 2.5f * substance->GetRadius(), hitSubstance->GetRadius()))
					{
						substance->ChasePosCalculation(hitSubstance->GetPos());

						continue;
					}

				}
			}
		}
	}
}
