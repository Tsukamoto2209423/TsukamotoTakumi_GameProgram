#pragma once

#include <cmath>
#include "Vector/Vector3D.h"

namespace
{
	//Matrix3D�̍s�̍ő吔
	constexpr int ROW_MAX_NUM_3D = 4;

	//Matrix3D�̗�̍ő吔
	constexpr int COLUMN_MAX_NUM_3D = 4;

	//Matrix3D�̍s�Ɨ�̍ő吔
	constexpr int ROW_COLUMN_MAX_NUM_3D = 4;

	//Matrix3D�̍s��̐����̍ő吔
	constexpr int ENTRY_COMPONENT_MAX_NUM = 16;
}

//�O�����p�̍s��N���X
class Matrix3D
{
public:
	/*
		���l�������s��
		�����������邽�߂Ɉꎟ���z��ɂ��Ă��܂�
	*/
	float m[ENTRY_COMPONENT_MAX_NUM];

public:
	// �R���X�g���N�^
	Matrix3D()
		: m()
	{}

	explicit constexpr Matrix3D(float init) noexcept
	{
		m[0] = init; m[1] = init; m[2] = init; m[3] = init;
		m[4] = init; m[5] = init; m[6] = init; m[7] = init;
		m[8] = init; m[9] = init; m[10] = init; m[11] = init;
		m[12] = init; m[13] = init; m[14] = init; m[15] = init;
	}


public:
	/**
	@param	�P�ʍs��擾
	@return	|  1  0  0  0  |
	@return	|  0  1  0  0  |
	@return	|  0  0  1  0  |
	@return	|  0  0  0  1  | 
	*/
	static Matrix3D GetIdentityMatrix(void) 
	{ 
		Matrix3D resultMat(0.0f);

		resultMat.m[0] = 1.0f;	resultMat.m[5] = 1.0f;	resultMat.m[10] = 1.0f;	resultMat.m[15] = 1.0f;

		return resultMat;
	}


	/// <summary>
	/// ���s�ړ��s��擾(float)
	/// </summary>
	/// <param name="movingValueX"></param>
	/// <param name="movingValueY"></param>
	/// <param name="movingValueZ"></param>
	/// @return	|  1  0  0  x  |
	/// @return	|  0  1  0  y  |
	/// @return	|  0  0  1  z  |
	/// @return	|  0  0  0  1  |
	static Matrix3D GetTranslateMatrix(float movingValueX, float movingValueY, float movingValueZ)
	{
		Matrix3D resultMat = GetIdentityMatrix();

		resultMat.m[3] = movingValueX; resultMat.m[7] = movingValueY; resultMat.m[11] = movingValueZ;

		return resultMat;
	}


	///**
	// @param	���s�ړ��s��擾(Vector3D)
	// @return	|  1  0  0  x  |
	// @return	|  0  1  0  y  |
	// @return	|  0  0  1  z  |
	// @return	|  0  0  0  1  |
	//*/
	static Matrix3D GetTranslateMatrix(const Vector3D& vec)
	{
		Matrix3D resultMat = GetIdentityMatrix();

		resultMat.m[3] = vec.x; resultMat.m[7] = vec.y; resultMat.m[11] = vec.z;

		return resultMat;
	}


	/*
		�g�k�s��擾(float)
		| Sx  0   0  0 |
		| 0	  Sy  0  0 |
		| 0   0  Sz  0 |
		| 0   0   0  1 |
	*/
	static Matrix3D GetScaleMatrix(float scalingX, float scalingY, float scalingZ)
	{
		Matrix3D resultMat = GetIdentityMatrix();

		resultMat.m[0] = scalingX;	resultMat.m[5] = scalingY;	resultMat.m[10] = scalingZ;

		return resultMat;
	}


	/*
		�g�k�s��擾(Vector3D)
		| Sx  0   0   0 |
		| 0	  Sy  0   0 |
		| 0   0   Sz  0 |
		| 0   0   0   1 |
	*/
	inline static Matrix3D GetScaleMatrix(const Vector3D& scalingVec)
	{
		Matrix3D resultMat = GetIdentityMatrix();

		resultMat.m[0] = scalingVec.x;	resultMat.m[5] = scalingVec.y;	resultMat.m[10] = scalingVec.z;

		return resultMat;
	}


