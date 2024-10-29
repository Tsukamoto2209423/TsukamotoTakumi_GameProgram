#pragma once

#include "State/StateBase.h"

class Idle : public StateBase
{
public:
	Idle();
	~Idle();

private:

	//‰Šú‰»ˆ—ŠÖ”
	void Init(void) override;

	//s“®ˆ—ŠÖ”
	void Step(void) override;
};

Idle::Idle()
{
}

Idle::~Idle()
{
}