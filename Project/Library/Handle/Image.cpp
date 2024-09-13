#include "Image.h"

#include <DxLib.h>

Image::Image(void) : handle_(-1) {}


Image::~Image(void)
{
	if (handle_ != -1)
	{
		DeleteGraph(handle_);
		handle_ = -1;
	}
}

void Image::Load(const char* name)
{
	handle_ = LoadGraph(name);
}
