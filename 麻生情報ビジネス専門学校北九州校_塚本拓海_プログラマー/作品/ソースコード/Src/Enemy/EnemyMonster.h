#pragma once

#include "EnemyBase.h"

namespace BOUDAMA
{
	//敵クラス
	class EnemyMonster : public EnemyBase
	{
	private:
		//移動する角度切り替え時間計測用変数
		int moveAngleChangeCount_;

		//プレイヤーを発見したときの反応時間計測用変数
		int findOutReactionCount_;

		//攻撃を開始するまでの時間計測用変数
		int attackChargeCount_;

		//攻撃時間計測用変数
		int attackTimeCount_;

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
