#pragma once

#include "Enemy/State/EnemyState.h"

namespace BOUDAMA
{
	class RandomWalk : public EnemyState
	{
	public:
		explicit constexpr RandomWalk(const auto stateName) : EnemyState(stateName) {}

		~RandomWalk() noexcept override = default;

		//‰Šú‰»ˆ—ŠÖ”
		void Enter(void) override;

		//s“®ˆ—ŠÖ”
		void Execute(void) override;
	};
}
