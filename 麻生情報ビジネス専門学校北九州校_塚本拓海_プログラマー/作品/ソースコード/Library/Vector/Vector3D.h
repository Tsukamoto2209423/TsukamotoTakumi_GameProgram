#pragma once

#include "DxLib.h"
#include <cmath>

//三次元の実数上のベクトルクラス
class Vector3D
{
public:
	//メンバ変数
	float x, y, z;

	constexpr Vector3D() noexcept : x(0.0f), y(0.0f), z(0.0f) {}
	explicit constexpr Vector3D(float initNum) noexcept : x(initNum), y(initNum), z(initNum) {}
	constexpr Vector3D(float init_x, float init_y,float init_z) noexcept : x(init_x), y(init_y), z(init_z) {}
	constexpr Vector3D(const Vector3D& vec) noexcept : x(vec.x), y(vec.y), z(vec.z) {}
	constexpr Vector3D(const VECTOR& vec) noexcept : x(vec.x), y(vec.y), z(vec.z) {}

	//引数に入力した値を取得する関数(x = value_x, y = value_y, z = value_z)
	constexpr Vector3D VGet(float value_x, float value_y, float value_z) {  return Vector3D(this->x = value_x, this->y = value_y, this->z = value_z); }
	//引数に入力した値を取得する関数(x = y = z = value)
	constexpr Vector3D VGet(float value) { return Vector3D(this->x = value, this->y = value, this->z = value); }
	//引数に入力した値を取得する関数(x = vec.x, y = vec.y, z = vec.z)
	constexpr Vector3D VGet(const Vector3D& vec) { return Vector3D(this->x = vec.x, this->y = vec.y, this->z = vec.z); }

	//Vector3Dの加算の定義
	constexpr Vector3D operator+(const Vector3D& vec) const { return Vector3D(this->x + vec.x, this->y + vec.y, this->z + vec.z); }

	//Vector3Dの加算代入の定義
	constexpr Vector3D operator+=(const Vector3D& vec) { return *this = *this + vec; }

	//Vector3Dの減算の定義
	constexpr Vector3D operator-(const Vector3D& vec) const { return Vector3D(this->x - vec.x, this->y - vec.y, this->z - vec.z); }

	//Vector3Dの減算代入の定義
	constexpr Vector3D operator-=(const Vector3D& vec) { return *this = *this - vec; }
	
	//外積の定義
	constexpr Vector3D operator*(const Vector3D& vec)
	{
		return { this->y * vec.z - this->z * vec.y,
			this->z * vec.x - this->x * vec.z,
			this->x * vec.y - this->y * vec.x };
	}

	//Vector3Dのスカラー倍の定義
	constexpr Vector3D operator*(int scale) const { return Vector3D(this->x * scale, this->y * scale, this->z * scale); }

	//Vector3Dのスカラー倍の定義
	constexpr Vector3D operator*(float scale) const { return Vector3D(this->x * scale, this->y * scale, this->z * scale); }

	//Vector3Dのスカラー倍代入の定義(int)
	constexpr Vector3D operator*=(int scale) { return *this = *this * scale; }

	//Vector3Dのスカラー倍代入の定義(float)
	constexpr Vector3D operator*=(float scale) { return *this = *this * scale; }

	//Vector3Dの代入の定義
	constexpr Vector3D& operator=(const Vector3D& vec) { this->x = vec.x; this->y = vec.y; this->z = vec.z; return *this; }
	constexpr Vector3D& operator=(float scale) { this->x = scale; this->y = scale; this->z = scale; return *this; }

	//同一ベクトル判定
	constexpr bool operator==(const Vector3D& vec) const { return (this->x == vec.x && this->y == vec.y && this->z == vec.z); }
	constexpr bool operator!=(const Vector3D& vec) const { return (this->x != vec.x && this->y != vec.y && this->z != vec.z); }

	constexpr bool operator>(const Vector3D& vec) const { return (this->x > vec.x && this->y > vec.y && this->z > vec.z); }

	constexpr bool operator<(const Vector3D& vec) const { return (this->x < vec.x && this->y < vec.y && this->z < vec.z); }

	constexpr bool operator>(float scale) const { return (this->x > scale && this->y > scale && this->z > scale); }

