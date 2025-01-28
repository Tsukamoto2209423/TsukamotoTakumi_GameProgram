#pragma once

#include "Item/ItemBase.h"

namespace BOUDAMA
{
	class Heal final : public ItemBase
	{
	private:
		//�񕜂�����l
		int healValue_;

		//�Y��(float)�������g�p����Ƃ��Ɏg���p�x��
		float floatMotionTheta_;

	public:
		Heal() : healValue_(0), floatMotionTheta_(0.0f) {}

		~Heal() {}

		void Init(void) override;

		void Load(const int originalHandle) override;

		void Step(void) override;

		//�`�揈���֐�
		void Draw(void) override;

		//�o�������֐�
		void AppearanceRequest(void) override;

		//�A�C�e�����g�p�������̌��ʎ��s�֐�
		void EffectExecute(const std::shared_ptr<Object>& targetObject) override;
	};
}
