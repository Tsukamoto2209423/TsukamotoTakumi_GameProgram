#include "SceneBase.h"
#include "Scene.h"

void SceneBase::Loop(const SCENE_STATE sceneState)
{
	//初期化・本編・破棄の分岐処理	
	static const decltype(&SceneBase::Init) SceneStatePointer[static_cast<int>(SCENE_STATE::NUM)] =
	{
		&SceneBase::Init,
		&SceneBase::Step,
		&SceneBase::Fin
	};

	//初期化・本編・破棄の分岐処理
	(this->*SceneStatePointer[static_cast<int>(sceneState)])();
}