	constexpr bool operator<(float scale) const { return (this->x < scale && this->y < scale && this->z < scale); }

	//DXライブラリのベクトル構造体へのキャスト演算子
	constexpr operator VECTOR() const { return VECTOR{ x,y,z }; }

public:

	//始点と終点からベクトルを作成
	static constexpr Vector3D Create(const Vector3D& start, const Vector3D& end)
	{
		//終点 - 始点
		return Vector3D(end.x - start.x, end.y - start.y, end.z - start.z);
	}

	//ベクトルの大きさを取得(L2ノルム)
	static inline float L2Norm(const Vector3D& vec)
	{
		// ||vec||_2 = √(|vec.x|^2 + |vec.y|^2 + |vec.z|^2)
		return std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	}

	//ベクトルの大きさを取得(L2ノルム)
	// ||vec||_2 = √(|vec.x|^2 + |vec.y|^2 + |vec.z|^2)
	inline float L2Norm(void) const
	{
		return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
	}

	//二乗したベクトルの大きさを取得(L2ノルム)
	//(||vec||_2)^2 = |vec.x|^2 + |vec.y|^2 + |vec.z|^2
	inline float SquareL2Norm(void) const
	{
		return this->x * this->x + this->y * this->y + this->z * this->z;
	}

	//単位ベクトル作成
	inline Vector3D Normalize(const Vector3D& vec) const
	{
		Vector3D result;

		//ベクトルの大きさの逆数取得
		const float reciprocalVecNorm = 1 / L2Norm(vec);

		//各成分にスカラー倍して正規化したものを代入
		result = vec * reciprocalVecNorm;

		return result;
	}

	//単位ベクトル作成
	inline Vector3D& Normalize(void)
	{
		//ベクトルの大きさの逆数取得
		const float reciprocalVecNorm = 1 / this->L2Norm();

		//各成分にスカラー倍して正規化
		*this *= reciprocalVecNorm;

		return *this;
	}

	//単位ベクトルを作成しスカラー倍
	static Vector3D NormalizeAndScalartimes(const Vector3D& vec, float scale)
	{
		//スカラー倍したい値とベクトルの大きさの逆数の積を取得
		float scaleOverVecNorm = scale / L2Norm(vec);

		return { vec.x * scaleOverVecNorm, vec.y * scaleOverVecNorm, vec.z * scaleOverVecNorm };
	}

	//ベクトルを作成し単位ベクトルにしてスカラー倍
	static Vector3D NormalizeAndScalartimes(const Vector3D& start, const Vector3D& end, float scale)
	{
		Vector3D vec;

		//スカラー倍したい値とベクトルの大きさの逆数の積を取得
		float scaleOverVecNorm = scale / L2Norm(vec);

		//ベクトルを作成し単位ベクトルにしてスカラー倍
		vec.x = (end.x - start.x) * scaleOverVecNorm;
		vec.y = (end.y - start.y) * scaleOverVecNorm;
		vec.z = (end.z - start.z) * scaleOverVecNorm;

		return vec;
	}


	//逆ベクトルにする
	constexpr Vector3D& Inverse(void)
	{
		*this *= -1;
		return *this;
	}

	//外積
	static constexpr Vector3D Cross(const Vector3D& vec1, const Vector3D& vec2)
	{
		return { vec1.y * vec2.z - vec1.z * vec2.y,
			vec1.z * vec2.x - vec1.x * vec2.z,
			vec1.x * vec2.y - vec1.y * vec2.x };
	}

	// ベクトルの内積
	inline float Dot(const Vector3D& vec) const
	{
		return this->x * vec.x + this->y * vec.y + this->z * vec.z;
	}

	// ベクトルの内積
	static inline float Dot(const Vector3D& vec1, const Vector3D& vec2)
	{
		return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
	}

	// ベクトルの向きをラジアン角で取得
	inline float Dir(const Vector3D& vec)
	{
		return std::atan2(vec.x, vec.z) - DX_PI_F;
	}
};

//Vector3Dのスカラー倍の定義
inline Vector3D operator*(float scale, const Vector3D& vec) { return vec * scale; }

//Vector3Dの逆ベクトルの定義
constexpr Vector3D operator-(const Vector3D& vec) { return Vector3D(-vec.x, -vec.y, -vec.z); }
