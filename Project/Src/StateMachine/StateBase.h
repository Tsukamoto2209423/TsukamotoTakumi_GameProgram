#pragma once

#include <memory>
#include "Vector/Vector3D.h"
#include "Object/Object.h"

namespace BOUDAMA
{
	//固有の状態に継承させる抽象クラス
	template<class T>
	class StateBase
	{
	protected:
		//状態の所有者
		std::weak_ptr<Object> owner_;

		//次に行く状態の名前
		T nextStateName_;

	public:
		StateBase() = default;

		StateBase(const std::shared_ptr<Object>& owner) : owner_(owner) {};

		virtual ~StateBase() = default;

		//初期化処理関数
		virtual void Init(void) = 0;

		//行動処理関数
		virtual void Step(void) = 0;
	
		/// <summary>
		/// 次の状態遷移できるか?
		/// </summary>
		/// <returns>
		/// true : 次の状態に遷移する
		/// false : 現在の状態を維持する
		/// </returns>
		virtual bool CanTransitionToNextState(void) const = 0 ;

		//遷移先の状態を取得
		virtual T GetNextState(void) const = 0 ;

	};
}
