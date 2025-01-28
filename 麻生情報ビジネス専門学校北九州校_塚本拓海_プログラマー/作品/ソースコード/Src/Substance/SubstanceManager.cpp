#include "SubstanceManager.h"
#include <DxLib.h>
#include "BigSubstance.h"
#include "Substance/SubstanceParameter.h"

namespace BOUDAMA
{
	//�R���X�g���N�^
	SubstanceManager::SubstanceManager()
	{

	}

	//�f�X�g���N�^
	SubstanceManager::~SubstanceManager()
	{

	}

	//�����������֐�
	void SubstanceManager::Init(void)
	{
		//�e�ʊm��
		for (int num = 0; num < SUBSTANCE::MAX_NUM; ++num)
		{
			substances_.emplace_back(std::make_shared<Substance>());
		}

		for (int num = 0; num < BIGSUBSTANCE::MAX_NUM; ++num)
		{
			substances_.emplace_back(std::make_shared<BigSubstance>());
		}

		//������
		for (const auto& substance : substances_)
		{
			substance->Init();
		}

		for (int appearNum = 0; const auto& substance : substances_)
		{
			//�����ɗN������
			substance->FlyAppearCalculation(SUBSTANCE::INIT_POS);
			++appearNum;

			//�����ȏ�N������E�o
			if (ALL_SUBSTANCE::INIT_APPEAR_NUM <= appearNum)
			{
				break;
			}
		}

	}

	//�ǂݍ��ݏ����֐�
	void SubstanceManager::Load(void)
	{
		//�����f���f�[�^�ǂݍ��ݏ���
		int originalHandle = MV1LoadModel(SUBSTANCE::PATH);

		int originalBigHandle = MV1LoadModel(BIGSUBSTANCE::PATH);

		auto&& substance = substances_.begin();

		//�������f���f�[�^�ǂݍ��ݏ���
		for (int num = 0; num < SUBSTANCE::MAX_NUM; ++num)
		{
			(*substance)->Load(originalHandle);

			++substance;
		}

		for (int num = 0; num < BIGSUBSTANCE::MAX_NUM; ++num, ++substance)
		{
			(*substance)->Load(originalBigHandle);
		}

		MV1DeleteModel(originalHandle);

		MV1DeleteModel(originalBigHandle);

	}

	//�s�������֐�
	void SubstanceManager::Step(void)
	{
		//�ꊇ�s������
		for (const auto& substance : substances_)
		{
			substance->Step();
		}
	}

	//�`�揈���֐�
	void SubstanceManager::Draw(void)
	{
		for (const auto& substance : substances_)
		{
			substance->Draw();
		}
	}

	//�j�������֐�
	void SubstanceManager::Fin(void)
	{
		for (const auto& substanceItr : substances_)
		{
			substanceItr->Fin();
		}

	}

	//�����̏ꏊ�����юU��Ȃ���o�����鏈��
	void SubstanceManager::FlyAppearCalculation(const Vector3D& appearPos)
	{
		//�܂��o�����Ă��Ȃ����̂����I��
		for (int appearNum = 0; const auto& substance : substances_)
		{
			if (substance->GetIsActive())
			{
				continue;
			}

			substance->FlyAppearCalculation(appearPos);

			++appearNum;

			//MAX_APPEAR_NUM�o��������߂�
			if (ALL_SUBSTANCE::MAX_APPEAR_NUM <= appearNum)
			{
				return;
			}
		}
	}

	//�����_���ɕ����𒊑I���Ĉ����̏ꏊ�����юU��Ȃ���o�����鏈��
	void SubstanceManager::RandomFlyAppearCalculation(const Vector3D& appearPos)
	{
		std::vector<int> randomNums;

		//�܂��o�����Ă��Ȃ����̂����I��
		for (int num = 0; const auto& substance : substances_)
		{
			if (substance->GetIsActive())
			{
				continue;
			}

			//�Y�����ۑ�
			randomNums.emplace_back(num);

			++num;
		}

		if (randomNums.empty())
		{
			return;
		}

		/*
			�o�������鐔�����߂�
			�o���ł��鐔���A�G��|�����Ƃ��ɗN�����鐔�ȏ�Ȃ�A�G��|�����Ƃ��ɗN�����鐔����
			�G��|�����Ƃ��ɗN�����鐔���A�o���ł��鐔�������������ꍇ�A�o���ł��鐔����
		*/
		unsigned int maxAppearNum = (ALL_SUBSTANCE::MAX_APPEAR_NUM <= randomNums.back() ? ALL_SUBSTANCE::MAX_APPEAR_NUM : randomNums.back());

		//��납��͈͂��k�����Ă����t�B�b�V���[�E�C�F�[�c�̃V���b�t�����g��
		for (unsigned int appearCount = 0; appearCount < maxAppearNum; ++appearCount)
		{
			//�o��������Y�����������_���Ō��߂�
			int appearIndex = GetRand((maxAppearNum - 1) - appearCount);

			//�o������
			substances_[randomNums[appearIndex]]->FlyAppearCalculation(appearPos);

			//�l��������
			const int tempNum = randomNums[appearIndex];
			randomNums[appearIndex] = randomNums[(maxAppearNum - 1) - appearCount];
			randomNums[(maxAppearNum - 1) - appearCount] = tempNum;
		}
	}
}
