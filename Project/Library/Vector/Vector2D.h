#pragma once

#include "DxLib.h"
#include <math.h>

//二次元の実数上のベクトルクラス
class Vector2D
{
public:
	//メンバ変数
	float x, y;

	constexpr Vector2D() noexcept : x(0.0f), y(0.0f) {}
	explicit constexpr Vector2D(float initNum) noexcept : x(initNum), y(initNum) {}
	constexpr Vector2D(float init_x, float init_y) noexcept : x(init_x), y(init_y) {}
	constexpr Vector2D(const Vector2D& vec) noexcept : x(vec.x), y(vec.y) {}
	constexpr Vector2D(const VECTOR& vec) noexcept : x(vec.x), y(vec.y) {}

	//引数に入力した値を取得する関数(x = value_x, y = value_y)
	inline constexpr Vector2D VGet(float value_x, float value_y) { this->x = value_x, this->y = value_y; return *this; }
	//引数に入力した値を取得する関数(x = y = value)
	inline constexpr Vector2D VGet(float value) { this->x = value, this->y = value; return *this; }
	//引数に入力した値を取得する関数(x = vec.x, y = vec.y)
	inline constexpr Vector2D VGet(const Vector2D& vec) { this->x = vec.x, this->y = vec.y; return *this; }

	//Vector2Dの加算の定義
	inline Vector2D operator+(const Vector2D& vec) const { this->x + vec.x, this->y + vec.y; return *this; }

	//Vector2Dの加算代入の定義
	inline Vector2D operator+=(const Vector2D& vec) { return *this = *this + vec; }

	//Vector2Dの減算の定義
	inline Vector2D operator-(const Vector2D& vec) const { this->x - vec.x, this->y - vec.y; return *this; }

	//Vector2Dの減算代入の定義
	inline Vector2D operator-=(const Vector2D& vec) { return *this = *this - vec; }

	//Vector2Dのスカラー倍の定義
	inline Vector2D operator*(float scale) const { return Vector2D(this->x * scale, this->y * scale); }

	inline Vector2D operator*(const Vector2D& vec) const { this->x* vec.x, this->y* vec.y; return *this; }

	//Vector2Dのスカラー倍代入の定義
	inline Vector2D operator*=(float scale) { return *this = *this * scale; }

	inline Vector2D operator*=(const Vector2D& vec) { return *this = *this * vec; }

	//Vector2Dの代入の定義
	inline Vector2D operator=(const Vector2D& vec) { this->x = vec.x, this->y = vec.y; return *this; }

	//同一ベクトル判定
	inline bool operator==(const Vector2D& vec) const { return (x == vec.x && y == vec.y); }
	inline bool operator!=(const Vector2D& vec) const { return !(*this == vec); }

	//DXライブラリのベクトル構造体へのキャスト演算子
	inline operator VECTOR() const { return VECTOR{ x, y, 0.0f }; }

	// 始点と終点からベクトルを作成
	Vector2D VecCreate(const Vector2D& start, const Vector2D& end)
	{
		//終点 - 始点
		return Vector2D(end.x - start.x, end.y - start.y);
	}

	// ベクトルの足し算
	Vector2D VecAdd(const Vector2D& vec1, const Vector2D& vec2)
	{
		//各成分を加算
		return Vector2D(vec1.x + vec2.x, vec1.y + vec2.y);
	}

	//L2ノルム
	float VecL2Norm(const Vector2D& vec)
	{
		// ||vec||_2 = √(|vec.x|^2 + |vec.y|^2)
		return sqrtf(vec.x * vec.x + vec.y * vec.y);
	}

	//単位ベクトル作成
	Vector2D Normalize(const Vector2D& vec)
	{
		Vector2D result;

		//ベクトルの長さを求める
		float vec_norm = VecL2Norm(vec);

		//各成分を長さで割り正規化する
		result.x = vec.x / vec_norm;
		result.y = vec.y / vec_norm;

		return result;
	}

	//単位ベクトルを作成しスカラー倍
	Vector2D VecNormalizeAndScalartimes(const Vector2D& vec, float scale)
	{
		float vec_norm = VecL2Norm(vec);

		return { (vec.x / vec_norm) * scale, (vec.y / vec_norm) * scale };
	}

	//ベクトルを作成し単位ベクトルにしてスカラー倍
	Vector2D VecNormalizeAndScalartimes(const Vector2D& start, const Vector2D& end, float scale)
	{
		Vector2D vec;

		vec.x = end.x - start.x;
		vec.y = end.y - start.y;

		float vec_norm = VecL2Norm(vec);

		return { (vec.x / vec_norm) * scale, (vec.y / vec_norm) * scale };
	}

	// ベクトルのスカラー倍
	Vector2D VecScalartimes(const Vector2D& vec, float scale)
	{
		//各成分をスカラー倍
		return Vector2D(vec.x * scale, vec.y * scale);
	}

	// ベクトルの内積
	float VecDot(const Vector2D& vec1, const Vector2D& vec2)
	{
		return vec1.x * vec2.x + vec1.y * vec2.y;
	}

	// ベクトルの向きをラジアン角で取得
	float VecDir(const Vector2D& vec)
	{
		return atan2f(vec.y, vec.x);
	}

};
