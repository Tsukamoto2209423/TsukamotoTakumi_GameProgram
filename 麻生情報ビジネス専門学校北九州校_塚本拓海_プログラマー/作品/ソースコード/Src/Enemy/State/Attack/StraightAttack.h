#pragma once

#include "Enemy/State/EnemyState.h"
#include "Enemy/EnemyBase.h"


namespace BOUDAMA
{
	//直線上に攻撃する状態
	class StraightAttack final : public EnemyState<EnemyBase>
	{
	private:
		//移動速度
		float moveSpeed_;

		//攻撃時間を計測する変数
		int attackTimeCount_;

		//攻撃時間を継続できる最大時間
		const int maxAttackTime_;

	public:
		explicit constexpr StraightAttack(const auto stateName, float moveSpeed, int maxAttackTime) noexcept :
			EnemyState(stateName), moveSpeed_(moveSpeed), attackTimeCount_(0), maxAttackTime_(maxAttackTime) {}

		explicit constexpr StraightAttack(const auto myState, const auto nextState, float moveSpeed, int maxAttackTime) noexcept :
			EnemyState(myState, nextState), moveSpeed_(moveSpeed), attackTimeCount_(0), maxAttackTime_(maxAttackTime) {}

		~StraightAttack() noexcept override = default;

		//初期化処理関数
		void Enter(void) override;

		//行動処理関数
		void Execute(void) override;
	};
}
