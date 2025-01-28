#pragma once

#include <memory>
#include "Object/Object.h"
#include <Player/PlayerParameter.h>

namespace BOUDAMA
{
	//�������N���X
	class SubstanceBase : public Object
	{
	protected:
		//���������Ƃ��̏��L��
		std::weak_ptr<Object> owner_;

		//���������Ƃ��ɃX�R�A�ɉ��Z����l
		int addScoreNum;

	public:
		//�R���X�g���N�^
		SubstanceBase();

		//�f�X�g���N�^
		virtual ~SubstanceBase();

		//�����������֐�
		virtual void Init(void);

		//�ǂݍ��ݏ����֐�
		virtual void Load(int originalHandle);

		//�s�������֐�
		virtual void Step(void);

		//�j�������֐�
		virtual void Fin(void);

		//�������֐�

		/// <summary>
		/// �������������s���֐�
		/// </summary>
		/// <param name="attachObject">�������I�u�W�F�N�g</param>
		virtual void AttachToObject(const std::shared_ptr<Object>& attachObject);

		//�����蔻�菈��
		virtual void HitCalculation(void);

		//�����̏ꏊ�ɏo�����鏈��
		virtual void appearCalculation(const Vector3D& appearPos);

		//�����̏ꏊ�����юU��Ȃ���o�����鏈��
		virtual void FlyAppearCalculation(const Vector3D& appearPos);

		//�v���C���[�ɋz�����܂��悤�ɒǂ������鏈��
		virtual void ChasePosCalculation(const Vector3D& chasePos);

		/// <summary>
		/// �������Ă��Ȃ���
		/// </summary>
		/// <returns>
		/// true : �������Ă��Ȃ�
		/// false : �������Ă���
		/// </returns>
		inline bool IsOwnerExpired(void) const noexcept { return owner_.expired(); }

		//�������Ă���l(���L��)�擾
		inline const auto GetOwner(void) const noexcept { return owner_.lock(); }

		//���L�Ґݒ�
		inline void SetOwner(const std::shared_ptr<Object>& owner) { owner_ = owner; }

		//���L�ҏ�����
		inline void ResetOwner(void) { owner_.reset(); }

		//���������Ƃ��ɃX�R�A�ɉ��Z����l���擾
		inline int GetAddScoreNum(void) const { return addScoreNum; }

		/// <summary>
		/// ���L�҂̓_���[�W��^�������Ԃ�
		/// </summary>
		/// <returns>
		/// true : �_���[�W��^������
		/// false : �_���[�W��^�����Ȃ�
		/// </returns>
		bool IsOwnerNotInvincible(void) const;

	};
}
