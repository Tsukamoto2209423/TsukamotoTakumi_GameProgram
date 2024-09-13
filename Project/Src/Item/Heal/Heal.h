#pragma once

#include "Item/ItemBase.h"

class Heal : public ItemBase
{
private:
	//‰ñ•œ‚³‚¹‚é’l
	int healValue_;

public:
	Heal() { healValue_ = 0; }

	~Heal(){}

	void Init(void) override;

	void Step(void) override;

	//oŒ»ˆ—ŠÖ”
	void AppearanceRequest(void) override;

	
	void EffectExecute(const std::shared_ptr<Object>& subjectObject);
};
