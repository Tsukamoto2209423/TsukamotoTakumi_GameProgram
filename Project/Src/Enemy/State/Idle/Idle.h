#pragma once

#include "Enemy/State/EnemyState.h"

namespace BOUDAMA
{
	//‘Ò‹@ó‘Ô
	class Idle final : public EnemyState
	{
	public:
		explicit constexpr Idle(const auto stateName) : EnemyState(stateName) {}

		~Idle() noexcept override = default;

		//‰Šú‰»ˆ—ŠÖ”
		void Enter(void) override;

		//s“®ˆ—ŠÖ”
		void Execute(void) override;
	};
}
