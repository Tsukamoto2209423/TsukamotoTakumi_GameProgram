#pragma once

#include <vector>
#include "Vector/Vector3D.h"

namespace BOUDAMA
{
	enum FLYWEIGHT_IMAGE
	{
		EXCLAMATION
	};

	class EnemyFlyweightImage final
	{
	private:
		static inline std::vector<int> images_;

	public:
		static inline int GetImageHandle(int index) { return images_[index]; }

		static void Load(void);

		static void Fin(void);
	};
}
