#pragma once

#include "Enemy/State/EnemyState.h"
#include "Enemy/EnemyBase.h"

namespace BOUDAMA
{
	class FindOut : public EnemyState<EnemyBase>
	{
	private:
		//状態の時間を計測する変数
		int reactionTimeCount_;

		//最大継続時間
		int maxReactionTimeCount_;

		//「！」の画像ハンドル
		int exclamationMarkHandle_;

	public:
		explicit constexpr FindOut(const auto stateName, int maxTime) : EnemyState(stateName), reactionTimeCount_(0), maxReactionTimeCount_(maxTime) {}
		explicit constexpr FindOut(const auto myState, const auto nextState, int maxTime) : EnemyState(myState, nextState), reactionTimeCount_(0), maxReactionTimeCount_(maxTime) {}

		~FindOut() noexcept override = default;

		//初期化処理関数
		void Enter(void) override;

		//行動処理関数
		void Execute(void) override;
	};
}