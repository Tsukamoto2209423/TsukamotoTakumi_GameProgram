#pragma once

#include "StateMachine/StateBase.h"
#include "Enemy/State/StateParameter.h"

namespace BOUDAMA
{
	//‘Ò‹@ó‘Ô
	class Idle final : public StateBase<ENEMY_STATE>
	{
	public:
		Idle() = default;
		~Idle() override = default;

	private:
		//‰Šú‰»ˆ—ŠÖ”
		void Init(void) override;

		//s“®ˆ—ŠÖ”
		void Step(void) override;

		/// <summary>
		/// Ÿ‚Ìó‘Ô‚É‘JˆÚ‚Å‚«‚é‚©H
		/// </summary>
		/// <returns>
		/// true : Ÿ‚Ìó‘Ô‚É‘JˆÚ‚·‚é
		/// false : Œ»İ‚Ìó‘Ô‚ğˆÛ‚·‚é
		/// </returns>
		virtual bool CanTransitionToNextState(void) const override;
	};
}
