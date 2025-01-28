#pragma once

#include "Enemy/State/EnemyState.h"
#include "Enemy/EnemyBase.h"

namespace BOUDAMA
{
	//’Ç”öó‘Ô
	class Chase final : public EnemyState<EnemyBase>
	{
	private:
		//ˆÚ“®‘¬“x
		float moveSpeed_;

	public:
		explicit constexpr Chase(const auto stateName, float moveSpeed) noexcept : EnemyState(stateName), moveSpeed_(moveSpeed) {}
		explicit constexpr Chase(const auto myState, const auto nextState, float moveSpeed) noexcept : EnemyState(myState, nextState), moveSpeed_(moveSpeed) {}

		~Chase() noexcept override = default;

		//‰Šú‰»ˆ—ŠÖ”
		void Enter(void) override;

		//s“®ˆ—ŠÖ”
		void Execute(void) override;
	};
}
