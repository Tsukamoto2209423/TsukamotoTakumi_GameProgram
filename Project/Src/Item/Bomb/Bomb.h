#pragma once

#include <memory>
#include "Item/ItemBase.h"
#include "Item/ItemParameter.h"

//爆弾クラス
class Bomb : public ItemBase
{
private:
	//状態管理用変数
	BOMB::STATE state_;

	//爆発するまでの時間
	int countExplodeTimeLimit_;

	//爆発時間
	int explosionTime_;

public:
	//コンストラクタ
	Bomb() { countExplodeTimeLimit_ = BOMB::MAX_EXPLODE_TIME_LIMIT; explosionTime_ = 0; }

	//デストラクタ
	~Bomb() {}

	//初期化処理関数
	void Init(void) override;

	//行動処理関数
	void Step(void) override;

	//出現処理関数
	void AppearanceRequest(void) override;

	//アイテムの効果実行
	void EffectExecute(const std::shared_ptr<Object>& subjectObject);

	//
	void HitCalculation(void) override;

	inline int GetCountExplodeTimeLimit(void) const { return countExplodeTimeLimit_; }

	inline int GetExplosionTime(void) const { return countExplodeTimeLimit_; }

private:
	//通常状態
	void MoveNormal(void);

	//投擲状態
	void MoveThrow(void);

	//爆発状態
	void MoveExplosion(void);

	//関数ポインタ
	const decltype(&Bomb::MoveNormal) MoveFunctionPointer[BOMB_STATE::NUM]
	{
		&Bomb::MoveNormal,
		&Bomb::MoveThrow,
		&Bomb::MoveExplosion
	};
};