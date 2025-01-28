#pragma once

#include <memory>
#include "Scene.h"
#include <Vector/Vector2D.h>

namespace BOUDAMA
{
	//��ʗp���ۃN���X
	class SceneBase
	{
	protected:

	public:
		SceneBase() {};

		virtual ~SceneBase() {};

		/// <summary>
		/// �������E�{�ҁE�j���̕��򏈗�	
		/// </summary>
		/// <param name="sceneState">
		/// ���݂̃V�[���̏��
		/// </param>
		virtual void Loop(const SCENE_STATE sceneState);

		//�`�揈��
		virtual void Draw(void) = 0;

		//�������֐�
		virtual void Init(void) = 0;

		//�ǂݍ��ݏ����֐�
		virtual void Load(void) = 0;

		//�s�������֐�
		virtual void Step(void) = 0;

		//�j�������֐�
		virtual void Fin(void) = 0;

		/// <summary>
		/// ���̃V�[���ɐi�ނ����肷��֐�
		/// </summary>
		/// <param name="state">���݂̃V�[���̏��</param>
		/// <returns>
		/// true:���̃V�[���Ɉڍs
		/// false:���݂̃V�[���̂܂�
		/// </returns>
		virtual bool CanGoToNextScene(const SCENE_STATE state) const = 0;

		/// <summary>
		/// ���̃V�[������p�֐�
		/// </summary>
		/// 
		/// <returns>
		/// ���̃V�[��
		/// </returns>
		virtual inline SCENE GetNextSceneNum(void) const noexcept = 0;
	};
}
