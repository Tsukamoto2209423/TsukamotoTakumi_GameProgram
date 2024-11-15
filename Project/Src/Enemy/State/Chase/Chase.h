#pragma once

#include "Enemy/State/EnemyState.h"

namespace BOUDAMA
{
	//’Ç”öó‘Ô
	class Chase final : public EnemyState
	{
	private:
		//ˆÚ“®‘¬“x
		float moveSpeed_;

	public:
		explicit constexpr Chase(const auto stateName, float moveSpeed) noexcept : EnemyState(stateName), moveSpeed_(moveSpeed) {}
		~Chase() noexcept override = default;

		//‰Šú‰»ˆ—ŠÖ”
		void Enter(void) override;

		//s“®ˆ—ŠÖ”
		void Execute(void) override;
	};
}
