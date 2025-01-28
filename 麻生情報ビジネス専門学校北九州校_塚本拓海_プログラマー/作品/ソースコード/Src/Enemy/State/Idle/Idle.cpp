#include "Idle.h"
#include "Math/MyMath.h"

namespace BOUDAMA
{
	//�����������֐�
	void Idle::Enter(void)
	{
		if (const auto& owner = owner_.lock())
		{
			owner->SetVelocity(MyMath::ZERO_VECTOR_3D);
		}

		isTransitionToNextState_ = false;
	}

	//�s�������֐�
	void Idle::Execute(void)
	{
		//-1�̏ꍇ�́A����ȏ㉽�����Ȃ����S�ɒ�~�����Ă�����
		if(maxIdleTime_ == -1)
		{
			//�������Ȃ�
			return;
		}

		++idleTimeCount_;

		if (maxIdleTime_ <= idleTimeCount_)
		{
			isTransitionToNextState_ = true;
		}
	}
}
