#pragma once

#include "SubstanceBase.h"

namespace BOUDAMA
{
	//�啨���N���X
	class BigSubstance : public SubstanceBase
	{
	private:

	public:
		//�R���X�g���N�^
		BigSubstance();

		//�f�X�g���N�^
		~BigSubstance();

		//�����������֐�
		void Init(void) override;

		//�ǂݍ��ݏ����֐�
		void Load(int origineHandle) override;
	};
}
