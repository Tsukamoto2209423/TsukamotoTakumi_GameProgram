#pragma once

#include "Enemy/State/EnemyState.h"
#include "Enemy/EnemyBase.h"

namespace BOUDAMA
{
	namespace CORPSE
	{
		constexpr int MAX_TIME = 60;
	}

	//€‘Ìó‘Ô
	class Corpse final : public EnemyState<EnemyBase>
	{
	private:
		//€‘Ìó‘Ô‚Å‚Á”ò‚Î‚³‚ê‚Ä‚¢‚éŠÔ‚ğŒv‘ª‚·‚é•Ï”
		int timeCount_;

		//€‘Ìó‘Ô‚Å‚Á”ò‚Î‚³‚ê‚éÅ‘åŠÔ
		const int maxTimeCount_;

	public:
		explicit constexpr Corpse(const auto stateName, int maxTime = CORPSE::MAX_TIME) : EnemyState(stateName), timeCount_(0), maxTimeCount_(maxTime) {}
		explicit constexpr Corpse(const auto myState, const auto nextState, int maxTime = CORPSE::MAX_TIME) : EnemyState(myState, nextState), timeCount_(0), maxTimeCount_(maxTime) {}

		~Corpse() noexcept override = default;

		//‰Šú‰»ˆ—ŠÖ”
		void Enter(void) override;

		//s“®ˆ—ŠÖ”
		void Execute(void) override;
	};

}
