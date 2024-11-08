#pragma once

#include "StateMachine/StateBase.h"
#include "Enemy/State/StateParameter.h"

namespace BOUDAMA
{
	//’Ç”öó‘Ô
	class Chase final : public StateBase<ENEMY_STATE>
	{
	public:
		constexpr Chase() = default;
		explicit constexpr Chase(const ENEMY_STATE stateName) : StateBase<ENEMY_STATE>(stateName) {}
		~Chase() noexcept override = default;

		//‰Šú‰»ˆ—ŠÖ”
		void Enter(void) override;

		//s“®ˆ—ŠÖ”
		void Execute(void) override;
	};
}
