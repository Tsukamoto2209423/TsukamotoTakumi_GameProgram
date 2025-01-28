#pragma once

#include <math.h>
#include "Vector/Vector2D.h"
#include "Vector/Vector3D.h"


//Matrix2D�̍s�̍ő吔
constexpr int ROW_MAX_NUM_2D = 4;

//Matrix2D�̗�̍ő吔
constexpr int COLUMN_MAX_NUM_2D = 4;

//Matrix2D�̍s�Ɨ�̍ő吔
constexpr int ROW_COLUMN_MAX_NUM_2D = 4;


class Matrix2D
{
public:
	//���l�������s��
	float m[ROW_MAX_NUM_2D][COLUMN_MAX_NUM_2D];


public:
	//��s��
	inline static constexpr Matrix2D ZERO_MATRIX() { return { 0.0f }; }

	//�P�ʍs��
	inline static constexpr Matrix2D IDENTITY_MATRIX()
	{
		return { 1.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,
		0.0f,0.0f,1.0f};
	}

	//���s�ړ��s��(float)
	inline static constexpr Matrix2D TRANSLATE_MATRIX(float movingValueX, float movingValueY)
	{
		return { 1.0f,0.0f,movingValueX,
				 0.0f,1.0f,movingValueY,
				 0.0f,0.0f,1.0f };
	}

	//���s�ړ��s��(Vector3D)
	inline static constexpr Matrix2D GetTranslateMatrix(const Vector3D& vec)
	{
		return { 1,0,vec.x,
				 0,1,vec.y,
				 0,0,vec.z };
	}

	//�g�k�s��(float)
	inline static constexpr Matrix2D GetScaleMatrix(float scalingX, float scalingY)
	{
		return { scalingX,0,0,
				 0,scalingY,0,
				 0, 0, 1 };
	}

	//�g�k�s��(Vector3D)
	inline static constexpr Matrix2D GetScaleMatrix(const Vector3D& scalingVec)
	{
		return { scalingVec.x,0,0,
				 0,scalingVec.y,0,
				 0,0,1 };
	}

	//��]�s��
	inline Matrix2D GetRotMatrix(float rotationValue)
	{
		return { cosf(rotationValue),-sinf(rotationValue),0,
				 sinf(rotationValue),cosf(rotationValue),0,
				 0,0,1 };
	}

public:
	//���@�A���@�A��@�A�]�u

	//Matrix2D�̉��@�̒�`
	inline Matrix2D operator+ (const Matrix2D& mat)
	{
		Matrix2D resultMat{};

		for (int row = 0; row < ROW_MAX_NUM_2D; ++row)
		{
			for (int column = 0; column < COLUMN_MAX_NUM_2D; ++column)
			{
				resultMat.m[row][column] = this->m[row][column] + mat.m[row][column];
			}
		}

		return resultMat;
	}

	//Matrix2D�̉��@����̒�`
	inline Matrix2D operator+= (const Matrix2D& mat)
	{
		for (int row = 0; row < ROW_MAX_NUM_2D; ++row)
		{
			for (int column = 0; column < COLUMN_MAX_NUM_2D; ++column)
			{
				this->m[row][column] = this->m[row][column] + mat.m[row][column];
			}
		}

		return *this;
	}

	//Matrix2D�̌��@�̒�`
	inline Matrix2D operator- (const Matrix2D& mat)
	{
		Matrix2D resultMat{};

		for (int row = 0; row < ROW_MAX_NUM_2D; ++row)
		{
			for (int column = 0; column < COLUMN_MAX_NUM_2D; ++column)
			{
				resultMat.m[row][column] = this->m[row][column] - mat.m[row][column];
			}
		}

		return resultMat;
	}

	//Matrix2D�̌��@����̒�`
	inline Matrix2D operator-= (const Matrix2D& mat)
	{
		for (int row = 0; row < ROW_MAX_NUM_2D; ++row)
		{
			for (int column = 0; column < COLUMN_MAX_NUM_2D; ++column)
			{
				this->m[row][column] = this->m[row][column] - mat.m[row][column];
			}
		}

		return *this;
	}

	//Matrix2D�̃X�J���[�{�̒�`(int)
	inline Matrix2D operator* (int iScalarNum)
	{
		Matrix2D resultMat{};

		for (int row = 0; row < ROW_MAX_NUM_2D; ++row)
		{
			for (int column = 0; column < COLUMN_MAX_NUM_2D; ++column)
			{
				resultMat.m[row][column] = this->m[row][column] * iScalarNum;
			}
		}

		return resultMat;
	}

	//Matrix2D�̃X�J���[�{�̒�`(float)
	inline Matrix2D operator* (float fScalarNum)
	{
		Matrix2D resultMat{};

		for (int row = 0; row < ROW_MAX_NUM_2D; ++row)
		{
			for (int column = 0; column < COLUMN_MAX_NUM_2D; ++column)
			{
				resultMat.m[row][column] = this->m[row][column] * fScalarNum;
			}
		}

		return resultMat;
	}

