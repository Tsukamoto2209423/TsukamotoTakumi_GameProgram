#pragma once

#include "Enemy/State/EnemyState.h"
#include "Enemy/EnemyBase.h"

namespace BOUDAMA
{
	namespace KNOCK_BACK
	{
		constexpr int MAX_KNOCK_BACK_TIME = 30;
	}

	//�m�b�N�o�b�N���
	class KnockBack : public EnemyState<EnemyBase>
	{
	private:
		//�m�b�N�o�b�N���Ă��鎞�Ԃ��v������ϐ�
		int timeCount_;

		//�ő�m�b�N�o�b�N�p������
		const int maxTimeCount_;

	public:
		explicit constexpr KnockBack(const auto stateName, int maxTime = KNOCK_BACK::MAX_KNOCK_BACK_TIME) : EnemyState(stateName), timeCount_(0), maxTimeCount_(maxTime) {}
		explicit constexpr KnockBack(const auto myState, const auto nextState, int maxTime = KNOCK_BACK::MAX_KNOCK_BACK_TIME) : EnemyState(myState, nextState), timeCount_(0), maxTimeCount_(maxTime) {}

		~KnockBack() noexcept override = default;

		//�����������֐�
		void Enter(void) override;

		//�s�������֐�
		void Execute(void) override;
	};

}
