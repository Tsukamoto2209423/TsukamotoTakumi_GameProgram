#pragma once

#include <vector>
#include "Object/Object.h"
#include "BulletBase.h"

namespace BOUDAMA
{
	//�e���Ǘ��p�N���X
	class BulletManager
	{
	private:
		//�e�̃x�N�^�[
		std::vector<BulletBase*> bullets_;

	public:
		//�R���X�g���N�^
		BulletManager();
		//�f�X�g���N�^
		~BulletManager();

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

		//�e���ˏ����֐�
		void RequestBullet(const Vector3D& firePos, const Vector3D& rot, int playerType, Object* player);

		//�e�擾
		inline const std::vector<BulletBase*>& GetBullet() { return bullets_; }

	};
}
