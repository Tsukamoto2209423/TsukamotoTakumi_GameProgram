#pragma once

#include "EnemyBase.h"

namespace BOUDAMA
{
	//敵クラス
	class EnemyMonster : public EnemyBase
	{
	private:

	public:
		//コンストラクタ
		EnemyMonster();

		//デストラクタ
		~EnemyMonster() override;

		//初期化処理関数
		void Init(void) override;

		//行動処理関数
		void Step(const Vector3D& playerPos) override;

		//描画処理関数
		void Draw(void) override;

		//出現処理関数
		void AppearanceRequest(void) override;
	};
}
