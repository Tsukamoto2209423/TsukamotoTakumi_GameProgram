#pragma once

#include <memory>

namespace BOUDAMA
{
	//�ŗL�̏�ԂɌp�������钊�ۃN���X
	template<class Ty, class Owner>
	class StateBase
	{
	public:
		using KeyType = Ty;
		using OwnerType = Owner;

		explicit constexpr StateBase(const KeyType initState) noexcept : myStateName_(initState), nextStateName_(initState), isTransitionToNextState_(false) {};
		explicit constexpr StateBase(const KeyType myState, const KeyType nextState) noexcept : myStateName_(myState), nextStateName_(nextState), isTransitionToNextState_(false) {};

		virtual ~StateBase() noexcept = default;

	protected:
		//��Ԃ̏��L��
		std::weak_ptr<OwnerType> owner_;

		//�������g�̏�Ԃ̖��O
		KeyType myStateName_;

		//���ɍs����Ԃ̖��O
		KeyType nextStateName_;

		//���̏�ԂɑJ�ڂ��邩�H
		bool isTransitionToNextState_;

	public:
		//���̏�Ԃɓ������u�Ԃɂ������s����֐�
		virtual void Enter(void) = 0;

		//�s�������֐�
		virtual void Execute(void) = 0;

		/// <summary>
		/// ���̏�ԑJ�ڂ��邩?
		/// </summary>
		/// <returns>
		/// true : ���̏�ԂɑJ�ڂ���
		/// false : ���݂̏�Ԃ��ێ�����
		/// </returns>
		constexpr bool IsTransitionToNextState(void) const noexcept
		{
			return isTransitionToNextState_;
		}

		//�������g�̂̏�Ԃ��擾
		constexpr KeyType GetMyState(void) const noexcept
		{
			return myStateName_;
		}

		//�J�ڐ�̏�Ԃ��擾
		constexpr KeyType GetNextState(void) const noexcept
		{
			return nextStateName_;
		}

		//��Ԃ̏��L��
		void SetOwner(const auto& owner) noexcept
		{
			owner_ = owner;
		}

	};
}
