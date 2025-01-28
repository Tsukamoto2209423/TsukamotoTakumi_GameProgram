#include "Object.h"
#include "Math/MyMath.h"

namespace BOUDAMA
{
	//�����������֐�
	void Object::Init(void)
	{
		//������
		handle_ = -1;
		isAlive_ = true;
		pos_ = MyMath::ZERO_VECTOR_3D;
		velocity_ = MyMath::ZERO_VECTOR_3D;
		rot_ = MyMath::ZERO_VECTOR_3D;
	}

	//�ǂݍ��ݏ����֐�
	void Object::Load(void) {}

	//�s�������֐�
	void Object::Step(void) {}

	//�`�揈���֐�
	void Object::Draw(void)
	{
		//�������Ă���ꍇ�͕`��
		if (isAlive_)
		{
			MV1DrawModel(handle_);
		}
	}

	//�j�������֐�
	void Object::Fin(void)
	{
		//�j������
		if (handle_ != -1)
		{
			MV1DeleteModel(handle_);
			handle_ = -1;
		}
	}

	//�����蔻�菈��
	void Object::HitCalculation(void)
	{
		//���S����
		isAlive_ = false;
		velocity_ = MyMath::ZERO_VECTOR_3D;
	}

	//�����蔻�菈��
	void Object::HitCalculation(int damage)
	{
		hp_ -= damage;

		if (hp_ <= 0)
		{
			//���S����
			isAlive_ = false;
			velocity_ = MyMath::ZERO_VECTOR_3D;
		}
	}
}
