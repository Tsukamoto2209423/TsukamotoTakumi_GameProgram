#include "Model.h"

#include <DxLib.h>

Model::Model(void) : handle_(-1) {}


Model::~Model(void)
{
	if (handle_ != -1)
	{
		DeleteGraph(handle_);
		handle_ = -1;
	}
}

//�摜�ǂݍ��ݏ���
void Model::Load(const char* name)
{
	handle_ = MV1LoadModel(name);
}

//�摜�ǂݍ��ݏ���
void Model::Load(const int handleNum)
{
	handle_ = MV1DuplicateModel(handleNum);
}
