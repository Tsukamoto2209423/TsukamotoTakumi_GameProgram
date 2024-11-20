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

//‰æ‘œ“Ç‚İ‚İˆ—
void Model::Load(const char* name)
{
	handle_ = MV1LoadModel(name);
}

//‰æ‘œ“Ç‚İ‚İˆ—
void Model::Load(const int handleNum)
{
	handle_ = MV1DuplicateModel(handleNum);
}
