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
			float maxMovementRange, int directionChangeInterval) :
			EnemyState(stateName), moveSpeed_(moveSpeed), maxMoveSpeed_(maxMoveSpeed), squareMaxMoveSpeed_(maxMoveSpeed* maxMoveSpeed),
			squareFindOutRange_(FindOutRange * FindOutRange), maxMovementRange_(maxMovementRange), directionChangeTimeCount_(0), directionChangeInterval_(directionChangeInterval) {}

		explicit constexpr RandomWalk(const auto myState, const auto nextState, float moveSpeed, float maxMoveSpeed, float FindOutRange,
			float maxMovementRange, int directionChangeInterval) :
			EnemyState(myState, nextState), moveSpeed_(moveSpeed), maxMoveSpeed_(maxMoveSpeed), squareMaxMoveSpeed_(maxMoveSpeed* maxMoveSpeed),
			squareFindOutRange_(FindOutRange * FindOutRange), maxMovementRange_(maxMovementRange), directionChangeTimeCount_(0), directionChangeInterval_(directionChangeInterval) {}


		~RandomWalk() noexcept override = default;

		//初期化処理関数
		void Enter(void) override;

		//行動処理関数
		void Execute(void) override;
	};
}
