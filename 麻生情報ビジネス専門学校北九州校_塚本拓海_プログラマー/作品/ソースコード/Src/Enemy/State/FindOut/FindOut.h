#pragma once

#include "Enemy/State/EnemyState.h"
#include "Enemy/EnemyBase.h"

namespace BOUDAMA
{
	namespace FIND_OUT
	{
		constexpr int REACTION_MAX_TIME = 120;

		constexpr Vector3D ADD_EXCLAMATION_DISTANCE = { 0.0f,75.0f,0.0f };
	}

	class FindOut : public EnemyState<EnemyBase>
	{
	private:
		//��Ԃ̎��Ԃ��v������ϐ�
		int reactionTimeCount_;

		//�ő�p������
		const int maxReactionTimeCount_;

		//�u�I�v�̉摜��\������ۂ̋���
		const Vector3D exclamationMarkDistance_;

	public:
		explicit constexpr FindOut(const auto stateName, int maxTime = FIND_OUT::REACTION_MAX_TIME, Vector3D exclamationMarkDistance = FIND_OUT::ADD_EXCLAMATION_DISTANCE) :
			EnemyState(stateName), reactionTimeCount_(0), maxReactionTimeCount_(maxTime), exclamationMarkDistance_(exclamationMarkDistance) {}

		explicit constexpr FindOut(const auto myState, const auto nextState, int maxTime = FIND_OUT::REACTION_MAX_TIME, Vector3D exclamationMarkDistance = FIND_OUT::ADD_EXCLAMATION_DISTANCE) :
			EnemyState(myState, nextState), reactionTimeCount_(0), maxReactionTimeCount_(maxTime), exclamationMarkDistance_(exclamationMarkDistance) {}

		~FindOut() noexcept override = default;

		//�����������֐�
		void Enter(void) override;

		//�s�������֐�
		void Execute(void) override;
	};
}
