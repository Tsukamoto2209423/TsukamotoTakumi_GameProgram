#include "BulletManager.h"
#include "Bullet.h"
#include "BigBullet.h"
#include "Common/Common.h"
#include <Matrix/Matrix3D.h>
#include <Math/MyMath.h>
#include <Player/PlayerParameter.h>

#define New new(_NORMAL_BLOCK,__FILE__,__LINE__)

namespace BOUDAMA
{
	//�R���X�g���N�^
	BulletManager::BulletManager(void)
	{
		//������
	}

	//�f�X�g���N�^
	BulletManager::~BulletManager(void)
	{
		//�j������
	}

	//�����������֐�
	void BulletManager::Init(void)
	{
		//�f�[�^����
		bullets_.clear();
		//m_enemyBullet.clear();

		//�L���̈�m��
		// sizeof(Bullet) �~ BULLET_MAX_NUM
		for (int bulletIndex = 0; bulletIndex < BULLET::MAX_NUM; ++bulletIndex)
		{
			bullets_.emplace_back(New Bullet);
		}

		//�L���̈�m��
		// sizeof(BigBullet) �~ BULLET_MAX_NUM
		for (int bulletIndex = 0; bulletIndex < BULLET::MAX_NUM; ++bulletIndex)
		{
			bullets_.emplace_back(New BigBullet);
		}

	}

	//�ǂݍ��ݏ����֐�
	void BulletManager::Load(void)
	{
		int origineBulletHandle[] = { MV1LoadModel(BULLET::PATH),MV1LoadModel(BIG_BULLET::PATH) };

		//�ǂݍ��ݏ���
		for (auto bullet : bullets_)
		{
			bullet->Load(origineBulletHandle[bullet->GetType()]);
		}

	}

	//�s�������֐�
	void BulletManager::Step(void)
	{
		//�e�ړ�����
		for (auto& bullet : bullets_)
		{
			//�ړ����̒e�������ꍇ
			if (bullet->GetIsActive())
			{
				//�s������
				bullet->Step();
			}
		}
	}

	//�`�揈���֐�
	void BulletManager::Draw(void)
	{
		//�`��
		for (auto& bullet : bullets_)
		{
			bullet->Draw();
		}

	}

	//�j�������֐�
	void BulletManager::Fin(void)
	{
		//�j������

		//�w���Ă���̂͒e�̎���
		for (auto&& bullet = bullets_.begin(); bullet != bullets_.end();)
		{
			(*bullet)->Fin();

			delete* bullet;
			bullet = bullets_.erase(bullet);
		}

		//����
		bullets_.clear();

		//�m�ۂ����L���̈���č\�z
		bullets_.shrink_to_fit();
	}

	//�e���ˏ����֐�
	void BulletManager::RequestBullet(const Vector3D& firePos, const Vector3D& rot, int playerState, Object* player)
	{
		//�e��������
		for (auto&& bullet : bullets_)
		{
			//���g�p�̒e ���� �����������������ꍇ
			if (!bullet->GetIsActive())
			{
				bullet->SetOwner(player);

				//�v���C���[���猩��100.0f�O���Ɉʒu�ݒ�
				bullet->SetPos(Matrix3D::GetTranslateMatrix(firePos.x, 150.0f, firePos.z) *
					Matrix3D::GetYawMatrix(rot.y) * Matrix3D::GetTranslateMatrix(0.0f, 0.0f, -(20.0f + bullet->GetRadius())) * MyMath::ZERO_VECTOR_3D);

				//���˕����ݒ�
				bullet->SetRot(rot);

				//���ґh��
				bullet->SetIsActive(true);

				//�E�o
				break;
			}
		}
	}
}
