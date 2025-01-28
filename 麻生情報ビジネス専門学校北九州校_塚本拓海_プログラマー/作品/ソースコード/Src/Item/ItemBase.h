#pragma once

#include <memory>
#include "Object/Object.h"

namespace BOUDAMA
{
	//�A�C�e���p���N���X
	class ItemBase : public Object
	{
	protected:
		bool playerOnlyEffect_;

	public:
		//�R���X�g���N�^
		ItemBase() : playerOnlyEffect_(false) {}

		//�f�X�g���N�^
		virtual ~ItemBase() = default;

		//�ǂݍ��ݏ����֐�
		virtual void Load(const int originalHandle)
		{
			if (handle_ == -1)
			{
				handle_ = MV1DuplicateModel(originalHandle);
			}
		}

		//�o�������֐�
		virtual void AppearanceRequest(void) = 0;

		//�A�C�e���̌��ʎ��s
		virtual void EffectExecute(const std::shared_ptr<Object>& targetObject) = 0;

		//�v���C���[�̂݌��ʂ��󂯂���A�C�e�����H
		bool IsPlayerOnlyEffect(void) const { return playerOnlyEffect_; }
	};
}
