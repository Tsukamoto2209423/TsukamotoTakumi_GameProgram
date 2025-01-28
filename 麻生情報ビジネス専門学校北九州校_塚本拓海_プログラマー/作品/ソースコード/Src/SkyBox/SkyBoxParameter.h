#pragma once

#include "Math/MyMath.h"
#include "Vector/Vector3D.h"

namespace BOUDAMA
{
	//�V���N���X�Ŏg���萔
	namespace SKY_BOX
	{
		//�傫�������p
		constexpr Vector3D SCALE_MULTIPLE = { 150.0f,150.0f,150.0f };

		//��]���x
		constexpr float SKY_BOX_ROT_SPEED = MyMath::PI * 0.00004f;

		//�V���̃p�X
		constexpr char SKY_BOX_PATH[] = "Data/Model/SkyBox/SkyBox.x";

	}
}
