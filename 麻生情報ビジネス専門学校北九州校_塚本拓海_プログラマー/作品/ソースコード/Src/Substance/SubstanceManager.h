#pragma once

#include <vector>
#include <memory>
#include "SubstanceBase.h"
#include "Substance.h"

namespace BOUDAMA
{
	//�����Ǘ��N���X
	class SubstanceManager
	{
	private:
		//�����Ǘ�
		std::vector<std::shared_ptr<SubstanceBase>> substances_;

	public:
		//�R���X�g���N�^
		SubstanceManager();

		//�f�X�g���N�^
		~SubstanceManager();

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

		//�����̏ꏊ�����юU��Ȃ���o�����鏈��
		void FlyAppearCalculation(const Vector3D& appearPos);

		//�����_���ɕ����𒊑I���Ĉ����̏ꏊ�����юU��Ȃ���o�����鏈��
		void RandomFlyAppearCalculation(const Vector3D& appearPos);

		inline const std::vector<std::shared_ptr<SubstanceBase>>& GetSubstance(void) const { return substances_; }
	};
}
