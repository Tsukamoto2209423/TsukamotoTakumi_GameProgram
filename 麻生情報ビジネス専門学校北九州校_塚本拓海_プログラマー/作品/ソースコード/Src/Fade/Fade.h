#pragma once

#include <vector>
#include "FadeParameter.h"

namespace BOUDAMA
{
	//�t�F�[�h�C���E�t�F�[�h�A�E�g�p�N���X
	class Fade
	{
	private:
		//���
		FADE::STATE state_;

		//���l(���ߓx)
		int alphaValue_;

		//�ʒu
		int posX_;

		//�摜�̓Y����
		int handleIndex_;

		//�W�����̓Y����
		int concentrationLineIndex_;

		//�摜�n���h����ۑ�����x�N�^�[
		std::vector<int> syobonHandles_;

		//�W�����̃n���h����ۑ�����x�N�^�[
		std::vector<int> lineHandles_;

		//��]�p�x
		float rotAngle_;

		//�t�F�[�h�C���E�t�F�[�h�A�E�g�������I�������
		bool isEnd_;

	public:
		//�R���X�g���N�^
		Fade();

		//�f�X�g���N�^
		~Fade();

		//�����������֐�
		void Init(void);

		//�ǂݍ��ݏ����֐�
		void Load(void);

		//�X�V�����֐�
		void Step(void);

		//�`�揈��
		void Draw(void);

		//�j�������֐�
		void Fin(void);

		//�t�F�[�h�̏�ԕύX
		void Change(void);

		//�t�F�[�h�C�����t�F�[�h�A�E�g���I�����������
		bool IsEnd(void) const noexcept;

	private:
		//�W�����`��
		void DrawConcentrationLine(void);
	};
}
