#pragma once

#include "Enemy/State/EnemyState.h"
#include "Enemy/EnemyBase.h"

namespace BOUDAMA
{
	namespace CORPSE
	{
		constexpr int MAX_TIME = 60;
	}

	//���̏��
	class Corpse final : public EnemyState<EnemyBase>
	{
	private:
		//���̏�ԂŐ�����΂���Ă��鎞�Ԃ��v������ϐ�
		int timeCount_;

		//���̏�ԂŐ�����΂����ő厞��
		const int maxTimeCount_;

	public:
		explicit constexpr Corpse(const auto stateName, int maxTime = CORPSE::MAX_TIME) : EnemyState(stateName), timeCount_(0), maxTimeCount_(maxTime) {}
		explicit constexpr Corpse(const auto myState, const auto nextState, int maxTime = CORPSE::MAX_TIME) : EnemyState(myState, nextState), timeCount_(0), maxTimeCount_(maxTime) {}

		~Corpse() noexcept override = default;

		//�����������֐�
		void Enter(void) override;

		//�s�������֐�
		void Execute(void) override;
	};

}
