#include "SkyBox.h"
#include "SkyBoxParameter.h"
#include <DxLib.h>
#include <Math/MyMath.h>

namespace BOUDAMA
{
	//�R���X�g���N�^
	SkyBox::SkyBox() : handle_(-1) {}

	//�f�X�g���N�^
	SkyBox::~SkyBox() {}

	//�����������֐�
	void SkyBox::Init(void)
	{
		//������
		handle_ = -1;
		pos_ = MyMath::ZERO_VECTOR_3D;
		rot_ = MyMath::ZERO_VECTOR_3D;
	}

	//�ǂݍ��ݏ����֐�
	void SkyBox::Load(void)
	{
		//�ǂݍ���
		handle_ = MV1LoadModel(SKY_BOX::SKY_BOX_PATH);

		//�傫������
		MV1SetScale(handle_, SKY_BOX::SCALE_MULTIPLE);
	}

	//�s�������֐�
	void SkyBox::Step(void)
	{
		//Y������]������
		rot_.y += SKY_BOX::SKY_BOX_ROT_SPEED;

		//��]�𔽉f������
		MV1SetRotationXYZ(handle_, rot_);
	}

	//�`�揈���֐�
	void SkyBox::Draw(void)
	{
		//�\��
		MV1DrawModel(handle_);
	}

	//�j�������֐�
	void SkyBox::Fin(void)
	{
		//�n���h�������݂�����폜
		if (handle_ != -1)
		{
			MV1DeleteModel(handle_);
			handle_ = -1;
		}
	}
}
