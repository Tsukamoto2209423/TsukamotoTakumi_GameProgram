#pragma once

namespace BOUDAMA
{
	//��N���X
	class Field
	{
	private:
		//�n���h��
		int handle_;

	public:
		//�R���X�g���N�^
		Field();

		//�f�X�g���N�^
		~Field();

		//�����������֐�
		void Init(void);

		//�ǂݍ��ݏ����֐�
		void Load(void);

		//�s�������֐�
		void Step(void);

		//�`�揈���֐�
		void Draw(void);

		//�j�������֐�
		void Fin(void);
	};
}
