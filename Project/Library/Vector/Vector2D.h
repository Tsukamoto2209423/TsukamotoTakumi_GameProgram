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

	//Vector2Dの除算の定義
	inline Vector2D operator/(const Vector2D& vec) const { this->x / vec.x, this->y / vec.y; return *this; }

	//Vector2Dの除算代入の定義
	inline Vector2D operator/=(const Vector2D& vec) { return *this = *this / vec; }

	//Vector2Dの代入の定義
	inline Vector2D operator=(const Vector2D& vec) { this->x = vec.x, this->y = vec.y; return *this; }

	//同一ベクトル判定
	inline bool operator==(const Vector2D& vec) const { return (x == vec.x && y == vec.y); }
	inline bool operator!=(const Vector2D& vec) const { return !(*this == vec); }

	//DXライブラリのベクトル構造体へのキャスト演算子
	inline operator VECTOR() const { return VECTOR{ (float)x,(float)y,0.0f }; }

	//始点終点ベクトル作成
	Vector2D VecCreate(const Vector2D& start, const Vector2D& end);

	//ベクトル和
	Vector2D VecAdd(const Vector2D& vec1, const Vector2D& vec2);

	//L2ノルム
	inline float VecL2Norm(const Vector2D& vec);

	//単位ベクトル作成
	Vector2D Normalize(const Vector2D& vec);

	//単位ベクトルを作成しスカラー倍
	Vector2D VecNormalizeAndScalartimes(const Vector2D& vec, float scale);

	//ベクトルを作成し単位ベクトルにしてスカラー倍
	Vector2D VecNormalizeAndScalartimes(const Vector2D& start, const Vector2D& end, float scale);

	//ベクトルのスカラー倍
	Vector2D VecScalartimes(const Vector2D& vec, float scale);

	//内積
	inline float VecDot(const Vector2D& vec1, const Vector2D& vec2);

	//ベクトルの角度θを取得
	inline float VecDir(const Vector2D& vec);
};
