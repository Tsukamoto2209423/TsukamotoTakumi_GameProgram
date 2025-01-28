#pragma once

#include "Enemy/State/EnemyState.h"
#include "Enemy/EnemyBase.h"


namespace BOUDAMA
{
	//������ɍU��������
	class StraightAttack final : public EnemyState<EnemyBase>
	{
	private:
		//�ړ����x
		float moveSpeed_;

		//�U�����Ԃ��v������ϐ�
		int attackTimeCount_;

		//�U�����Ԃ��p���ł���ő厞��
		const int maxAttackTime_;

	public:
		explicit constexpr StraightAttack(const auto stateName, float moveSpeed, int maxAttackTime) noexcept :
			EnemyState(stateName), moveSpeed_(moveSpeed), attackTimeCount_(0), maxAttackTime_(maxAttackTime) {}

		explicit constexpr StraightAttack(const auto myState, const auto nextState, float moveSpeed, int maxAttackTime) noexcept :
			EnemyState(myState, nextState), moveSpeed_(moveSpeed), attackTimeCount_(0), maxAttackTime_(maxAttackTime) {}

		~StraightAttack() noexcept override = default;

		//�����������֐�
		void Enter(void) override;

		//�s�������֐�
		void Execute(void) override;
	};
}
