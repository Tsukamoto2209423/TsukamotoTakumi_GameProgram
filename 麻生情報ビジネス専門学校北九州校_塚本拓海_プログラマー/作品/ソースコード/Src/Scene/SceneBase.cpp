#include "SceneBase.h"
#include "Scene.h"

namespace BOUDAMA
{
	void SceneBase::Loop(const SCENE_STATE sceneState)
	{
		//�������E�{�ҁE�j���̕��򏈗�	
		static const decltype(&SceneBase::Init) SceneStatePointer[static_cast<int>(SCENE_STATE::NUM)] =
		{
			&SceneBase::Init,
			&SceneBase::Step,
			&SceneBase::Fin
		};

		//�������E�{�ҁE�j���̕��򏈗�
		(this->*SceneStatePointer[static_cast<int>(sceneState)])();
	}
}
