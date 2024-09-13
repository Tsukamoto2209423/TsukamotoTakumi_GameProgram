#include "Vector2D.h"

// 始点と終点からベクトルを作成
Vector2D Vector2D::VecCreate(const Vector2D& start, const Vector2D& end)
{
	//終点 - 始点
	return Vector2D(end.x - start.x, end.y - start.y);
}

// ベクトルの足し算
Vector2D Vector2D::VecAdd(const Vector2D& vec1, const Vector2D& vec2)
{
	//各成分を加算
	return Vector2D(vec1.x + vec2.x, vec1.y + vec2.y);
}

//L2ノルム
float Vector2D::VecL2Norm(const Vector2D& vec)
{
	// ||vec||_2 = √(|vec.x|^2 + |vec.y|^2)
	return sqrtf(vec.x * vec.x + vec.y * vec.y);
}

//単位ベクトル作成
Vector2D Vector2D::Normalize(const Vector2D& vec)
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
Vector2D Vector2D::VecNormalizeAndScalartimes(const Vector2D& vec, float scale)
{
	float vec_norm = VecL2Norm(vec);

	return { (vec.x / vec_norm) * scale, (vec.y / vec_norm) * scale };
}

//ベクトルを作成し単位ベクトルにしてスカラー倍
Vector2D Vector2D::VecNormalizeAndScalartimes(const Vector2D& start, const Vector2D& end, float scale)
{
	Vector2D vec;

	vec.x = end.x - start.x;
	vec.y = end.y - start.y;

	float vec_norm = VecL2Norm(vec);

	return { (vec.x / vec_norm) * scale, (vec.y / vec_norm) * scale };
}

// ベクトルのスカラー倍
Vector2D Vector2D::VecScalartimes(const Vector2D& vec, float scale)
{
	//各成分をスカラー倍
	return Vector2D(vec.x * scale, vec.y * scale);
}

// ベクトルの内積
float Vector2D::VecDot(const Vector2D& vec1, const Vector2D& vec2)
{
	return vec1.x * vec2.x + vec1.y * vec2.y;
}

// ベクトルの向きをラジアン角で取得
float Vector2D::VecDir(const Vector2D& vec)
{
	return atan2f(vec.y, vec.x);
}
