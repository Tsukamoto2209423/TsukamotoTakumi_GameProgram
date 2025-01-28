#pragma once

#include "Vector/Vector3D.h"
#include "Transform/Transform.h"

namespace BOUDAMA
{
	//�ėp���N���X
	class Object : public Transform
	{
	protected:
		//�n���h��
		int handle_;

		//�̗�
		int hp_;

		//���a
		float radius_;

		//���x
		Vector3D velocity_;

		//��������
		bool isAlive_;

	public:
		//�R���X�g���N�^
		constexpr Object() noexcept :
			handle_(-1),
			hp_(0),
			radius_(0.0f),
			isAlive_(false)  {}

		//�f�X�g���N�^
		virtual ~Object() = default;

		//�����������֐�
		virtual void Init(void);

		//�ǂݍ��ݏ����֐�
		virtual void Load(void);

		//�s�������֐�
		virtual void Step(void);

		//�`�揈���֐�
		virtual void Draw(void);

		//�j�������֐�
		virtual void Fin(void);

		//�Փˎ��̌v�Z����
		virtual void HitCalculation(void);

		//�Փˎ��̌v�Z����
		virtual void HitCalculation(int damage);

	public:
		//�n���h���擾
		constexpr int GetHandle(void) const noexcept { return handle_; }


		//HP���Z
		virtual constexpr void AddHP(int addNum) { hp_ += addNum; }

		//HP���Z
		virtual constexpr void SubHP(int subNum) { hp_ -= subNum; }

		//HP�擾
		constexpr int GetHP(void) const noexcept { return hp_; }

		//HP�ݒ�
		constexpr void SetHP(int HP) { hp_ = HP; }


		//���a�擾
		constexpr float GetRadius(void) const noexcept { return radius_; }

		//���a�ݒ�
		constexpr void SetRadius(float radius) { radius_ = radius; }


		/// <summary>
		/// ��������擾
		/// </summary>
		/// <returns>
		/// true : �������Ă���
		/// false : �������Ă��Ȃ�
		/// </returns>
		constexpr bool GetIsActive(void) const noexcept { return isAlive_; }

		//��������ݒ�
		constexpr void SetIsActive(bool authenticity) { isAlive_ = authenticity; }


		//���x�x�N�g���擾
		constexpr Vector3D GetVelocity(void) const noexcept { return velocity_; }

		//���x�x�N�g���ݒ�
		constexpr void SetVelocity(const Vector3D& velocity) { velocity_ = velocity; }

		//���x�x�N�g�����Z
		constexpr void AddVelocity(const Vector3D& addVelocity) { velocity_ += addVelocity; }

		//���x�x�N�g�����Z
		constexpr void SubVelocity(const Vector3D& subVelocity) { velocity_ -= subVelocity; }


		//X���擾
		constexpr float GetVelocityX(void) const noexcept { return velocity_.x; }

		//X���ݒ�
		constexpr void SetVelocityX(float x) { velocity_.x = x; }


		//Y���擾
		constexpr float GetVelocityY(void) const noexcept { return velocity_.y; }

		//Y���ݒ�
		constexpr void SetVelocityY(float y) { velocity_.y = y; }


		//Z���擾
		constexpr float GetVelocityZ(void) const noexcept { return velocity_.z; }

		//Z���ݒ�
		constexpr void SetVelocityZ(float z) { velocity_.z = z; }
	};
}
