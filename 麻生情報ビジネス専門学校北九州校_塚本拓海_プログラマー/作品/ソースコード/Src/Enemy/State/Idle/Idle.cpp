#include "Idle.h"
#include "Math/MyMath.h"

namespace BOUDAMA
{
	//‰Šú‰»ˆ—ŠÖ”
	void Idle::Enter(void)
	{
		if (const auto& owner = owner_.lock())
		{
			owner->SetVelocity(MyMath::ZERO_VECTOR_3D);
		}

		isTransitionToNextState_ = false;
	}

	//s“®ˆ—ŠÖ”
	void Idle::Execute(void)
	{
		//-1‚Ìê‡‚ÍA‚±‚êˆÈã‰½‚à‚µ‚È‚¢Š®‘S‚É’â~‚³‚¹‚Ä‚¢‚éó‘Ô
		if(maxIdleTime_ == -1)
		{
			//‰½‚à‚µ‚È‚¢
			return;
		}

		++idleTimeCount_;

		if (maxIdleTime_ <= idleTimeCount_)
		{
			isTransitionToNextState_ = true;
		}
	}
}
