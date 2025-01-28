#pragma once

#include <vector>
#include <memory>
#include "EnemyParameter.h"
#include "EnemyBase.h"
#include <Item/ItemManager.h>
#include <Scene/Scene.h>

namespace BOUDAMA
{
	//�G���Ǘ��N���X
	class EnemyManager
	{
	private:
		//�G�̔z��
		std::vector<std::shared_ptr<EnemyBase>> enemies_;

		//�G�̍ő吔
		std::vector<int> enemiesMaxNum_;

		//�G�o�����Ԍv��
		int appearCountTime_[static_cast<int>(ENEMY_MANAGER::ENEMY_LIST::ALL_NUM)];

		//���S��
		int deathCount_;

		//�t�B�[�o�[�^�C���v��
		int feverTimeCount_;

		//�G�����X�Əo������u�t�B�[�o�[�^�C���v���ǂ���
		bool isFeverTime_;

	public:
		//�R���X�g���N�^
		EnemyManager();

		//�f�X�g���N�^
		~EnemyManager();

		//�����������֐�
		void Init(const SCENE difficulty, const ItemManager& itemManager);

		//�ǂݍ��ݏ����֐�
		void Load(const SCENE difficulty);

		//�s�������֐�
		void Step(const Vector3D& playerPos);

		//�`�揈���֐�
		void Draw(void);

		//�j�������֐�
		void Fin(void);

		//�G���擾
		inline const std::vector<std::shared_ptr<EnemyBase>>& GetEnemy(void) { return enemies_; }

		inline int GetEnemyDeathCount(void) const { return deathCount_; }

		inline void AddEnemyDeathCount(void) { ++deathCount_; }

		inline void FeverTime(void) { isFeverTime_ = true; }

	private:
		template<class EnemyType, class... Args>
		void CreateEnemy(Args... args)
		{
			enemies_.emplace_back(std::make_shared<EnemyType>(args...));
		}

		//�o���������Ԍv���֐�
		void AppearanceCountProcess(void);

		//�G�����ۂɃQ�[�����ɏo��������֐�
		void AppearanceRequest(int kindNum = 0, int enemyArrayIndex = 0);
	};
}
