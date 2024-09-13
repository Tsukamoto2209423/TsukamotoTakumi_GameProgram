#include "MyMath.h"
#include <math.h>

// 点P(x1, y1)から点Q(x2, y2)までの距離を返す
float MyMath::GetDistance(float x1, float y1, float x2, float y2)
{
	// 点Pから点Qまでの直線を斜辺とする直角三角形を作り、
	// ピタゴラスの定理から斜辺の長さを計算する。
	// ①まずは底辺の長さを計算する
	float a = x2 - x1;

	// ②高さを計算する
	float b = y2 - y1;

	// ③斜辺の2乗の値を計算する
	float double_c = a * a + b * b;

	// ④2乗の値なので平方根を計算して長さとする
	// 　平方根は<math.h>のsqrtf関数で取得できる
	return sqrtf(double_c);
}

// 回転値を0～2πの値にする
float MyMath::RadianNormalize(float rad)
{
	float result = rad;
	if (result < 0.0f) {
		while (result < 0.0f) {
			result += DX_TWO_PI_F;
		}
	}
	else if (result > DX_TWO_PI_F) {
		while (result <= DX_TWO_PI_F) {
			result -= DX_TWO_PI_F;
		}
	}

	return result;
}
