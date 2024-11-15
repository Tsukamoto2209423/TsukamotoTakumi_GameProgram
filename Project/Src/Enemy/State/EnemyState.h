#pragma once

#include "StateMachine/StateBase.h"
#include "StateParameter.h"

namespace BOUDAMA
{
	//敵の状態専用の基底クラス
	class EnemyState : public StateBase<ENEMY_STATE>
	{
	public:
		explicit constexpr EnemyState(const ENEMY_STATE stateName) noexcept : StateBase(stateName) {}

		virtual ~EnemyState() noexcept = default;

		//その状態に入った瞬間にだけ実行する関数
		virtual void Enter(void) override = 0;

		//行動処理関数
		virtual void Execute(void) override = 0;
	};
}
