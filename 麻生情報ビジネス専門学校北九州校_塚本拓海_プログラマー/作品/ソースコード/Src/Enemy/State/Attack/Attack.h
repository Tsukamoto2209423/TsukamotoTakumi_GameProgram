#pragma once

#include "Enemy/State/EnemyState.h"
#include "Enemy/EnemyMonster.h"

namespace BOUDAMA
{
	//怪物専用の攻撃状態
	class Attack final : public EnemyState<EnemyMonster>
	{
	private:
		//移動速度
		float moveSpeed_;

		int attackTimeCount_;

		const int maxAttackTime_;

	public:
		explicit constexpr Attack(const auto stateName, float moveSpeed, int maxAttackTime) noexcept :
			EnemyState(stateName), moveSpeed_(moveSpeed), attackTimeCount_(0), maxAttackTime_(maxAttackTime) {}

		explicit constexpr Attack(const auto myState, const auto nextState, float moveSpeed, int maxAttackTime) noexcept :
			EnemyState(myState, nextState), moveSpeed_(moveSpeed), attackTimeCount_(0), maxAttackTime_(maxAttackTime) {}

		~Attack() noexcept override = default;

		//初期化処理関数
		void Enter(void) override;

		//行動処理関数
		void Execute(void) override;
	};
}
