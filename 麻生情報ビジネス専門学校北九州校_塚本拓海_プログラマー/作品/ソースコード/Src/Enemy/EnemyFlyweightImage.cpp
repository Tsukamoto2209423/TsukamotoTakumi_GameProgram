#include "EnemyFlyweightImage.h"
#include "DxLib.h"

namespace BOUDAMA
{
	//�G�̏�ɏo������u�I�v�̉摜�̃p�X
	constexpr char EXCLAMATION_PATH[] = { "Data/Image/Exclamation_Mark.PNG" };

	void EnemyFlyweightImage::Load(void)
	{
		images_.emplace_back(LoadGraph(EXCLAMATION_PATH));
	}

	void EnemyFlyweightImage::Fin(void)
	{
		for (const auto& image : images_)
		{
			DeleteGraph(image);
		}

		images_.clear();
		images_.shrink_to_fit();
	}
}
