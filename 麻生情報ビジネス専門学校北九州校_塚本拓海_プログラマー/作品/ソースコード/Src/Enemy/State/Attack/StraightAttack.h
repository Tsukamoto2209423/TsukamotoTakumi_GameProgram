#pragma once

#include "Enemy/State/EnemyState.h"
#include "Enemy/EnemyBase.h"


namespace BOUDAMA
{
	//’¼üã‚ÉUŒ‚‚·‚éó‘Ô
	class StraightAttack final : public EnemyState<EnemyBase>
	{
	private:
		//ˆÚ“®‘¬“x
		float moveSpeed_;

		//UŒ‚ŠÔ‚ğŒv‘ª‚·‚é•Ï”
		int attackTimeCount_;

		//UŒ‚ŠÔ‚ğŒp‘±‚Å‚«‚éÅ‘åŠÔ
		const int maxAttackTime_;

	public:
		explicit constexpr StraightAttack(const auto stateName, float moveSpeed, int maxAttackTime) noexcept :
			EnemyState(stateName), moveSpeed_(moveSpeed), attackTimeCount_(0), maxAttackTime_(maxAttackTime) {}

		explicit constexpr StraightAttack(const auto myState, const auto nextState, float moveSpeed, int maxAttackTime) noexcept :
			EnemyState(myState, nextState), moveSpeed_(moveSpeed), attackTimeCount_(0), maxAttackTime_(maxAttackTime) {}

		~StraightAttack() noexcept override = default;

		//‰Šú‰»ˆ—ŠÖ”
		void Enter(void) override;

		//s“®ˆ—ŠÖ”
		void Execute(void) override;
	};
}
