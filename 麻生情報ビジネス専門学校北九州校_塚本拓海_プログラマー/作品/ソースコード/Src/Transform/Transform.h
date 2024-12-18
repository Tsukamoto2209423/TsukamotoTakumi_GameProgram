#pragma once

#include "Vector/Vector3D.h"

//位置・方向・回転を扱う基底クラス
class Transform
{
protected:
	//位置
	Vector3D pos_;

	//方向ベクトル
	Vector3D dir_;

	//回転角度
	Vector3D rot_;

public:
	constexpr Transform() = default;
	virtual ~Transform() = default;

public:
	//現在の位置(XYZ座標)取得
	constexpr Vector3D GetPos(void) const noexcept { return pos_; }

	//位置(XYZ座標)設定
	constexpr void SetPos(const Vector3D& pos) noexcept { pos_ = pos; }

	//位置(XYZ座標)設定
	constexpr void SetPos(float x, float y, float z) noexcept { pos_.x = x; pos_.y = y; pos_.z = z; }

	//位置(XYZ座標)を動かす
	constexpr void MovePos(const Vector3D& direction) noexcept { pos_ += direction; }
	constexpr void MovePos(float x, float y, float z) noexcept { pos_.x += x; pos_.y += y; pos_.z += z; }

	//初期化
	constexpr void ResetPos(void) { pos_ = { 0.0f,0.0f,0.0f }; }


	//X軸取得
	constexpr float GetPosX(void) const noexcept { return pos_.x; }

	//X軸設定
	constexpr void SetPosX(float x) { pos_.x = x; }


	//Y軸取得
	constexpr float GetPosY(void) const noexcept { return pos_.y; }

	//Y軸設定
	constexpr void SetPosY(float y) { pos_.y = y; }


	//Z軸取得
	constexpr float GetPosZ(void) const noexcept { return pos_.z; }

	//Z軸設定
	constexpr void SetPosZ(float z) { pos_.z = z; }


	//方向ベクトル取得
	constexpr Vector3D GetDir(void) const noexcept { return dir_; }

	//方向ベクトル設定
	constexpr void SetDir(const Vector3D& dir) { dir_ = dir; }
	constexpr void SetDir(float x, float y, float z) noexcept { dir_.x = x; dir_.y = y; dir_.z = z; }

	//初期化
	constexpr void ResetDir(void) { dir_ = { 0.0f,0.0f,0.0f }; }


	//回転させる関数
	constexpr void RotatePitch(float x) noexcept { rot_.x += x; }

	inline void RotateYaw(const Vector3D& dir) noexcept { rot_.y = std::atan2(-dir.x, -dir.z); }
	inline void RotateYaw(float x, float z) noexcept { rot_.y = std::atan2(-x, -z); }

	//回転軸取得
	constexpr Vector3D GetRot(void) const noexcept { return rot_; }

	//回転軸設定
	constexpr void SetRot(const Vector3D& rot) { rot_ = rot; }

	//初期化
	constexpr void ResetRot(void) { rot_ = { 0.0f,0.0f,0.0f }; }


	//X軸取得
	constexpr float GetRotX(void) const noexcept { return rot_.x; }

	//X軸設定
	constexpr void SetRotX(float x) { rot_.x = x; }


	//Y軸取得
	constexpr float GetRotY(void) const noexcept { return rot_.y; }

	//Y軸設定
	constexpr void SetRotY(float y) { rot_.y = y; }


	//Z軸取得
	constexpr float GetRotZ(void) const noexcept { return rot_.z; }

	//Z軸設定
	constexpr void SetRotZ(float z) { rot_.z = z; }
};
