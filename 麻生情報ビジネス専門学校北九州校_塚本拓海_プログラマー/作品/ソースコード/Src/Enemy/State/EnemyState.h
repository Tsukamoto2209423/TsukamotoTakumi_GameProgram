#pragma once

#include "StateMachine/StateBase.h"
#include "StateParameter.h"

namespace BOUDAMA
{
	//敵の状態専用の基底クラス
	template<class StateTransitionableEnemy>
	class EnemyState : public StateBase<ENEMY_STATE, StateTransitionableEnemy>
	{
	public:
		explicit constexpr EnemyState(const auto stateName) noexcept : StateBase<ENEMY_STATE, StateTransitionableEnemy>(stateName) {}
		explicit constexpr EnemyState(const auto myState, const auto nextState) noexcept : StateBase<ENEMY_STATE, StateTransitionableEnemy>(myState, nextState) {}

		virtual ~EnemyState() noexcept = default;

		//その状態に入った瞬間にだけ実行する関数
		virtual void Enter(void) override = 0;

		//行動処理関数
		virtual void Execute(void) override = 0;
	};
}
