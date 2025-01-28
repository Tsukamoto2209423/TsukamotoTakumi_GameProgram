#pragma once

#include "Enemy/State/EnemyState.h"
#include "Enemy/EnemyBase.h"

namespace BOUDAMA
{
	//�ǔ����
	class Chase final : public EnemyState<EnemyBase>
	{
	private:
		//�ړ����x
		float moveSpeed_;

	public:
		explicit constexpr Chase(const auto stateName, float moveSpeed) noexcept : EnemyState(stateName), moveSpeed_(moveSpeed) {}
		explicit constexpr Chase(const auto myState, const auto nextState, float moveSpeed) noexcept : EnemyState(myState, nextState), moveSpeed_(moveSpeed) {}

		~Chase() noexcept override = default;

		//�����������֐�
		void Enter(void) override;

		//�s�������֐�
		void Execute(void) override;
	};
}
