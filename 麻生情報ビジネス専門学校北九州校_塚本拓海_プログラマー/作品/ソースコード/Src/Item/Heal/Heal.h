#pragma once

#include "Item/ItemBase.h"

namespace BOUDAMA
{
	class Heal final : public ItemBase
	{
	private:
		//回復させる値
		int healValue_;

		//漂う(float)動きを使用するときに使う角度θ
		float floatMotionTheta_;

	public:
		Heal() : healValue_(0), floatMotionTheta_(0.0f) {}

		~Heal() {}

		void Init(void) override;

		void Load(const int originalHandle) override;

		void Step(void) override;

		//描画処理関数
		void Draw(void) override;

		//出現処理関数
		void AppearanceRequest(void) override;

		//アイテムを使用した時の効果実行関数
		void EffectExecute(const std::shared_ptr<Object>& targetObject) override;
	};
}
