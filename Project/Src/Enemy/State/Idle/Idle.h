#pragma once

#include "Enemy/State/EnemyState.h"

namespace BOUDAMA
{
	//待機状態
	class Idle final : public EnemyState
	{
	public:
		explicit constexpr Idle(const auto stateName) : EnemyState(stateName) {}

		~Idle() noexcept override = default;

		//初期化処理関数
		void Enter(void) override;

		//行動処理関数
		void Execute(void) override;
	};
}
