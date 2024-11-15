#pragma once

#include "Enemy/State/EnemyState.h"

namespace BOUDAMA
{
	//追尾状態
	class Chase final : public EnemyState
	{
	private:
		//移動速度
		float moveSpeed_;

	public:
		explicit constexpr Chase(const auto stateName, float moveSpeed) noexcept : EnemyState(stateName), moveSpeed_(moveSpeed) {}
		~Chase() noexcept override = default;

		//初期化処理関数
		void Enter(void) override;

		//行動処理関数
		void Execute(void) override;
	};
}
