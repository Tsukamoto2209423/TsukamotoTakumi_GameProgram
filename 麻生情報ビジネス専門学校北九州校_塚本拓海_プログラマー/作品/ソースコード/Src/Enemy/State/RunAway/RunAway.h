#pragma once

#include "Enemy/State/EnemyState.h"
#include "Enemy/EnemyBase.h"

namespace BOUDAMA
{
	//�ҋ@���
	class RunAway final : public EnemyState<EnemyBase>
	{
	private:
		//�ړ����x
		float moveSpeed_;

		//�������Ԃ��v������ϐ�
		int timeCount_;

	public:
		explicit constexpr RunAway(const auto stateName, float moveSpeed) noexcept : EnemyState(stateName), moveSpeed_(moveSpeed), timeCount_(0) {}
		explicit constexpr RunAway(const auto myState, const auto nextState, float moveSpeed) noexcept : EnemyState(myState, nextState), moveSpeed_(moveSpeed), timeCount_(0) {}

		~RunAway() noexcept override = default;

		//�����������֐�
		void Enter(void) override;

		//�s�������֐�
		void Execute(void) override;
	};
}
