#pragma once

#include <memory>
#include "Object/Object.h"
#include "Bullet/BulletManager.h"
#include <Substance/SubstanceBase.h>
#include "Combo/Combo.h"
#include "Player2DEffect.h"
#include "Player3DEffect.h"

namespace BOUDAMA
{
	//プレイヤークラス
	class Player final : public Object
	{
	private:
		//くっついた物質を保存する変数
		std::vector<std::weak_ptr<SubstanceBase>> attachedSubstances_;

		//プレイヤーに関する画像を描画する
		Player2DEffect player2dEffect_;

		//プレイヤーに関する3Dエフェクトを描画する
		Player3DEffect player3dEffect_;

		//コンボ計測用変数
		Combo combo_;

		//死んだときに時間計測するときに使う変数
		int deathTimeCount_;

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
		
		//当たり判定処理
		void HitCalculation(int damage) override;

		//死亡イベント
		void DeathEvent(void);

		//死亡イベントが終わったか
		bool IsEndDeathEvent(void);

		//無敵かどうか
		bool IsInvincible(void);

	private:
		//移動計算処理
		void MoveCalculation(void);

		//回転計算処理
		void RotateCalculation(void);

		//ターボを溜める
		void TurboCharge(void);

	public:
		//くっついた物質取得
		inline std::vector<std::weak_ptr<SubstanceBase>>& GetAttachedSubstance(void) { return attachedSubstances_; }

		//くっついた物質追加
		inline void AddAttachedSubstance(const std::shared_ptr<SubstanceBase>& substance) { attachedSubstances_.emplace_back(substance); }

		//コンボ追加
		inline void AddComboNum(void) { combo_.AddComboNum(); }

		//HP加算
		inline void AddHP(int addNum = 1) override
		{
			hp_ += addNum;

			player2dEffect_.EffectRequest(PLAYER_EFFECT::HEAL);
			player3dEffect_.EffectRequest(EFFECT_HANDLE::HEAL_INDEX, pos_, rot_.y);
		}

		//HP減算
		inline void SubHP(int subNum = 1) override
		{
			//HP減算
			hp_ -= subNum;

			player2dEffect_.EffectRequest(PLAYER_EFFECT::DAMAGE);
			player3dEffect_.EffectRequest(EFFECT_HANDLE::DAMAGE_INDEX, pos_, rot_.y);

		}
	};
}
