#pragma once

#include "Vector/Vector3D.h"

namespace BOUDAMA
{
	//�V���N���X
	class SkyBox final
	{
	private:
		//�n���h��
		int handle_;

		//�ʒu
		Vector3D pos_;

		//�p�x��
		Vector3D rot_;

	public:
		//�R���X�g���N�^
		SkyBox();
		//�f�X�g���N�^
		~SkyBox();

		//�����������֐�
		void Init(void);

		//�ǂݍ��ݏ����֐�
		void Load(void);

		//�X�V�����֐�
		void Step(void);

		//�`�揈���֐�
		void Draw(void);

		//�j�������֐�
		void Fin(void);
	};
}