	/*
		X����]�s��擾
		|  1     0      0      0  |
		|  0   cos��  -sin��   0  |
		|  0   sin��   cos��   0  |
		|  0     0      0      1  |
	*/
	static Matrix3D GetPitchMatrix(float rotationValue)
	{
		Matrix3D pitchMat = GetIdentityMatrix();

		pitchMat.m[5] = std::cos(rotationValue); pitchMat.m[6] = -std::sin(rotationValue); pitchMat.m[9] = std::sin(rotationValue); pitchMat.m[10] = std::cos(rotationValue);
		
		return pitchMat;
	}


	/*
		Y����]�s��擾
		| cos��   0    sin��   0  |
		|  0      1     0      0  |
		| -sin��  0    cos��   0  |
		|  0      0     0      1  |
	*/
	static Matrix3D GetYawMatrix(float rotationValue)
	{
		Matrix3D yawMat = GetIdentityMatrix();
		yawMat.m[0] = std::cos(rotationValue); yawMat.m[2] = std::sin(rotationValue); yawMat.m[8] = -std::sin(rotationValue); yawMat.m[10] = std::cos(rotationValue);
		return yawMat;
	}


	/*
		Z����]�s��擾
		|  cos��  -sin��  0    0  |
		|  sin��   cos��  0    0  |
		|    0      0     1    0  |
		|    0      0     0    1  |
	*/
	static Matrix3D GetRollMatrix(float rotationValue)
	{
		Matrix3D rollMat = GetIdentityMatrix();

		rollMat.m[0] = std::cos(rotationValue); rollMat.m[1] = -std::sin(rotationValue); rollMat.m[4] = std::sin(rotationValue); rollMat.m[5] = std::cos(rotationValue);
		
		return rollMat;
	}

public:
	//���@�A���@�A��@�A�]�u

	//Matrix3D�̉��@�̒�`
	inline Matrix3D operator+ (const Matrix3D& mat)
	{
		Matrix3D resultMat(0.0f);

		//�e�����̘a
		resultMat.m[0] = m[0] + mat.m[0];	resultMat.m[1] = m[1] + mat.m[1];	resultMat.m[2] = m[2] + mat.m[2];	resultMat.m[3] = m[3] + mat.m[3];
		resultMat.m[4] = m[4] + mat.m[4];	resultMat.m[5] = m[5] + mat.m[5];	resultMat.m[6] = m[6] + mat.m[6];	resultMat.m[7] = m[7] + mat.m[7];
		resultMat.m[8] = m[8] + mat.m[8];	resultMat.m[9] = m[9] + mat.m[9];	resultMat.m[10] = m[10] + mat.m[10];	resultMat.m[11] = m[11] + mat.m[11];
		resultMat.m[12] = m[12] + mat.m[12];	resultMat.m[13] = m[13] + mat.m[13];	resultMat.m[14] = m[14] + mat.m[14];	resultMat.m[15] = m[15] + mat.m[15];
		
		return resultMat;
	}

	//Matrix3D�̉��@����̒�`
	inline Matrix3D operator+= (const Matrix3D& mat)
	{
		return *this = *this + mat;
	}

	//Matrix3D�̌��@�̒�`
	inline Matrix3D operator- (const Matrix3D& mat)
	{
		Matrix3D resultMat(0.0f);

		//�e�����̍�
		resultMat.m[0] = m[0] - mat.m[0];	resultMat.m[1] = m[1] - mat.m[1];	resultMat.m[2] = m[2] - mat.m[2];	resultMat.m[3] = m[3] - mat.m[3];
		resultMat.m[4] = m[4] - mat.m[4];	resultMat.m[5] = m[5] - mat.m[5];	resultMat.m[6] = m[6] - mat.m[6];	resultMat.m[7] = m[7] - mat.m[7];
		resultMat.m[8] = m[8] - mat.m[8];	resultMat.m[9] = m[9] - mat.m[9];	resultMat.m[10] = m[10] - mat.m[10];	resultMat.m[11] = m[11] - mat.m[11];
		resultMat.m[12] = m[12] - mat.m[12];	resultMat.m[13] = m[13] - mat.m[13];	resultMat.m[14] = m[14] - mat.m[14];	resultMat.m[15] = m[15] - mat.m[15];

		return resultMat;
	}

