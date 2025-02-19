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

//画像読み込み処理
void Model::Load(const char* name)
{
	handle_ = MV1LoadModel(name);
}

//画像読み込み処理
void Model::Load(const int handleNum)
{
	handle_ = MV1DuplicateModel(handleNum);
}
