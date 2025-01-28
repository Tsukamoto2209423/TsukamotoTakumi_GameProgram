#pragma once

#include "Vector/Vector2D.h"
#include "Vector/Vector3D.h"

//���w�֐�
namespace MyMath
{
	//2��
	constexpr float TWO_PI = 6.283185307179586476925286766559f;

	//��
	constexpr float PI = 3.1415926535897932384626433832795f;

	//1/(2��)
	constexpr float INVERSE_TWO_PI = 1.0f / TWO_PI;

	//1/��
	constexpr float INVERSE_PI = 1.0f / PI;

	//�[���x�N�g��
	constexpr Vector2D ZERO_VECTOR_2D = { 0.0f,0.0f };

	//�[���x�N�g��
	constexpr Vector3D ZERO_VECTOR_3D = { 0.0f,0.0f,0.0f };

	//4��/3
	constexpr float FOUR_PI_OVER_THREE = 1.3333333333333333333333333333333f * PI;

	//��/2
	constexpr float HALF_PI = 0.5f * PI;

	//��/3
	constexpr float PI_OVER_THREE = 0.3333333333333333333333333333333f * PI;

	//��/4
	constexpr float PI_OVER_FOUR = 0.25f * PI;

	//��/6
	constexpr float PI_OVER_SIX = 0.1666666666666666666666666666666f * PI;

	//��/8
	constexpr float PI_OVER_EIGHT = 0.125f * PI;

	//��/10
	constexpr float PI_OVER_TEN = 0.1f * PI;

	//��/20
	constexpr float PI_OVER_TWENTY = 0.05f * PI;

	//���W�A���p�ɕϊ�����Ƃ��Ɏg���萔
	constexpr float RADIAN_CONVERT_COEFFICIENT = PI / 180.0f;


	template<class T>
	constexpr inline T Abs(const T num)
	{
		return num >= static_cast<T>(0) ? num : -num;
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

	//�f�B�O���[�p���烉�W�A���p�ɂ���
	template<class T>
	constexpr inline float DegreesToRadian(const T degrees)
	{
		return static_cast<float>(degrees * MyMath::RADIAN_CONVERT_COEFFICIENT);
	}
};
