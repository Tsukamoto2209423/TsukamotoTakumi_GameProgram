#include "BulletManager.h"
#include "Bullet.h"
#include "BigBullet.h"
#include "Common/Common.h"
#include <Matrix/Matrix3D.h>
#include <Math/MyMath.h>
#include <Player/PlayerParameter.h>

#define New new(_NORMAL_BLOCK,__FILE__,__LINE__)

//コンストラクタ
BulletManager::BulletManager(void)
{
	//初期化
}

//デストラクタ
BulletManager::~BulletManager(void)
{
	//破棄処理
}

//初期化処理関数
void BulletManager::Init(void)
{
	//データ消去
	bullets_.clear();
	//m_enemyBullet.clear();

	//記憶領域確保
	// sizeof(Bullet) × BULLET_MAX_NUM
	for (int bulletIndex = 0; bulletIndex < BULLET::MAX_NUM; ++bulletIndex)
	{
		bullets_.emplace_back(New Bullet);
	}

	//記憶領域確保
	// sizeof(BigBullet) × BULLET_MAX_NUM
	for (int bulletIndex = 0; bulletIndex < BULLET::MAX_NUM; ++bulletIndex)
	{
		bullets_.emplace_back(New BigBullet);
	}

}

//読み込み処理関数
void BulletManager::Load(void)
{
	int origineBulletHandle[] = { MV1LoadModel(BULLET::PATH),MV1LoadModel(BIG_BULLET::PATH) };

	//読み込み処理
	for (auto bullet : bullets_)
	{
		bullet->Load(origineBulletHandle[bullet->GetType()]);
	}

}

//行動処理関数
void BulletManager::Step(void)
{
	//弾移動処理
	for (auto bullet : bullets_)
	{
		//移動中の弾だった場合
		if (bullet->GetIsActive())
		{
			//行動処理
			bullet->Step();
		}
	}
}

//描画処理関数
void BulletManager::Draw(void)
{
	//描画
	for (auto bullet : bullets_)
	{
		bullet->Draw();
	}

}

//破棄処理関数
void BulletManager::Fin(void)
{
	//破棄処理

	//指しているのは弾の実体
	for (auto bullet = bullets_.begin();bullet!=bullets_.end();)
	{
		(*bullet)->Fin();
	
		delete *bullet;
		bullet = bullets_.erase(bullet);
	}

	//消去
	bullets_.clear();

	//確保した記憶領域を再構築
	bullets_.shrink_to_fit();
}

//弾発射処理関数
void BulletManager::RequestBullet(const Vector3D& firePos, const Vector3D& rot,int playerState,Object* player)
{
	//弾発生処理
	for (auto&& bullet : bullets_)
	{
		//未使用の弾 且つ 属性が同じだった場合
		if (!bullet->GetIsActive())
		{
			bullet->SetOwner(player);

			//プレイヤーから見て100.0f前方に位置設定
			bullet->SetPos(Matrix3D::GetTranslateMatrix(firePos.x, 150.0f, firePos.z) *
				Matrix3D::GetYawMatrix(rot.y) * Matrix3D::GetTranslateMatrix(0.0f, 0.0f, -(20.0f + bullet->GetRadius()) ) * MY_MATH::ZERO_VECTOR_3D);

			//発射方向設定
			bullet->SetRot(rot);

			//死者蘇生
			bullet->SetIsActive(true);

			//脱出
			break;
		}
	}
}
