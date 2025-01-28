#pragma once

#include <memory>

namespace BOUDAMA
{
	//固有の状態に継承させる抽象クラス
	template<class Ty, class Owner>
	class StateBase
	{
	public:
		using KeyType = Ty;
		using OwnerType = Owner;

		explicit constexpr StateBase(const KeyType initState) noexcept : myStateName_(initState), nextStateName_(initState), isTransitionToNextState_(false) {};
		explicit constexpr StateBase(const KeyType myState, const KeyType nextState) noexcept : myStateName_(myState), nextStateName_(nextState), isTransitionToNextState_(false) {};

		virtual ~StateBase() noexcept = default;

	protected:
		//状態の所有者
		std::weak_ptr<OwnerType> owner_;

		//自分自身の状態の名前
		KeyType myStateName_;

		//次に行く状態の名前
		KeyType nextStateName_;

		//次の状態に遷移するか？
		bool isTransitionToNextState_;

	public:
		//その状態に入った瞬間にだけ実行する関数
		virtual void Enter(void) = 0;

		//行動処理関数
		virtual void Execute(void) = 0;

		/// <summary>
		/// 次の状態遷移するか?
		/// </summary>
		/// <returns>
		/// true : 次の状態に遷移する
		/// false : 現在の状態を維持する
		/// </returns>
		constexpr bool IsTransitionToNextState(void) const noexcept
		{
			return isTransitionToNextState_;
		}

		//自分自身のの状態を取得
		constexpr KeyType GetMyState(void) const noexcept
		{
			return myStateName_;
		}

		//遷移先の状態を取得
		constexpr KeyType GetNextState(void) const noexcept
		{
			return nextStateName_;
		}

		//状態の所有者
		void SetOwner(const auto& owner) noexcept
		{
			owner_ = owner;
		}

	};
}
