#pragma once

#include "DxLib.h"
#include <cmath>

//�O�����̎�����̃x�N�g���N���X
class Vector3D
{
public:
	//�����o�ϐ�
	float x, y, z;

	constexpr Vector3D() noexcept : x(0.0f), y(0.0f), z(0.0f) {}
	explicit constexpr Vector3D(float initNum) noexcept : x(initNum), y(initNum), z(initNum) {}
	constexpr Vector3D(float init_x, float init_y,float init_z) noexcept : x(init_x), y(init_y), z(init_z) {}
	constexpr Vector3D(const Vector3D& vec) noexcept : x(vec.x), y(vec.y), z(vec.z) {}
	constexpr Vector3D(const VECTOR& vec) noexcept : x(vec.x), y(vec.y), z(vec.z) {}

	//�����ɓ��͂����l���擾����֐�(x = value_x, y = value_y, z = value_z)
	constexpr Vector3D VGet(float value_x, float value_y, float value_z) {  return Vector3D(this->x = value_x, this->y = value_y, this->z = value_z); }
	//�����ɓ��͂����l���擾����֐�(x = y = z = value)
	constexpr Vector3D VGet(float value) { return Vector3D(this->x = value, this->y = value, this->z = value); }
	//�����ɓ��͂����l���擾����֐�(x = vec.x, y = vec.y, z = vec.z)
	constexpr Vector3D VGet(const Vector3D& vec) { return Vector3D(this->x = vec.x, this->y = vec.y, this->z = vec.z); }

	//Vector3D�̉��Z�̒�`
	constexpr Vector3D operator+(const Vector3D& vec) const { return Vector3D(this->x + vec.x, this->y + vec.y, this->z + vec.z); }

	//Vector3D�̉��Z����̒�`
	constexpr Vector3D operator+=(const Vector3D& vec) { return *this = *this + vec; }

	//Vector3D�̌��Z�̒�`
	constexpr Vector3D operator-(const Vector3D& vec) const { return Vector3D(this->x - vec.x, this->y - vec.y, this->z - vec.z); }

	//Vector3D�̌��Z����̒�`
	constexpr Vector3D operator-=(const Vector3D& vec) { return *this = *this - vec; }
	
	//�O�ς̒�`
	constexpr Vector3D operator*(const Vector3D& vec)
	{
		return { this->y * vec.z - this->z * vec.y,
			this->z * vec.x - this->x * vec.z,
			this->x * vec.y - this->y * vec.x };
	}

	//Vector3D�̃X�J���[�{�̒�`
	constexpr Vector3D operator*(int scale) const { return Vector3D(this->x * scale, this->y * scale, this->z * scale); }

	//Vector3D�̃X�J���[�{�̒�`
	constexpr Vector3D operator*(float scale) const { return Vector3D(this->x * scale, this->y * scale, this->z * scale); }

	//Vector3D�̃X�J���[�{����̒�`(int)
	constexpr Vector3D operator*=(int scale) { return *this = *this * scale; }

	//Vector3D�̃X�J���[�{����̒�`(float)
	constexpr Vector3D operator*=(float scale) { return *this = *this * scale; }

	//Vector3D�̑���̒�`
	constexpr Vector3D& operator=(const Vector3D& vec) { this->x = vec.x; this->y = vec.y; this->z = vec.z; return *this; }
	constexpr Vector3D& operator=(float scale) { this->x = scale; this->y = scale; this->z = scale; return *this; }

	//����x�N�g������
	constexpr bool operator==(const Vector3D& vec) const { return (this->x == vec.x && this->y == vec.y && this->z == vec.z); }
	constexpr bool operator!=(const Vector3D& vec) const { return (this->x != vec.x && this->y != vec.y && this->z != vec.z); }

	constexpr bool operator>(const Vector3D& vec) const { return (this->x > vec.x && this->y > vec.y && this->z > vec.z); }

	constexpr bool operator<(const Vector3D& vec) const { return (this->x < vec.x && this->y < vec.y && this->z < vec.z); }

	constexpr bool operator>(float scale) const { return (this->x > scale && this->y > scale && this->z > scale); }

	constexpr bool operator<(float scale) const { return (this->x < scale && this->y < scale && this->z < scale); }

	//DX���C�u�����̃x�N�g���\���̂ւ̃L���X�g���Z�q
	constexpr operator VECTOR() const { return VECTOR{ x,y,z }; }

public:

