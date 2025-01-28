#pragma once

#include <type_traits>

namespace BOUDAMA
{
	//��ʈꗗ
	enum class SCENE
	{
		TITLE,
		NORMAL_PLAY,
		HARD_PLAY,
		ENDLESS_PLAY,
		CLEAR,
		RESULT,
		GAMEOVER,

		ALL_NUM
	};

	//�󋵔��f�p�񋓌^
	enum class SCENE_STATE
	{
		INIT,		//������
		STEP,		//���쏈��
		FIN,		//�j��

		NUM			//�󋵔��f�p�萔�̑���
	};

	constexpr SCENE_STATE begin(SCENE_STATE) { return SCENE_STATE::INIT; }

	constexpr SCENE_STATE end(SCENE_STATE) { return SCENE_STATE::NUM; }

	constexpr SCENE_STATE operator*(SCENE_STATE dir) { return dir; }

	constexpr SCENE_STATE operator++(SCENE_STATE& dir)
	{
		return dir = SCENE_STATE(std::underlying_type_t<SCENE_STATE>(dir) + 1);
	}
}
