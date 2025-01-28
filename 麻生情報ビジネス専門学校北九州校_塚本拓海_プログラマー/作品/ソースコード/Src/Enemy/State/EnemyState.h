#pragma once

#include "StateMachine/StateBase.h"
#include "StateParameter.h"

namespace BOUDAMA
{
	//�G�̏�Ԑ�p�̊��N���X
	template<class StateTransitionableEnemy>
	class EnemyState : public StateBase<ENEMY_STATE, StateTransitionableEnemy>
	{
	public:
		explicit constexpr EnemyState(const auto stateName) noexcept : StateBase<ENEMY_STATE, StateTransitionableEnemy>(stateName) {}
		explicit constexpr EnemyState(const auto myState, const auto nextState) noexcept : StateBase<ENEMY_STATE, StateTransitionableEnemy>(myState, nextState) {}

		virtual ~EnemyState() noexcept override = default;

		//���̏�Ԃɓ������u�Ԃɂ������s����֐�
		virtual void Enter(void) override = 0;

		//�s�������֐�
		virtual void Execute(void) override = 0;
	};
}
