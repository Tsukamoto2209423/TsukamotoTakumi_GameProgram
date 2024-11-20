#pragma once

#include "Enemy/State/EnemyState.h"
#include "Enemy/EnemyBase.h"

namespace BOUDAMA
{
	//ノックバック状態
	class KnockBack : public EnemyState<EnemyBase>
	{
	private:
		//ノックバックしている時間を計測する変数
		int timeCount_;

		//最大ノックバック継続時間
		int maxTimeCount_;

	public:
		explicit constexpr KnockBack(const auto stateName, int maxTime) : EnemyState(stateName), timeCount_(0), maxTimeCount_(maxTime) {}
		explicit constexpr KnockBack(const auto myState, const auto nextState, int maxTime) : EnemyState(myState, nextState), timeCount_(0), maxTimeCount_(maxTime) {}

		~KnockBack() noexcept override = default;

		//初期化処理関数
		void Enter(void) override;

		//行動処理関数
		void Execute(void) override;
	};

	namespace KNOCK_BACK
	{
		constexpr float SPEED = 1.0f;
	}
}
