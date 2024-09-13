#pragma once

#include <math.h>
#include "Vector/Vector2D.h"


//Matrix2Dの行の最大数
constexpr int ROW_MAX_NUM_2D = 4;

//Matrix2Dの列の最大数
constexpr int COLUMN_MAX_NUM_2D = 4;

//Matrix2Dの行と列の最大数
constexpr int ROW_COLUMN_MAX_NUM_2D = 4;

//仮の設置
class Vector3D
{
public:
	float x, y, z;
};

class Matrix2D
{
public:
	//実四次正方行列
	float m[ROW_MAX_NUM_2D][COLUMN_MAX_NUM_2D];


public: // コンストラクタ
	/*explicit constexpr Matrix2D() noexcept : m() {}
	explicit constexpr Matrix2D(float XYZ) noexcept :
	constexpr Matrix2D(const Matrix2D& mat) noexcept :
	constexpr Matrix2D(const MATRIX& mat) noexcept : */

public:

	//零行列
	inline static constexpr Matrix2D ZERO_MATRIX() { return { 0.0f }; }

	//単位行列
	inline static constexpr Matrix2D IDENTITY_MATRIX()
	{
		return { 1.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,
		0.0f,0.0f,1.0f};
	}

	//平行移動行列(float)
	inline static constexpr Matrix2D TRANSLATE_MATRIX(float movingValueX, float movingValueY)
	{
		return { 1,0,movingValueX,
				 0,1,movingValueY,
				 0,0,1 };
	}

	//平行移動行列(Vector3D)
	inline static constexpr Matrix2D GetTranslateMatrix(const Vector3D& vec)
	{
		return { 1,0,vec.x,
				 0,1,vec.y,
				 0,0,vec.z };
	}

	//拡縮行列(float)
	inline static constexpr Matrix2D GetScaleMatrix(float scalingX, float scalingY)
	{
		return { scalingX,0,0,
				 0,scalingY,0,
				 0, 0, 1 };
	}

	//拡縮行列(Vector3D)
	inline static constexpr Matrix2D GetScaleMatrix(const Vector3D& scalingVec)
	{
		return { scalingVec.x,0,0,
				 0,scalingVec.y,0,
				 0,0,1 };
	}

	//回転行列
	inline Matrix2D GetRotMatrix(float rotationValue)
	{
		return { cosf(rotationValue),-sinf(rotationValue),0,
				 sinf(rotationValue),cosf(rotationValue),0,
				 0,0,1 };
	}

public:
	//加法、減法、乗法、転置

	//Matrix2Dの加法の定義
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

	//Matrix2Dの加法代入の定義
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

	//Matrix2Dの減法の定義
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

	//Matrix2Dの減法代入の定義
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

	//Matrix2Dのスカラー倍の定義(int)
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

	//Matrix2Dのスカラー倍の定義(float)
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

	//Matrix2Dのスカラー倍代入の定義(int)
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

	//Matrix2Dのスカラー倍代入の定義(float)
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

	//Matrix2Dの乗法の定義(Matrix2D)
	//行列同士の積は非可換である
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

	//Matrix2Dの乗法代入の定義(Matrix2D)
	//行列同士の積は非可換である
	inline Matrix2D operator*= (const Matrix2D& mat)
	{
		return *this = *this * mat;
	}

	//Matrix2Dの乗法の定義(Vector2D)
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

	//Matrix2Dの乗法代入の定義(Vector2D)
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

	//Matrix2Dの転置の定義
	inline Matrix2D operator/ (const Matrix2D& mat)
	{
		for (int column = 0; column < ROW_MAX_NUM_2D; column++)
		{
			for (int row = 0; row < COLUMN_MAX_NUM_2D; row++)
			{
				//各成分を対角成分で折り返した行列にする
				this->m[column][row] = mat.m[row][column];
			}
		}
		return *this;
	}
	;
	//Matrix2Dの転置代入の定義
	inline Matrix2D operator/= (const Matrix2D& mat)
	{
		for (int column = 0; column < ROW_MAX_NUM_2D; column++)
		{
			for (int row = 0; row < COLUMN_MAX_NUM_2D; row++)
			{
				//各成分を対角成分で折り返した行列にする
				this->m[column][row] = mat.m[row][column];
			}
		}
		return *this;
	}

	//Matrix2Dの代入の定義
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

	//同一行列判定
	inline bool operator== (const Matrix2D& mat)
	{
		for (int row = 0; row < ROW_MAX_NUM_2D; ++row)
		{
			for (int column = 0; column < COLUMN_MAX_NUM_2D; ++column)
			{
				//ひとつでも違う要素が存在する場合は偽
				if (this->m[row][column] != mat.m[row][column])
					return false;
			}
		}

		//ここまで来た場合は真
		return true;
	}
};

constexpr Matrix2D ZERO_MATRIX = { 0.0f };
