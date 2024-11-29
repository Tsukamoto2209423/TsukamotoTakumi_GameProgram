#pragma once

#include <memory>
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
		using StateMachineType = StateMachine<ENEMY_STATE, EnemyBase>;

		//状態
		//ENEMY::STATE state_;
		//状態遷移用変数
		std::unique_ptr<StateMachineType> stateMachine_;

		//狙っている物体の位置
		Vector3D targetPosition_;

		//倒されたときにスコアに加算される点数
		int scoreNum_;

		//当たり判定有効フラグ
		bool isCollisionEnabled_;

		//無敵か？
		bool isInvincible_;

	public:
		//コンストラクタ
		constexpr EnemyBase() : scoreNum_(0), isCollisionEnabled_(true), isInvincible_(false) {}

		//デストラクタ
		virtual ~EnemyBase() = default;

		//行動処理関数
		virtual void Step(const Vector3D& playerPos);

		//読み込み処理関数
		virtual void Load(int originalHandle);

		//出現処理関数
		virtual void AppearanceRequest(void);

		virtual void HitCalculation(void) override;

		virtual void DeathCalculation(const Vector3D& hitObjectVelocity);

		//状態取得
		//inline ENEMY::STATE GetState(void) const { return state_; }

		inline Vector3D GetTargetPosition(void) const noexcept { return targetPosition_; }

		inline void SetTargetPosition(const Vector3D& targetPos) noexcept { targetPosition_ = targetPos; }

		//倒された時に加算される点数取得
		inline int GetScoreNum(void) const { return scoreNum_; }

		inline bool IsCollisionEnabled(void) const noexcept { return isCollisionEnabled_; }
		inline void SetIsCollisionEnabled(bool isInCollision) noexcept { isCollisionEnabled_ = isInCollision; }

		//無敵か？
		inline bool IsInvincible(void) const noexcept { return isInvincible_; };
		inline void SetIsInvincible(bool isInvincible) noexcept { isInvincible_ = isInvincible; }

		void SetStateMachineOwner(const auto& owner)
		{
			stateMachine_->SetAllStateOwner(owner);
		}
	};
}