	//�n�_�ƏI�_����x�N�g�����쐬
	static constexpr Vector3D Create(const Vector3D& start, const Vector3D& end)
	{
		//�I�_ - �n�_
		return Vector3D(end.x - start.x, end.y - start.y, end.z - start.z);
	}

	//�x�N�g���̑傫�����擾(L2�m����)
	static inline float L2Norm(const Vector3D& vec)
	{
		// ||vec||_2 = ��(|vec.x|^2 + |vec.y|^2 + |vec.z|^2)
		return std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	}

	//�x�N�g���̑傫�����擾(L2�m����)
	// ||vec||_2 = ��(|vec.x|^2 + |vec.y|^2 + |vec.z|^2)
	inline float L2Norm(void) const
	{
		return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
	}

	//��悵���x�N�g���̑傫�����擾(L2�m����)
	//(||vec||_2)^2 = |vec.x|^2 + |vec.y|^2 + |vec.z|^2
	inline float SquareL2Norm(void) const
	{
		return this->x * this->x + this->y * this->y + this->z * this->z;
	}

	//�P�ʃx�N�g���쐬
	inline Vector3D Normalize(const Vector3D& vec) const
	{
		Vector3D result;

		//�x�N�g���̑傫���̋t���擾
		const float reciprocalVecNorm = 1 / L2Norm(vec);

		//�e�����ɃX�J���[�{���Đ��K���������̂���
		result = vec * reciprocalVecNorm;

		return result;
	}

	//�P�ʃx�N�g���쐬
	inline Vector3D& Normalize(void)
	{
		//�x�N�g���̑傫���̋t���擾
		const float reciprocalVecNorm = 1 / this->L2Norm();

		//�e�����ɃX�J���[�{���Đ��K��
		*this *= reciprocalVecNorm;

		return *this;
	}

	//�P�ʃx�N�g�����쐬���X�J���[�{
	static Vector3D NormalizeAndScalartimes(const Vector3D& vec, float scale)
	{
		//�X�J���[�{�������l�ƃx�N�g���̑傫���̋t���̐ς��擾
		float scaleOverVecNorm = scale / L2Norm(vec);

		return { vec.x * scaleOverVecNorm, vec.y * scaleOverVecNorm, vec.z * scaleOverVecNorm };
	}

	//�x�N�g�����쐬���P�ʃx�N�g���ɂ��ăX�J���[�{
	static Vector3D NormalizeAndScalartimes(const Vector3D& start, const Vector3D& end, float scale)
	{
		Vector3D vec;

		//�X�J���[�{�������l�ƃx�N�g���̑傫���̋t���̐ς��擾
		float scaleOverVecNorm = scale / L2Norm(vec);

		//�x�N�g�����쐬���P�ʃx�N�g���ɂ��ăX�J���[�{
		vec.x = (end.x - start.x) * scaleOverVecNorm;
		vec.y = (end.y - start.y) * scaleOverVecNorm;
		vec.z = (end.z - start.z) * scaleOverVecNorm;

		return vec;
	}


	//�t�x�N�g���ɂ���
	constexpr Vector3D& Inverse(void)
	{
		*this *= -1;
		return *this;
	}

	//�O��
	static constexpr Vector3D Cross(const Vector3D& vec1, const Vector3D& vec2)
	{
		return { vec1.y * vec2.z - vec1.z * vec2.y,
			vec1.z * vec2.x - vec1.x * vec2.z,
			vec1.x * vec2.y - vec1.y * vec2.x };
	}

	// �x�N�g���̓���
	inline float Dot(const Vector3D& vec) const
	{
		return this->x * vec.x + this->y * vec.y + this->z * vec.z;
	}

	// �x�N�g���̓���
	static inline float Dot(const Vector3D& vec1, const Vector3D& vec2)
	{
		return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
	}

	// �x�N�g���̌��������W�A���p�Ŏ擾
	inline float Dir(const Vector3D& vec)
	{
		return std::atan2(vec.x, vec.z) - DX_PI_F;
	}
};

//Vector3D�̃X�J���[�{�̒�`
inline Vector3D operator*(float scale, const Vector3D& vec) { return vec * scale; }

//Vector3D�̋t�x�N�g���̒�`
constexpr Vector3D operator-(const Vector3D& vec) { return Vector3D(-vec.x, -vec.y, -vec.z); }
