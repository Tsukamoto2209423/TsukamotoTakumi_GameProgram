#pragma once

#include "Math/MyMath.h"
#include "Vector/Vector3D.h"

namespace BOUDAMA
{
	//天球クラスで使う定数
	namespace SKY_BOX
	{
		//大きさ調整用
		constexpr Vector3D SCALE_MULTIPLE = { 150.0f,150.0f,150.0f };

		//回転速度
		constexpr float SKY_BOX_ROT_SPEED = MyMath::PI * 0.00004f;

		//天球のパス
		constexpr char SKY_BOX_PATH[] = "Data/Model/SkyBox/SkyBox.x";

	}
}
