#pragma once

#include "Enemy/State/EnemyState.h"
#include "Enemy/EnemyBase.h"

namespace BOUDAMA
{
	namespace FIND_OUT
	{
		constexpr int REACTION_MAX_TIME = 120;

		constexpr Vector3D ADD_EXCLAMATION_DISTANCE = { 0.0f,75.0f,0.0f };
	}

	class FindOut : public EnemyState<EnemyBase>
	{
	private:
		//状態の時間を計測する変数
		int reactionTimeCount_;

		//最大継続時間
		const int maxReactionTimeCount_;

		//「！」の画像を表示する際の距離
		const Vector3D exclamationMarkDistance_;

	public:
		explicit constexpr FindOut(const auto stateName, int maxTime = FIND_OUT::REACTION_MAX_TIME, Vector3D exclamationMarkDistance = FIND_OUT::ADD_EXCLAMATION_DISTANCE) :
			EnemyState(stateName), reactionTimeCount_(0), maxReactionTimeCount_(maxTime), exclamationMarkDistance_(exclamationMarkDistance) {}

		explicit constexpr FindOut(const auto myState, const auto nextState, int maxTime = FIND_OUT::REACTION_MAX_TIME, Vector3D exclamationMarkDistance = FIND_OUT::ADD_EXCLAMATION_DISTANCE) :
			EnemyState(myState, nextState), reactionTimeCount_(0), maxReactionTimeCount_(maxTime), exclamationMarkDistance_(exclamationMarkDistance) {}

		~FindOut() noexcept override = default;

		//初期化処理関数
		void Enter(void) override;

		//行動処理関数
		void Execute(void) override;
	};
}
