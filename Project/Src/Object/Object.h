#pragma once

#include "Vector/Vector3D.h"

//汎用基底クラス
class Object
{
protected:
	//ハンドル
	int handle_;

	//体力
	int hp_;

	//半径
	float radius_;

	//位置
	Vector3D pos_;

	//方向
	Vector3D dir_;

	//速度
	Vector3D velocity_;

	//角度θ
	Vector3D rot_;

	//生存判定
	bool isAlive_;

public:
	//コンストラクタ
	Object()
	{
		handle_ = -1;
		hp_ = 0;
		radius_ = 0.0f;
		isAlive_ = false;
	}

	//デストラクタ
	virtual ~Object() {}

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

	//当たり判定処理
	virtual void HitCalculation(void);

public:
	//ハンドル取得
	inline int GetHandle(void) const noexcept { return handle_; }

	
	//HP加算
	inline void AddHP(int addNum) { hp_ += addNum; }

	//HP減算
	inline void SubHP(int subNum) { hp_ += subNum; }

	//HP取得
	inline int GetHP(void) const noexcept { return hp_; }

	//HP設定
	inline void SetHP(int HP) { hp_ = HP; }


	//半径取得
	inline float GetRadius(void) const noexcept { return radius_; }

	//半径設定
	inline void SetRadius(float radius) { radius_ = radius; }


	/// <summary>
	/// 生存判定取得
	/// </summary>
	/// <returns>
	/// true : 生存している
	/// false : 生存していない
	/// </returns>
	inline bool GetIsActive(void) const noexcept { return isAlive_; }

	//生存判定設定
	inline void SetIsActive(bool authenticity) { isAlive_ = authenticity; }


	//現在の位置(XYZ座標)取得
	inline Vector3D GetPos(void) const noexcept { return pos_; }

	//位置(XYZ座標)設定
	inline void SetPos(const Vector3D& pos) { pos_ = pos; }

	//位置(XYZ座標)設定
	inline void SetPos(float x, float y, float z) { pos_.x = x; pos_.y = y; pos_.z = z; }


	//X軸取得
	inline float GetPosX(void) const noexcept { return pos_.x; }

	//X軸設定
	inline void SetPosX(float x) { pos_.x = x; }


	//Y軸取得
	inline float GetPosY(void) const noexcept { return pos_.y; }

	//Y軸設定
	inline void SetPosY(float y) { pos_.y = y; }


	//Z軸取得
	inline float GetPosZ(void) const noexcept { return pos_.z; }

	//Z軸設定
	inline void SetPosZ(float z) { pos_.z = z; }


	//方向ベクトル取得
	inline Vector3D GetDir(void) const noexcept { return dir_; }

	//方向ベクトル設定
	inline void SetDir(const Vector3D& dir) { dir_ = dir; }


	//速度ベクトル取得
	inline Vector3D GetVelocity(void) const noexcept { return velocity_; }

	//速度ベクトル設定
	inline void SetVelocity(const Vector3D& velocity) { velocity_ = velocity; }

	//速度ベクトル加算
	inline void AddVelocity(const Vector3D& addVelocity) { velocity_ += addVelocity; }

	//速度ベクトル減算
	inline void SubVelocity(const Vector3D& subVelocity) { velocity_ -= subVelocity; }


	//X軸取得
	inline float GetVelocityX(void) const noexcept { return velocity_.x; }

	//X軸設定
	inline void SetVelocityX(float x) { velocity_.x = x; }


	//Y軸取得
	inline float GetVelocityY(void) const noexcept { return velocity_.y; }

	//Y軸設定
	inline void SetVelocityY(float y) { velocity_.y = y; }


	//Z軸取得
	inline float GetVelocityZ(void) const noexcept { return velocity_.z; }

	//Z軸設定
	inline void SetVelocityZ(float z) { velocity_.z = z; }


	//回転軸取得
	inline Vector3D GetRot(void) const noexcept { return rot_; }

	//回転軸設定
	inline void SetRot(const Vector3D& rot) { rot_ = rot; }


	//X軸取得
	inline float GetRotX(void) const noexcept { return rot_.x; }

	//X軸設定
	inline void SetRotX(float x) { rot_.x = x; }


	//Y軸取得
	inline float GetRotY(void) const noexcept { return rot_.y; }

	//Y軸設定
	inline void SetRotY(float y) { rot_.y = y; }


	//Z軸取得
	inline float GetRotZ(void) const noexcept { return rot_.z; }

	//Z軸設定
	inline void SetRotZ(float z) { rot_.z = z; }

};
