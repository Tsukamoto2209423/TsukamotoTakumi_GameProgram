#pragma once

#include "Object/Object.h"

namespace BOUDAMA
{
	//�e�p���N���X
	class BulletBase : public Object
	{
	protected:
		int type_;
		int lifeSpan_;
		Object* owner_;

	public:
		//�R���X�g���N�^
		BulletBase()
		{
			owner_ = nullptr; type_ = -1; lifeSpan_ = 0;
		}

		//�f�X�g���N�^
		~BulletBase() {}

		//�ǂݍ��ݏ����֐�
		virtual void Load(int originalHandle)
		{
			if (handle_ == -1)
			{
				handle_ = MV1DuplicateModel(originalHandle);
			}
		}

		inline int GetType(void) const { return type_; }

		inline Object* GetOwner() const { return owner_; }
		inline void SetOwner(Object* const owner) { owner_ = owner; }
	};
}
