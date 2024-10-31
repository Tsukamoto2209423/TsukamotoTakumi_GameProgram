#pragma once

#include "Vector/Vector2D.h"
#include "Vector/Vector3D.h"

//数学で使う定数
namespace MY_MATH
{
	//2π
	constexpr float TWO_PI = 6.283185307179586476925286766559f;

	//π
	constexpr float PI = 3.1415926535897932384626433832795f;

	//1/(2π)
	constexpr float INVERSE_TWO_PI = 1.0f / TWO_PI;

	//1/π
	constexpr float INVERSE_PI = 1.0f / PI;

	//ゼロベクトル
	constexpr Vector2D ZERO_VECTOR_2D = { 0.0f,0.0f };

	//ゼロベクトル
	constexpr Vector3D ZERO_VECTOR_3D = { 0.0f,0.0f,0.0f };

	//4π/3
	constexpr float FOUR_PI_OVER_THREE = 1.3333333333333333333333333333333f * PI;

	//π/2
	constexpr float HALF_PI = 0.5f * PI;

	//π/3
	constexpr float PI_OVER_THREE = 0.3333333333333333333333333333333f * PI;

	//π/4
	constexpr float PI_OVER_FOUR = 0.25f * PI;

	//π/6
	constexpr float PI_OVER_SIX = 0.1666666666666666666666666666666f * PI;

	//π/8
	constexpr float PI_OVER_EIGHT = 0.125f * PI;

	//π/10
	constexpr float PI_OVER_TEN = 0.1f * PI;

	//π/20
	constexpr float PI_OVER_TWENTY = 0.05f * PI;

	//ラジアン角に変換するときに使う定数
	constexpr float RADIAN_CONVERT_COEFFICIENT = PI / 180.0f;
}

//数学関数
namespace MyMath
{
	template<class T>
	constexpr inline T Abs(const T num)
	{
		return num >= (T)0 ? num : -num;
	}

	template<class T>
	constexpr inline T Max(const T num1, const T num2)
	{
		return num1 >= num2 ? num1 : num2;
	}

	template<class T>
	constexpr inline T Min(const T num1, const T num2)
	{
		return num1 <= num2 ? num1 : num2;
	}

	//ディグリー角からラジアン角にする
	template<class T>
	constexpr inline float DegreesToRadian(const T degrees)
	{
		return static_cast<float>(degrees * MY_MATH::RADIAN_CONVERT_COEFFICIENT);
	}
};
