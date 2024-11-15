#pragma once

#include <memory>
#include <vector>
#include "StateBase.h"

namespace BOUDAMA
{
	//ó‘ÔŠÇ——pƒNƒ‰ƒX
	template<class StateType>
	class StateMachine final
	{
	private:
		//ó‘Ôˆê——
		std::vector<std::unique_ptr<StateType>> stateVector_;

		//Œ»İ‚Ìó‘Ô‚Ì”z—ñ‚Ì“Y‚¦š
		int currentStateIndex_;

	public:
		constexpr StateMachine(void) noexcept : currentStateIndex_(0) {};

		StateMachine(const StateMachine&) = delete;
		StateMachine& operator=(const StateMachine&) = delete;

		~StateMachine() noexcept = default;

		void Step(void)
		{
			//Œ»İ‚Ìó‘Ô‚Ìˆ—
			stateVector_[currentStateIndex_]->Execute();

			if (stateVector_[currentStateIndex_]->CanTransitionToNextState())
			{
				ChangeState();

				//‘JˆÚŒã‚Ìó‘Ô‚Ì‰Šú‰»
				stateVector_[currentStateIndex_]->Enter();

				return;
			}
		}

		//ó‘Ô‚ğV‚µ‚­ì¬‚·‚é
		template<class State, class... Args>
		void MakeState(Args&&... args)
		{
			stateVector_.emplace_back(std::make_unique<State>(args...));
		}

		//‚·‚×‚Ä‚Ìó‘Ô‚ÌŠ—LÒİ’è
		void SetAllStateOwner(const auto& owner)
		{
			for (const auto& state : stateVector_)
			{
				state->SetOwner(owner);
			}
		}

		//Å‰‚©‚çn‚ß‚éó‘Ô‚ğİ’è
		void SetStartState(const auto startStateName)
		{
			for (int index = 0; const auto& state : stateVector_)
			{
				if (state->GetMyState() == startStateName)
				{
					currentStateIndex_ = index;
					break;
				}

				++index;
			}

			stateVector_[currentStateIndex_]->Enter();
		}

		//Ÿ‚Ìó‘Ô‚É‘JˆÚ‚·‚é
		void ChangeState(void)
		{
			const auto nextState = stateVector_[currentStateIndex_]->GetNextState();

			for (int index = 0; const auto& state : stateVector_)
			{
				if (state->GetMyState() == nextState)
				{
					currentStateIndex_ = index;
					return;
				}

				++index;
			}
		}

		/// <summary>
		/// ˆø”‚Ìó‘Ô‚É‘JˆÚ‚³‚¹‚é
		/// </summary>
		/// <param name="changeStateName">
		/// ‘JˆÚæ‚Ìó‘Ô
		/// </param>
		void ChangeState(const auto changeStateName)
		{
			for (int index = 0; const auto& state : stateVector_)
			{
				if (state->GetMyState() == changeStateName)
				{
					currentStateIndex_ = index;
					return;
				}

				++index;
			}
		}

		//‚·‚×‚Ä‚Ìó‘Ô‚ğíœ‚·‚é
		void AllClear(void)
		{
			stateVector_.clear();
			stateVector_.shrink_to_fit();
		}

	};
}