	//Matrix3D�̃}�C�i�X���̒�`
	inline Matrix3D operator- ()
	{
		Matrix3D resultMat(0.0f);

		//�e������-1���|�������̂���
		resultMat.m[0] = -m[0];	resultMat.m[1] = -m[1];	resultMat.m[2] = -m[2];	resultMat.m[3] = -m[3];
		resultMat.m[4] = -m[4];	resultMat.m[5] = -m[5];	resultMat.m[6] = -m[6];	resultMat.m[7] = -m[7];
		resultMat.m[8] = -m[8];	resultMat.m[9] = -m[9];	resultMat.m[10] = -m[10];resultMat.m[11] = -m[11];
		resultMat.m[12] = -m[12];resultMat.m[13] = -m[13];resultMat.m[14] = -m[14];resultMat.m[15] = -m[15];

		return resultMat;
	}

	//Matrix3D�̌��@����̒�`
	inline Matrix3D operator-= (const Matrix3D& mat)
	{
		return *this = *this - mat;
	}

	//Matrix3D�̃X�J���[�{�̒�`(int)
	inline Matrix3D operator* (const int iNum)
	{
		Matrix3D resultMat(0.0f);

		//�e�����̐�
		resultMat.m[0] = m[0] * iNum;	resultMat.m[1] = m[1] * iNum;	resultMat.m[2] = m[2] * iNum;	resultMat.m[3] = m[3] * iNum;
		resultMat.m[4] = m[4] * iNum;	resultMat.m[5] = m[5] * iNum;	resultMat.m[6] = m[6] * iNum;	resultMat.m[7] = m[7] * iNum;
		resultMat.m[8] = m[8] * iNum;	resultMat.m[9] = m[9] * iNum;	resultMat.m[10] = m[10] * iNum;	resultMat.m[11] = m[11] * iNum;
		resultMat.m[12] = m[12] * iNum;	resultMat.m[13] = m[13] * iNum;	resultMat.m[14] = m[14] * iNum;	resultMat.m[15] = m[15] * iNum;

		return resultMat;
	}

	//Matrix3D�̃X�J���[�{�̒�`(float)
	inline Matrix3D operator* (const float fNum)
	{
		Matrix3D resultMat(0.0f);

		//�e�����̐�
		resultMat.m[0] = m[0] * fNum;	resultMat.m[1] = m[1] * fNum;	resultMat.m[2] = m[2] * fNum;	resultMat.m[3] = m[3] * fNum;
		resultMat.m[4] = m[4] * fNum;	resultMat.m[5] = m[5] * fNum;	resultMat.m[6] = m[6] * fNum;	resultMat.m[7] = m[7] * fNum;
		resultMat.m[8] = m[8] * fNum;	resultMat.m[9] = m[9] * fNum;	resultMat.m[10] = m[10] * fNum;	resultMat.m[11] = m[11] * fNum;
		resultMat.m[12] = m[12] * fNum;	resultMat.m[13] = m[13] * fNum;	resultMat.m[14] = m[14] * fNum;	resultMat.m[15] = m[15] * fNum;

		return resultMat;
	}

	//Matrix3D�̏�@�̒�`(Vector3D)
	inline Vector3D operator* (const Vector3D& vec)
	{
		Vector3D resultVec(0.0f);

		resultVec.x = (m[0] * vec.x) + (m[1] * vec.y) + (m[2] * vec.z) + m[3];
		resultVec.y = (m[4] * vec.x) + (m[5] * vec.y) + (m[6] * vec.z) + m[7];
		resultVec.z = (m[8] * vec.x) + (m[9] * vec.y) + (m[10] * vec.z) + m[11];
		
		return resultVec;
	}

	//Vector3D��Matrix3D�̐ς̒�`
	constexpr Vector3D operator*=(const Vector3D& vec)
	{
		return Vector3D((vec.x * m[0]) + (vec.y * m[1]) + (vec.z * m[2]) + m[3],
			(vec.x * m[4]) + (vec.y * m[5]) + (vec.z * m[6]) + m[7],
			(vec.x * m[8]) + (vec.y * m[9]) + (vec.z * m[10]) + m[11]);
	}

