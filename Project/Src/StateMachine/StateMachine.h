#pragma once

#include <memory>
#include <unordered_map>
#include "StateBase.h"

namespace BOUDAMA
{
	//ó‘ÔŠÇ——pƒNƒ‰ƒX
	template<class T>
	class StateMachine final
	{
	private:
		//ó‘Ôˆê——‚ÌƒŠƒXƒg
		std::unordered_map<T, const std::shared_ptr<StateBase<T>>&> stateMap_;

		//Œ»İ‚Ìó‘Ô
		std::weak_ptr<StateBase<T>> currentState_;

	public:
		StateMachine() = default;
		~StateMachine() = default;

		void Step(void)
		{
			if (!currentState_)
			{
				return;
			}

			//Œ»İ‚Ìó‘Ô‚Ìˆ—
			currentState_->Step();

			if (currentState_->CanTransitionToNextState())
			{
				ChangeState();

				if (currentState_)
				{

					//‘JˆÚŒã‚Ìó‘Ô‚Ì‰Šú‰»
					currentState_->Init();

					return;
				}
			}
		}

		//ó‘Ô‚ğV‚µ‚­“o˜^‚·‚é
		void Register(T name, const std::shared_ptr<StateBase<T>>& state)
		{
			stateMap_.insert(std::make_pair(name, state));
		}

		//Å‰‚©‚çn‚ß‚éó‘Ô‚ğİ’è
		void SetStartState(T startStateName)
		{
			const auto& it = stateMap_.find(registerName);

			if (it == stateMap_.end())
			{
				return;
			}

			currentState_ = it->second.lock();

			currentState_->Init();
		}

		//ó‘Ô‚ğ•ÏX‚·‚é
		void ChangeState(void)
		{
			const auto& it = stateMap_.find(currentState_->GetNextState());

			if (it == stateMap_.end())
			{
				return;
			}

			currentState_ = it->second.lock();
		}

		//“o˜^‚µ‚½‚à‚Ì‚ğíœ‚·‚é
		void Deregistration(T eraseStateName)
		{
			const auto& it = stateMap_.find(eraseStateName);

			if (it == stateMap_.end())
			{
				return;
			}

			stateMap_.erase(it);
		}

		//‚·‚×‚Ä‚Ì“o˜^‚ğíœ‚·‚é
		void AllDeregistration(void)
		{
			stateMap_.clear();
		}

	};
}
