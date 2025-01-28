#pragma once

#include "Enemy/State/EnemyState.h"
#include "Enemy/EnemyBase.h"

namespace BOUDAMA
{
	//待機状態
	class RunAway final : public EnemyState<EnemyBase>
	{
	private:
		//移動速度
		float moveSpeed_;

		//逃走時間を計測する変数
		int timeCount_;

	public:
		explicit constexpr RunAway(const auto stateName, float moveSpeed) noexcept : EnemyState(stateName), moveSpeed_(moveSpeed), timeCount_(0) {}
		explicit constexpr RunAway(const auto myState, const auto nextState, float moveSpeed) noexcept : EnemyState(myState, nextState), moveSpeed_(moveSpeed), timeCount_(0) {}

		~RunAway() noexcept override = default;

		//初期化処理関数
		void Enter(void) override;

		//行動処理関数
		void Execute(void) override;
	};
}
