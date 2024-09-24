#pragma once

#include "Item/ItemBase.h"

class Heal : public ItemBase
{
private:
	//回復させる値
	int healValue_;

public:
	Heal() { healValue_ = 0; }

	~Heal() {}

	void Init(void) override;

	void Step(void) override;

	//出現処理関数
	void AppearanceRequest(void) override;

	//アイテムを使用した時の効果実行関数
	void EffectExecute(const std::shared_ptr<Object>& subjectObject) override;
};
