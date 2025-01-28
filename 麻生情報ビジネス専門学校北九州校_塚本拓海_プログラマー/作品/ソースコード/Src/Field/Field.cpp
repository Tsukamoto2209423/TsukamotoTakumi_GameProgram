#include "Field.h"
#include "DxLib.h"

namespace BOUDAMA
{
	namespace FIELD
	{
		constexpr char PATH[] = "Data/Model/Field/Field_Blue.x";

		constexpr VECTOR SCALE = { 9.0f,9.0f, 9.0f };
	}

	//�R���X�g���N�^
	Field::Field()
	{
		//�n���h��������
		handle_ = -1;
	}

	//�f�X�g���N�^
	Field::~Field()
	{

	}

	//�����������֐�
	void Field::Init(void)
	{

	}

	//�ǂݍ��ݏ����֐�
	void Field::Load(void)
	{
		//���ǂݍ��݂Ȃ�ǂݍ���
		if (handle_ == -1)
		{
			handle_ = MV1LoadModel(FIELD::PATH);
		}

		MV1SetScale(handle_, FIELD::SCALE);

		MV1SetPosition(handle_, { 0.0f,-30.0f,0.0f });
	}

	//�s�������֐�
	void Field::Step(void)
	{

	}

	//�`�揈���֐�
	void Field::Draw(void)
	{
		//�`��
		MV1DrawModel(handle_);
	}

	//�j�������֐�
	void Field::Fin(void)
	{
		//�ǂݍ��܂�Ă���Ȃ�j������
		if (handle_ != -1)
		{
			MV1DeleteModel(handle_);
			handle_ = -1;
		}
	}
}