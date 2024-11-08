#pragma once

#include "StateMachine/StateBase.h"
#include "Enemy/State/StateParameter.h"

namespace BOUDAMA
{
	//‘Ò‹@ó‘Ô
	class Idle final : public StateBase<ENEMY_STATE>
	{
	public:
		constexpr Idle() = default;
		explicit constexpr Idle(const ENEMY_STATE stateName) : StateBase<ENEMY_STATE>(stateName) {}
		~Idle() noexcept override = default;

		//‰Šú‰»ˆ—ŠÖ”
		void Enter(void) override;

		//s“®ˆ—ŠÖ”
		void Execute(void) override;
	};
}