	//Matrix3D�̏�@�̒�`(Matrix3D)
	//�s�񓯎m�̐ς͔���ł���
	inline Matrix3D operator* (const Matrix3D& mat)
	{
		Matrix3D resultMat(0.0f);

		for (int i = 0; i < 4; i++) 
		{
			resultMat.m[i] += m[0] * mat.m[i];
			resultMat.m[i] += m[1] * mat.m[4 + i];
			resultMat.m[i] += m[2] * mat.m[8 + i];
			resultMat.m[i] += m[3] * mat.m[12 + i];

			resultMat.m[4 + i] += m[4] * mat.m[i];
			resultMat.m[4 + i] += m[5] * mat.m[4 + i];
			resultMat.m[4 + i] += m[6] * mat.m[8 + i];
			resultMat.m[4 + i] += m[7] * mat.m[12 + i];

			resultMat.m[8 + i] += m[8] * mat.m[i];
			resultMat.m[8 + i] += m[9] * mat.m[4 + i];
			resultMat.m[8 + i] += m[10] * mat.m[8 + i];
			resultMat.m[8 + i] += m[11] * mat.m[12 + i];

			resultMat.m[12 + i] += m[12] * mat.m[i];
			resultMat.m[12 + i] += m[13] * mat.m[4 + i];
			resultMat.m[12 + i] += m[14] * mat.m[8 + i];
			resultMat.m[12 + i] += m[15] * mat.m[12 + i];
		}

		return resultMat;
	}

	//Matrix3D�̃X�J���[�{����̒�`(int)
	constexpr Matrix3D& operator*= (int iNum)
	{
		return *this = *this * iNum;
	}

	//Matrix3D�̃X�J���[�{����̒�`(float)
	constexpr Matrix3D& operator*= (float fNum)
	{
		return *this = *this * fNum;
	}

	//Matrix3D�̏�@����̒�`(Matrix3D)
	//�s�񓯎m�̐ς͔���ł���
	constexpr Matrix3D& operator*= (const Matrix3D& mat)
	{
		return *this = *this * mat;
	}

	//Matrix3D�̑���̒�`
	constexpr Matrix3D& operator=(const Matrix3D& mat)
	{
		//�e��������
		m[0] = mat.m[0];	m[1] = mat.m[1];	m[2] = mat.m[2];	m[3] = mat.m[3];
		m[4] = mat.m[4];	m[5] = mat.m[5];	m[6] = mat.m[6];	m[7] = mat.m[7];
		m[8] = mat.m[8];	m[9] = mat.m[9];	m[10] = mat.m[10];	m[11] = mat.m[11];
		m[12] = mat.m[12];	m[13] = mat.m[13];	m[14] = mat.m[14];	m[15] = mat.m[15];

		return *this;
	}

	constexpr float& operator[](int index)
	{
		return m[index];
	}
};

//Vector3D��Matrix3D�̐ς̒�`
constexpr Vector3D operator*(const Vector3D& vec, const Matrix3D& mat)
{
	return Vector3D((vec.x * mat.m[0]) + (vec.y * mat.m[1]) + (vec.z * mat.m[2]) + mat.m[3],
		(vec.x * mat.m[4]) + (vec.y * mat.m[5]) + (vec.z * mat.m[6]) + mat.m[7],
		(vec.x * mat.m[8]) + (vec.y * mat.m[9]) + (vec.z * mat.m[10]) + mat.m[11]);
}

//Vector3D��Matrix3D�̐ς̒�`
constexpr Vector3D operator*=(Vector3D& vec, const Matrix3D& mat)
{
	return vec = { (vec.x * mat.m[0]) + (vec.y * mat.m[1]) + (vec.z * mat.m[2]) + mat.m[3],
		(vec.x * mat.m[4]) + (vec.y * mat.m[5]) + (vec.z * mat.m[6]) + mat.m[7],
		(vec.x * mat.m[8]) + (vec.y * mat.m[9]) + (vec.z * mat.m[10]) + mat.m[11] };
}

