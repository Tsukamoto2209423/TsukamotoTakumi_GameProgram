#pragma once

#include "EnemyBase.h"
#include "EnemyParameter.h"
#include "Item/Bomb/Bomb.h"
#include "Math/MyMath.h"

namespace BOUDAMA
{
	//爆弾魔クラス
	class EnemyBomber : public EnemyBase
	{
	private:
		//参照する爆弾
		std::shared_ptr<ItemBase> bomb_;

		//爆弾を投げた時のスタン時間
		int bombThrowStunTime_;

		//漂う(float)動きを使用するときに使う角度θ
		float floatMotionTheta_;

	public:
		//コンストラクタ
		constexpr EnemyBomber() : bombThrowStunTime_(0), floatMotionTheta_(0.0f) {}

		EnemyBomber(const auto& bomb) : bomb_(bomb), bombThrowStunTime_(0), floatMotionTheta_(0.0f) {}
		
		//デストラクタ
		~EnemyBomber() override {}

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
