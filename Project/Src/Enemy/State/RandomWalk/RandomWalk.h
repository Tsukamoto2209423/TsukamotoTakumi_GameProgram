#pragma once

#include "Enemy/State/EnemyState.h"

namespace BOUDAMA
{
	class RandomWalk : public EnemyState
	{
	public:
		explicit constexpr RandomWalk(const auto stateName) : EnemyState(stateName) {}

		~RandomWalk() noexcept override = default;

		//初期化処理関数
		void Enter(void) override;

		//行動処理関数
		void Execute(void) override;
	};
}
