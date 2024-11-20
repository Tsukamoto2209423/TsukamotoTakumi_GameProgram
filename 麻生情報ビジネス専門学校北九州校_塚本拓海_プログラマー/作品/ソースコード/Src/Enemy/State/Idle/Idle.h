#pragma once

#include "Enemy/State/EnemyState.h"
#include "Enemy/EnemyBase.h"

namespace BOUDAMA
{
	//‘Ò‹@ó‘Ô
	class Idle final : public EnemyState<EnemyBase>
	{
	public:
		explicit constexpr Idle(const auto stateName) : EnemyState(stateName) {}
		explicit constexpr Idle(const auto myState, const auto nextState) : EnemyState(myState, nextState) {}

		~Idle() noexcept override = default;

		//‰Šú‰»ˆ—ŠÖ”
		void Enter(void) override;

		//s“®ˆ—ŠÖ”
		void Execute(void) override;
	};
}
