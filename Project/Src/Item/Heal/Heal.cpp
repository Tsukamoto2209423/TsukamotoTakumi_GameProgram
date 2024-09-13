#include "Heal.h"

#include "DxLib.h"

#include <Item/ItemParameter.h>

void Heal::Init(void)
{
	healValue_ = 5;

}

void Heal::Step(void)
{
	//ê∂ë∂ÇµÇƒÇ¢Ç»ÇØÇÍÇŒé¿çsÇµÇ»Ç¢
	if (!isAlive_)
	{
		return;
	}

	if (owner_.expired())
	{
		pos_.y - HEAL::GRAVITY > HEAL::GROUND_POS ? pos_.y -= HEAL::GRAVITY : pos_.y = HEAL::GROUND_POS;

		return;
	}

	const std::shared_ptr<Object>& owner = owner_.lock();

	pos_ = owner->GetPos() + HEAL::UP_DISTANCE;
}

//èoåªèàóùä÷êî
void Heal::AppearanceRequest(void)
{
	isAlive_ = true;

	if (owner_.expired())
	{
		pos_ = { HEAL::INIT_POS_X_Z + GetRand(BOMB::INIT_POS_XZ_RAND_MAX_NUM),
			0.0f,
			HEAL::INIT_POS_X_Z + GetRand(BOMB::INIT_POS_XZ_RAND_MAX_NUM) };
	}
}

void Heal::EffectExecute(const std::shared_ptr<Object>& subjectObject)
{
	//HPâÒïú
	subjectObject->AddHP(healValue_);
}
