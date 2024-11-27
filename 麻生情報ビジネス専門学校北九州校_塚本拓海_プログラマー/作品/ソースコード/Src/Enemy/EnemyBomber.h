#pragma once

#include "EnemyBase.h"
#include "Item/Bomb/Bomb.h"

namespace BOUDAMA
{
	//爆弾魔クラス
	class EnemyBomber : public EnemyBase
	{
	private:
		//参照する爆弾
		std::weak_ptr<Bomb> bomb_;

		//移動する角度切り替え時間計測
		int moveAngleChangeCount_;

		//プレイヤーを発見したときの反応時間計測用変数
		int findOutReactionCount_;

		//攻撃溜め
		int attackChargeCount_;

	public:
		//コンストラクタ
		EnemyBomber();

		//デストラクタ
		~EnemyBomber();

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