	//Matrix2D�̃X�J���[�{����̒�`(int)
	inline Matrix2D operator*= (int iScalarNum)
	{
		for (int row = 0; row < ROW_MAX_NUM_2D; ++row)
		{
			for (int column = 0; column < COLUMN_MAX_NUM_2D; ++column)
			{
				this->m[row][column] = this->m[row][column] * iScalarNum;
			}
		}

		return *this;
	}

	//Matrix2D�̃X�J���[�{����̒�`(float)
	inline Matrix2D operator*= (float fScalarNum)
	{
		for (int row = 0; row < ROW_MAX_NUM_2D; ++row)
		{
			for (int column = 0; column < COLUMN_MAX_NUM_2D; ++column)
			{
				this->m[row][column] = this->m[row][column] * fScalarNum;
			}
		}

		return *this;
	}

	//Matrix2D�̏�@�̒�`(Matrix2D)
	//�s�񓯎m�̐ς͔���ł���
	inline Matrix2D operator* (const Matrix2D& mat)
	{
		Matrix2D retMat{};

		for (int row = 0; row < ROW_MAX_NUM_2D; row++)
		{
			for (int column = 0; column < COLUMN_MAX_NUM_2D; column++)
			{
				for (int index = 0; index < ROW_COLUMN_MAX_NUM_2D; index++)
				{
					retMat.m[row][column] += this->m[row][index] * mat.m[index][column];
				}
			}
		}
		return retMat;
	}

	//Matrix2D�̏�@����̒�`(Matrix2D)
	//�s�񓯎m�̐ς͔���ł���
	inline Matrix2D operator*= (const Matrix2D& mat)
	{
		return *this = *this * mat;
	}

	//Matrix2D�̏�@�̒�`(Vector2D)
	inline Matrix2D operator* (const Vector3D& vec)
	{
		Matrix2D retMat{};

		float vecMat[4] = { vec.x,vec.y,vec.z,1.0f };
		for (int index1 = 0; index1 < ROW_MAX_NUM_2D; index1++)
		{
			for (int index2 = 0; index2 < COLUMN_MAX_NUM_2D; index2++)
			{
				retMat.m[index1][index2] = this->m[index1][index2] * vecMat[index2];
			}
		}
		return retMat;
	}

	//Matrix2D�̏�@����̒�`(Vector2D)
	inline Matrix2D operator*= (const Vector3D& vec)
	{
		float vecMat[4] = { vec.x,vec.y,vec.z,1.0f };
		for (int index1 = 0; index1 < ROW_MAX_NUM_2D; index1++)
		{
			for (int index2 = 0; index2 < COLUMN_MAX_NUM_2D; index2++)
			{
				this->m[index1][index2] = this->m[index1][index2] * vecMat[index2];
			}
		}
		return *this;
	}

	//Matrix2D�̓]�u�̒�`
	inline Matrix2D operator/ (const Matrix2D& mat)
	{
		for (int column = 0; column < ROW_MAX_NUM_2D; column++)
		{
			for (int row = 0; row < COLUMN_MAX_NUM_2D; row++)
			{
				//�e������Ίp�����Ő܂�Ԃ����s��ɂ���
				this->m[column][row] = mat.m[row][column];
			}
		}
		return *this;
	}
	;
	//Matrix2D�̓]�u����̒�`
	inline Matrix2D operator/= (const Matrix2D& mat)
	{
		for (int column = 0; column < ROW_MAX_NUM_2D; column++)
		{
			for (int row = 0; row < COLUMN_MAX_NUM_2D; row++)
			{
				//�e������Ίp�����Ő܂�Ԃ����s��ɂ���
				this->m[column][row] = mat.m[row][column];
			}
		}
		return *this;
	}

	//Matrix2D�̑���̒�`
	inline Matrix2D operator= (const Matrix2D& mat)
	{
		for (int row = 0; row < ROW_MAX_NUM_2D; ++row)
		{
			for (int column = 0; column < COLUMN_MAX_NUM_2D; ++column)
			{
				this->m[row][column] = mat.m[row][column];
			}
		}

		return *this;
	}

	//����s�񔻒�
	inline bool operator== (const Matrix2D& mat)
	{
		for (int row = 0; row < ROW_MAX_NUM_2D; ++row)
		{
			for (int column = 0; column < COLUMN_MAX_NUM_2D; ++column)
			{
				//�ЂƂł��Ⴄ�v�f�����݂���ꍇ�͋U
				if (this->m[row][column] != mat.m[row][column])
					return false;
			}
		}

		//�����܂ŗ����ꍇ�͐^
		return true;
	}
};

constexpr Matrix2D ZERO_MATRIX = { 0.0f };
