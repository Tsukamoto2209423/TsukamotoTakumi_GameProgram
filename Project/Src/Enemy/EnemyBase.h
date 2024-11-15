#pragma once

#include <vector>

#include "Object/Object.h"
#include "StateMachine/StateMachine.h"
#include "Enemy/State/EnemyState.h"

namespace BOUDAMA
{
	namespace ENEMY
	{
		//敵の状態
		enum class STATE
		{
			//プレイヤー探索
			SEARCH,

			//プレイヤー発見
			FIND_OUT,

			//プレイヤー追跡
			CHASE,

			//攻撃溜め
			CHARGE,

			//攻撃中
			ATTACK,

			//ノックバック
			KNOCK_BACK,

			//総数
			NUM
		};

		//吹っ飛ばされるときに速度に掛ける(スカラー倍する)係数
		constexpr float KNOCK_BACK_BOOST = 1.75f;
	}


	//全ての敵の基底クラス
	class EnemyBase : public Object
	{
	protected:
		//状態
		ENEMY::STATE state_;
		//状態遷移用変数
		StateMachine<EnemyState> stateMachine_;


		//吹っ飛ばされて消えるまでの時間計測
		int knockBackTimeCount_;

		//倒されたときにスコアに加算される点数
		int scoreNum_;

		//当たっているか判定するフラグ
		bool isInCollision_;

	public:
		//コンストラクタ
		EnemyBase();

		//デストラクタ
		virtual ~EnemyBase() = default;

		//行動処理関数
		virtual void Step(const Vector3D& playerPos);

		//読み込み処理関数
		virtual void Load(int originalHandle);

		//出現処理関数
		virtual void AppearanceRequest(void);

		virtual void HitCalculation(void) override;

		virtual void SetKnockBack(const Vector3D& hitObjectVelocity);

		//状態取得
		inline ENEMY::STATE GetState(void) const { return state_; }

		//倒された時に加算される点数取得
		inline int GetScoreNum(void) const { return scoreNum_; }

		inline bool IsInCollision(void) const noexcept { return isInCollision_; }
		inline bool SetIsInCollision(bool isInCollision) noexcept { isInCollision_ = isInCollision; }


		void SetStateMachineOwner(const auto& owner) noexcept
		{
			stateMachine_.SetAllStateOwner(owner);
		}
	};
}
