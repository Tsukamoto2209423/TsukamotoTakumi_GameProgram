#pragma once

#include <memory>
#include "Object/Object.h"
#include "PlayerEffect.h"
#include "Bullet/BulletManager.h"
#include <Substance/SubstanceBase.h>
#include "Combo/Combo.h"

//プレイヤークラス
class Player : public Object
{
private:
	//くっついた物質を保存する変数
	std::vector<std::weak_ptr<SubstanceBase>> attachedSubstances_;

	//プレイヤーに関する画像を描画する
	PlayerEffect playerUI_;

	//コンボ計測用変数
	Combo combo_;

	int deathTimeCount;

	bool isShadowDraw;

public:
	//コンストラクタ
	Player();

	//デストラクタ
	~Player();

	//初期化処理関数
	void Init(void) override;

	//読み込み処理関数
	void Load(void) override;

	//行動処理関数
	void Step(void) override;

	//描画処理関数
	void Draw(void) override;

	//破棄処理関数
	void Fin(void) override;

	//当たり判定処理
	void HitCalculation(void) override;

	//移動計算処理
	void MoveCalculation(void);

	//回転計算処理
	void RotateCalculation(void);

	//ターボを溜める
	void TurboCharge(void);

	//死亡イベント
	void DeathEvent(void);

	//死亡イベントが終わったか
	bool IsEndDeathEvent(void);

	//無敵かどうか
	bool IsInvincible(void);

	//くっついた物質取得
	inline std::vector<std::weak_ptr<SubstanceBase>> &GetAttachedSubstance(void) { return attachedSubstances_; }

	//くっついた物質追加
	inline void AddAttachedSubstance(const std::shared_ptr<SubstanceBase>& substance) { attachedSubstances_.emplace_back(substance); }

	//コンボ追加
	inline void AddComboNum(void) { combo_.AddComboNum(); }
};
