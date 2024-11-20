#pragma once

#include "Enemy/State/EnemyState.h"
#include "Enemy/EnemyBase.h"

namespace BOUDAMA
{
	//ランダムウォーク状態
	class RandomWalk : public EnemyState<EnemyBase>
	{
	private:
		//移動速度
		float moveSpeed_;

		//移動可能な範囲
		float maxMovementRange_;

		//方向ベクトルを変える時間を計る変数
		int directionChangeTimeCount_;

		//方向ベクトルを変更する間隔
		int directionChangeInterval_;

	public:
		explicit constexpr RandomWalk(const auto stateName, float moveSpeed, float maxMovementRange, int moveAngleChangeCount_, int directionChangeInterval) :
			EnemyState(stateName), moveSpeed_(moveSpeed), maxMovementRange_(maxMovementRange),
			directionChangeTimeCount_(0), directionChangeInterval_(directionChangeInterval) {}

		explicit constexpr RandomWalk(const auto myState, const auto nextState, float moveSpeed, float maxMovementRange, int moveAngleChangeCount_, int directionChangeInterval) :
			EnemyState(myState, nextState), moveSpeed_(moveSpeed), maxMovementRange_(maxMovementRange),
			directionChangeTimeCount_(0), directionChangeInterval_(directionChangeInterval) {}


		~RandomWalk() noexcept override = default;

		//初期化処理関数
		void Enter(void) override;

		//行動処理関数
		void Execute(void) override;
	};
}
