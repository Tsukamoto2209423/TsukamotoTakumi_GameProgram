#pragma once

#include "Enemy/State/EnemyState.h"
#include "Enemy/EnemyBase.h"

namespace BOUDAMA
{
	namespace RANDOM_WALK
	{
		constexpr int DIRECTION_CHANGE_INTERVAL = 150;

		constexpr float MAX_MOVEMENT_RANGE = 7000.0f;
	}

	//ランダムウォーク状態
	class RandomWalk : public EnemyState<EnemyBase>
	{
	private:
		//移動速度
		float moveSpeed_;

		//最大移動速度
		float maxMoveSpeed_;

		//最大移動速度の二乗
		float squareMaxMoveSpeed_;

		//発見可能範囲の二乗
		float squareFindOutRange_;

		//移動可能な範囲
		float maxMovementRange_;

		//方向ベクトルを変える時間を計る変数
		int directionChangeTimeCount_;

		//方向ベクトルを変更する間隔
		const int directionChangeInterval_;

	public:
		explicit constexpr RandomWalk(const auto stateName, float moveSpeed, float maxMoveSpeed, float FindOutRange,
			float maxMovementRange = RANDOM_WALK::MAX_MOVEMENT_RANGE, int directionChangeInterval = RANDOM_WALK::DIRECTION_CHANGE_INTERVAL) :
			EnemyState(stateName), moveSpeed_(moveSpeed), maxMoveSpeed_(maxMoveSpeed), squareMaxMoveSpeed_(maxMoveSpeed * maxMoveSpeed),
			squareFindOutRange_(FindOutRange * FindOutRange), maxMovementRange_(maxMovementRange), directionChangeTimeCount_(0), directionChangeInterval_(directionChangeInterval) {}

		explicit constexpr RandomWalk(const auto myState, const auto nextState, float moveSpeed, float maxMoveSpeed, float FindOutRange,
			float maxMovementRange = RANDOM_WALK::MAX_MOVEMENT_RANGE, int directionChangeInterval = RANDOM_WALK::DIRECTION_CHANGE_INTERVAL) :
			EnemyState(myState, nextState), moveSpeed_(moveSpeed), maxMoveSpeed_(maxMoveSpeed), squareMaxMoveSpeed_(maxMoveSpeed * maxMoveSpeed),
			squareFindOutRange_(FindOutRange * FindOutRange), maxMovementRange_(maxMovementRange), directionChangeTimeCount_(0), directionChangeInterval_(directionChangeInterval) {}


		~RandomWalk() noexcept override = default;

		//初期化処理関数
		void Enter(void) override;

		//行動処理関数
		void Execute(void) override;
	};

}
