#pragma once

#include "Enemy/State/EnemyState.h"
#include "Enemy/EnemyBase.h"

namespace BOUDAMA
{
	namespace CORPSE
	{
		constexpr int MAX_TIME = 60;
	}

	//死体状態
	class Corpse final : public EnemyState<EnemyBase>
	{
	private:
		//死体状態で吹っ飛ばされている時間を計測する変数
		int timeCount_;

		//死体状態で吹っ飛ばされる最大時間
		const int maxTimeCount_;

	public:
		explicit constexpr Corpse(const auto stateName, int maxTime = CORPSE::MAX_TIME) : EnemyState(stateName), timeCount_(0), maxTimeCount_(maxTime) {}
		explicit constexpr Corpse(const auto myState, const auto nextState, int maxTime = CORPSE::MAX_TIME) : EnemyState(myState, nextState), timeCount_(0), maxTimeCount_(maxTime) {}

		~Corpse() noexcept override = default;

		//初期化処理関数
		void Enter(void) override;

		//行動処理関数
		void Execute(void) override;
	};

}
