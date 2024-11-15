#pragma once

#include <memory>
#include "Vector/Vector3D.h"
#include "Object/Object.h"

namespace BOUDAMA
{
	//固有の状態に継承させる抽象クラス
	template<class Ty>
	class StateBase
	{
	public:
		using Type = Ty;

		constexpr StateBase(void) noexcept : myStateName_(), nextStateName_(), isTransitionToNextState(false) {};
		explicit constexpr StateBase(const Type initState) noexcept : myStateName_(initState), nextStateName_(initState), isTransitionToNextState(false) {};

		virtual ~StateBase() noexcept = default;

	protected:
		//状態の所有者
		std::weak_ptr<Object> owner_;

		//自分自身の状態の名前
		Type myStateName_;

		//次に行く状態の名前
		Type nextStateName_;

		//次の状態に遷移するか？
		bool isTransitionToNextState;

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
		inline bool IsTransitionToNextState(void) const noexcept
		{
			return isTransitionToNextState;
		}

		//自分自身のの状態を取得
		inline Type GetMyState(void) const noexcept
		{
			return myStateName_;
		}

		//遷移先の状態を取得
		inline Type GetNextState(void) const noexcept
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
