#include "Heal.h"

#include "DxLib.h"

#include <Item/ItemParameter.h>

void Heal::Init(void)
{
	healValue_ = HEAL::HEAL_VALUE;
}

void Heal::Step(void)
{
	//生存していなければ実行しない
	if (!isAlive_)
	{
		return;
	}

	//アイテムが床に落ちている場合
	if (owner_.expired())
	{
		pos_.y - HEAL::GRAVITY > HEAL::GROUND_POS ? pos_.y -= HEAL::GRAVITY : pos_.y = HEAL::GROUND_POS;

		return;
	}

	const std::shared_ptr<Object>& owner = owner_.lock();

	pos_ = owner->GetPos() + HEAL::UP_DISTANCE;
}

//出現処理関数
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

//アイテムを使用した時の効果実行関数
void Heal::EffectExecute(const std::shared_ptr<Object>& subjectObject)
{
	//HP回復
	subjectObject->AddHP(healValue_);
}
