#pragma once

#include <memory>
#include <vector>
#include "StateBase.h"

#ifdef _DEBUG

#include <iostream>
#include <intrin.h>

#endif

namespace BOUDAMA
{
	//ó‘ÔŠÇ——pƒNƒ‰ƒX
	template<class StateType, class Owner>
	class StateMachine final
	{
	public:
		using State = StateBase<StateType, Owner>;

	private:
		//ó‘Ôˆê——
		std::vector<std::unique_ptr<State>> stateVector_;

		//Œ»İ‚Ìó‘Ô‚Ì”z—ñ‚Ì“Y‚¦š
		int currentStateIndex_;

	public:
		constexpr StateMachine(void) noexcept : currentStateIndex_(-1) {}

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
		template<class StateElement, class StateNumber, class... Args>
		void AddState(const StateNumber num, Args&&... args)
		{
#ifdef _DEBUG
			//Šù‚É’Ç‰Á‚³‚ê‚Ä‚¢‚é‚È‚ç–ß‚é
			for (const auto& state : stateVector_)
			{
				if (state->GetMyState() == num)
				{
					std::cerr << "Debug break : Šù‚É’Ç‰Á‚³‚ê‚½ó‘Ô‚ğ’Ç‰Á‚µ‚Ä‚¢‚Ü‚·I" << std::endl;
					__debugbreak();
				}
			}
#endif // !_DEBUG

			stateVector_.emplace_back(std::make_unique<StateElement>(num, args...));
		}

		//‚·‚×‚Ä‚Ìó‘Ô‚ÌŠ—LÒİ’è
		void SetAllStateOwner(const auto& owner)
		{
			for (const auto& state : stateVector_)
			{
				state->SetOwner(owner);
			}
		}

		//w’è‚Ìó‘Ô‚ÌŠ—LÒİ’è
		void SetStateOwner(const auto stateName, const auto& owner)
		{
			for (const auto& state : stateVector_)
			{
				if (state->GetMyState() == stateName)
				{
					state->SetOwner(owner);
				}
			}
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

			//‘JˆÚæ‚Ìó‘Ô‚Ì‰Šú‰»
			stateVector_[currentStateIndex_]->Enter();
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

			//‘JˆÚæ‚Ìó‘Ô‚Ì‰Šú‰»
			stateVector_[currentStateIndex_]->Enter();
		}

		//‚·‚×‚Ä‚Ìó‘Ô‚ğíœ‚·‚é
		void AllClear(void)
		{
			stateVector_.clear();
			stateVector_.shrink_to_fit();
		}

	};
}
