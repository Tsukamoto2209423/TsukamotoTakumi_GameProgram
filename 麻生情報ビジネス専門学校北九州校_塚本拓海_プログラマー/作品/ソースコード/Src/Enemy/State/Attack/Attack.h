#pragma once

#include "Enemy/State/EnemyState.h"
#include "Enemy/EnemyMonster.h"

namespace BOUDAMA
{
	//‰ö•¨ê—p‚ÌUŒ‚ó‘Ô
	class Attack final : public EnemyState<EnemyMonster>
	{
	private:
		//ˆÚ“®‘¬“x
		float moveSpeed_;

		int attackTimeCount_;

		const int maxAttackTime_;

	public:
		explicit constexpr Attack(const auto stateName, float moveSpeed, int maxAttackTime) noexcept :
			EnemyState(stateName), moveSpeed_(moveSpeed), attackTimeCount_(0), maxAttackTime_(maxAttackTime) {}

		explicit constexpr Attack(const auto myState, const auto nextState, float moveSpeed, int maxAttackTime) noexcept :
			EnemyState(myState, nextState), moveSpeed_(moveSpeed), attackTimeCount_(0), maxAttackTime_(maxAttackTime) {}

		~Attack() noexcept override = default;

		//‰Šú‰»ˆ—ŠÖ”
		void Enter(void) override;

		//s“®ˆ—ŠÖ”
		void Execute(void) override;
	};
}
