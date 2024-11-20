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
	//状態管理用クラス
	template<class StateType, class Owner>
	class StateMachine final
	{
	public:
		using State = StateBase<StateType, Owner>;

	private:
		//状態一覧
		std::vector<std::unique_ptr<State>> stateVector_;

		//現在の状態の配列の添え字
		int currentStateIndex_;

	public:
		constexpr StateMachine(void) noexcept : currentStateIndex_(-1) {}

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
		template<class StateElement, class StateNumber, class... Args>
		void AddState(const StateNumber num, Args&&... args)
		{
			#ifdef _DEBUG

			//既に追加されているなら戻る
			for (const auto& state : stateVector_)
			{
				if (state->GetMyState() == num)
				{
					std::cerr << "Debug break : 既に追加された状態を追加しています！" << std::endl;
					__debugbreak();
				}
			}
			#endif // !_DEBUG

			stateVector_.emplace_back(std::make_unique<StateElement>(num, args...));
		}

		//すべての状態の所有者設定
		void SetAllStateOwner(const auto& owner)
		{
			for (const auto& state : stateVector_)
			{
				state->SetOwner(owner);
			}
		}

		//最初から始める状態を設定
		void SetStartState(const auto startStateName)
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

		//次の状態に遷移する
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
		/// 引数の状態に遷移させる
		/// </summary>
		/// <param name="changeStateName">
		/// 遷移先の状態
		/// </param>
		void ChangeState(const auto changeStateName)
		{
			for (int index = 0; const auto & state : stateVector_)
			{
				if (state->GetMyState() == changeStateName)
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
			stateVector_.shrink_to_fit();
		}

	};
}
