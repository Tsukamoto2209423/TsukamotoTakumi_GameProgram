#pragma once

#include "DxLib.h"
#include <cmath>

//�񎟌��̎�����̃x�N�g���N���X
class Vector2D
{
public:
	//�����o�ϐ�
	float x, y;

	constexpr Vector2D() noexcept : x(0.0f), y(0.0f) {}
	explicit constexpr Vector2D(float initNum) noexcept : x(initNum), y(initNum) {}
	constexpr Vector2D(float init_x, float init_y) noexcept : x(init_x), y(init_y) {}
	constexpr Vector2D(const Vector2D& vec) noexcept : x(vec.x), y(vec.y) {}
	constexpr Vector2D(const VECTOR& vec) noexcept : x(vec.x), y(vec.y) {}

	//�����ɓ��͂����l���擾����֐�(x = value_x, y = value_y)
	inline constexpr Vector2D VGet(float value_x, float value_y) { this->x = value_x, this->y = value_y; return *this; }
	//�����ɓ��͂����l���擾����֐�(x = y = value)
	inline constexpr Vector2D VGet(float value) { this->x = value, this->y = value; return *this; }
	//�����ɓ��͂����l���擾����֐�(x = vec.x, y = vec.y)
	inline constexpr Vector2D VGet(const Vector2D& vec) { this->x = vec.x, this->y = vec.y; return *this; }

	//Vector2D�̉��Z�̒�`
	inline Vector2D operator+(const Vector2D& vec) const { this->x + vec.x, this->y + vec.y; return *this; }

	//Vector2D�̉��Z����̒�`
	inline Vector2D operator+=(const Vector2D& vec) { return *this = *this + vec; }

	//Vector2D�̌��Z�̒�`
	inline Vector2D operator-(const Vector2D& vec) const { this->x - vec.x, this->y - vec.y; return *this; }

	//Vector2D�̌��Z����̒�`
	inline Vector2D operator-=(const Vector2D& vec) { return *this = *this - vec; }

	//Vector2D�̃X�J���[�{�̒�`
	inline Vector2D operator*(float scale) const { return Vector2D(this->x * scale, this->y * scale); }

	inline Vector2D operator*(const Vector2D& vec) const { this->x* vec.x, this->y* vec.y; return *this; }

	//Vector2D�̃X�J���[�{����̒�`
	inline Vector2D operator*=(float scale) { return *this = *this * scale; }

	inline Vector2D operator*=(const Vector2D& vec) { return *this = *this * vec; }

	//Vector2D�̑���̒�`
	inline Vector2D operator=(const Vector2D& vec) { this->x = vec.x, this->y = vec.y; return *this; }

	//����x�N�g������
	inline bool operator==(const Vector2D& vec) const { return (x == vec.x && y == vec.y); }
	inline bool operator!=(const Vector2D& vec) const { return !(*this == vec); }

	//DX���C�u�����̃x�N�g���\���̂ւ̃L���X�g���Z�q
	inline operator VECTOR() const { return VECTOR{ x, y, 0.0f }; }

	// �n�_�ƏI�_����x�N�g�����쐬
	Vector2D VecCreate(const Vector2D& start, const Vector2D& end)
	{
		//�I�_ - �n�_
		return Vector2D(end.x - start.x, end.y - start.y);
	}

	// �x�N�g���̑����Z
	Vector2D VecAdd(const Vector2D& vec1, const Vector2D& vec2)
	{
		//�e���������Z
		return Vector2D(vec1.x + vec2.x, vec1.y + vec2.y);
	}

	//L2�m����
	inline float VecL2Norm(const Vector2D& vec)
	{
		// ||vec||_2 = ��(|vec.x|^2 + |vec.y|^2)
		return std::sqrt(vec.x * vec.x + vec.y * vec.y);
	}

	//�x�N�g���̑傫�����擾(L2�m����)
	// ||vec||_2 = ��(|vec.x|^2 + |vec.y|^2)
	inline float L2Norm() const
	{
		return std::sqrt(this->x * this->x + this->y * this->y);
	}

	//��悵���x�N�g���̑傫�����擾(L2�m����)
	//(||vec||_2)^2 = |vec.x|^2 + |vec.y|^2
	inline float SquareL2Norm() const
	{
		return this->x * this->x + this->y * this->y;
	}

	//�P�ʃx�N�g���쐬
	Vector2D Normalize(const Vector2D& vec)
	{
		Vector2D result;

		//�x�N�g���̒��������߂�
		float vec_norm = VecL2Norm(vec);

		//�e�����𒷂��Ŋ��萳�K������
		result.x = vec.x / vec_norm;
		result.y = vec.y / vec_norm;

		return result;
	}

	//�P�ʃx�N�g���쐬
	const Vector2D& Normalize()
	{
		//�x�N�g���̑傫���̋t���擾
		const float reciprocalVecNorm = 1 / this->L2Norm();

		//�e�����ɃX�J���[�{���Đ��K��
		*this *= reciprocalVecNorm;

		return *this;
	}

	//�P�ʃx�N�g�����쐬���X�J���[�{
	Vector2D VecNormalizeAndScalartimes(const Vector2D& vec, float scale)
	{
		float vec_norm = VecL2Norm(vec);

		return { (vec.x / vec_norm) * scale, (vec.y / vec_norm) * scale };
	}

	//�x�N�g�����쐬���P�ʃx�N�g���ɂ��ăX�J���[�{
	Vector2D VecNormalizeAndScalartimes(const Vector2D& start, const Vector2D& end, float scale)
	{
		Vector2D vec;

		vec.x = end.x - start.x;
		vec.y = end.y - start.y;

		float vec_norm = VecL2Norm(vec);

		return { (vec.x / vec_norm) * scale, (vec.y / vec_norm) * scale };
	}

	// �x�N�g���̃X�J���[�{
	Vector2D VecScalartimes(const Vector2D& vec, float scale)
	{
		//�e�������X�J���[�{
		return Vector2D(vec.x * scale, vec.y * scale);
	}

	// �x�N�g���̓���
	float VecDot(const Vector2D& vec1, const Vector2D& vec2)
	{
		return vec1.x * vec2.x + vec1.y * vec2.y;
	}

	// �x�N�g���̌��������W�A���p�Ŏ擾
	float VecDir(const Vector2D& vec)
	{
		return atan2f(vec.y, vec.x);
	}

};
