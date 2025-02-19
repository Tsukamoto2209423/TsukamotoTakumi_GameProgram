#pragma once

#include "Vector/Vector3D.h"
#include "Transform/Transform.h"

namespace BOUDAMA
{
	//汎用基底クラス
	class Object : public Transform
	{
	protected:
		//ハンドル
		int handle_;

		//体力
		int hp_;

		//半径
		float radius_;

		//速度
		Vector3D velocity_;

		//生存判定
		bool isAlive_;

	public:
		//コンストラクタ
		constexpr Object() noexcept :
			handle_(-1),
			hp_(0),
			radius_(0.0f),
			isAlive_(false)  {}

		//デストラクタ
		virtual ~Object() = default;

		//初期化処理関数
		virtual void Init(void);

		//読み込み処理関数
		virtual void Load(void);

		//行動処理関数
		virtual void Step(void);

		//描画処理関数
		virtual void Draw(void);

		//破棄処理関数
		virtual void Fin(void);

		//衝突時の計算処理
		virtual void HitCalculation(void);

		//衝突時の計算処理
		virtual void HitCalculation(int damage);

	public:
		//ハンドル取得
		constexpr int GetHandle(void) const noexcept { return handle_; }


		//HP加算
		virtual constexpr void AddHP(int addNum) { hp_ += addNum; }

		//HP減算
		virtual constexpr void SubHP(int subNum) { hp_ -= subNum; }

		//HP取得
		constexpr int GetHP(void) const noexcept { return hp_; }

		//HP設定
		constexpr void SetHP(int HP) { hp_ = HP; }


		//半径取得
		constexpr float GetRadius(void) const noexcept { return radius_; }

		//半径設定
		constexpr void SetRadius(float radius) { radius_ = radius; }


		/// <summary>
		/// 生存判定取得
		/// </summary>
		/// <returns>
		/// true : 生存している
		/// false : 生存していない
		/// </returns>
		constexpr bool GetIsActive(void) const noexcept { return isAlive_; }

		//生存判定設定
		constexpr void SetIsActive(bool authenticity) { isAlive_ = authenticity; }


		//速度ベクトル取得
		constexpr Vector3D GetVelocity(void) const noexcept { return velocity_; }

		//速度ベクトル設定
		constexpr void SetVelocity(const Vector3D& velocity) { velocity_ = velocity; }

		//速度ベクトル加算
		constexpr void AddVelocity(const Vector3D& addVelocity) { velocity_ += addVelocity; }

		//速度ベクトル減算
		constexpr void SubVelocity(const Vector3D& subVelocity) { velocity_ -= subVelocity; }


		//X軸取得
		constexpr float GetVelocityX(void) const noexcept { return velocity_.x; }

		//X軸設定
		constexpr void SetVelocityX(float x) { velocity_.x = x; }


		//Y軸取得
		constexpr float GetVelocityY(void) const noexcept { return velocity_.y; }

		//Y軸設定
		constexpr void SetVelocityY(float y) { velocity_.y = y; }


		//Z軸取得
		constexpr float GetVelocityZ(void) const noexcept { return velocity_.z; }

		//Z軸設定
		constexpr void SetVelocityZ(float z) { velocity_.z = z; }
	};
}
