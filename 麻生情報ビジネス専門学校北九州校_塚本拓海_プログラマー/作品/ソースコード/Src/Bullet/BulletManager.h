#pragma once

#include <vector>
#include "Object/Object.h"
#include "BulletBase.h"

namespace BOUDAMA
{
	//弾情報管理用クラス
	class BulletManager
	{
	private:
		//弾のベクター
		std::vector<BulletBase*> bullets_;

	public:
		//コンストラクタ
		BulletManager();
		//デストラクタ
		~BulletManager();

		//初期化処理関数
		void Init(void);

		//読み込み処理関数
		void Load(void);

		//行動処理関数
		void Step(void);

		//描画処理関数
		void Draw(void);

		//破棄処理関数
		void Fin(void);

		//弾発射処理関数
		void RequestBullet(const Vector3D& firePos, const Vector3D& rot, int playerType, Object* player);

		//弾取得
		inline const std::vector<BulletBase*>& GetBullet() { return bullets_; }

	};
}
