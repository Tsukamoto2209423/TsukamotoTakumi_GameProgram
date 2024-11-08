#pragma once

#include <memory>
#include "StateBase.h"

namespace BOUDAMA
{
	//状態管理用クラス
	template<class T>
	class StateMachine final
	{
	private:
		using State = StateBase<T>;

		//状態一覧
		std::vector<std::unique_ptr<State>> stateVector_;

		//現在の状態の配列の添え字
		int currentStateIndex_;

	public:
		constexpr StateMachine(void) noexcept : currentStateIndex_(0) {};

		StateMachine(const StateMachine&) = delete;
		StateMachine& operator=(const StateMachine&) = delete;

		~StateMachine() noexcept = default;

		void Step(void)
		{
			//現在の状態の処理
			stateVector_[currentStateIndex_]->Execute();

			if (stateVector_[currentStateIndex_]->CanTransitionToNextState())
			{
				ChangeState();

				//遷移後の状態の初期化
				stateVector_[currentStateIndex_]->Enter();

				return;
			}
		}

		//状態を新しく作成する
		template<class Ty>
		void MakeState(const T stateName)
		{
			stateVector_.emplace_back(std::make_unique<Ty>(stateName));
		}

		//最初から始める状態を設定
		void SetStartState(const T startStateName)
		{
			for (int index = 0; const auto & state : stateVector_)
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

		//状態を変更する
		void ChangeState(void)
		{
			const auto nextState = stateVector_[currentStateIndex_]->GetNextState();

			for (int index = 0; const auto & state : stateVector_)
			{
				if (state->GetMyState() == nextState)
				{
					currentStateIndex_ = index;
					return;
				}

				++index;
			}
		}

		//すべての状態を削除する
		void AllClear(void)
		{
			stateVector_.clear();
		}

	};
}
