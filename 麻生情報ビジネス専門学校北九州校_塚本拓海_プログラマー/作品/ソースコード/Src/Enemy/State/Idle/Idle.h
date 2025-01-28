#pragma once

#include "Enemy/State/EnemyState.h"
#include "Enemy/EnemyBase.h"

namespace BOUDAMA
{
	//�ҋ@���
	class Idle final : public EnemyState<EnemyBase>
	{
	private:
		int idleTimeCount_;

		const int maxIdleTime_;

	public:
		explicit constexpr Idle(const auto stateName, int maxIdleTime = -1) : EnemyState(stateName), idleTimeCount_(0), maxIdleTime_(maxIdleTime) {}
		explicit constexpr Idle(const auto myState, const auto nextState, int maxIdleTime = -1) : EnemyState(myState, nextState), idleTimeCount_(0), maxIdleTime_(maxIdleTime) {}

		~Idle() noexcept override = default;

		//�����������֐�
		void Enter(void) override;

		//�s�������֐�
		void Execute(void) override;
	};
}
