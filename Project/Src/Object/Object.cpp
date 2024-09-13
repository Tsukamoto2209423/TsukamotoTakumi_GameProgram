#include "Object.h"
#include "Math/MyMath.h"

//‰Šú‰»ˆ—ŠÖ”
void Object::Init(void)
{
	//‰Šú‰»
	handle_ = -1;
	isAlive_ = true;
	pos_ = MY_MATH::ZERO_VECTOR_3D;
	velocity_ = MY_MATH::ZERO_VECTOR_3D;
	rot_ = MY_MATH::ZERO_VECTOR_3D;
}

//“Ç‚İ‚İˆ—ŠÖ”
void Object::Load(void) {}

//s“®ˆ—ŠÖ”
void Object::Step(void) {}

//•`‰æˆ—ŠÖ”
void Object::Draw(void)
{
	//¶‘¶‚µ‚Ä‚¢‚éê‡‚Í•`‰æ
	if (isAlive_)
	{
		MV1DrawModel(handle_);
	}
}

//”jŠüˆ—ŠÖ”
void Object::Fin(void)
{
	//”jŠüˆ—
	if (handle_ != -1)
	{
		MV1DeleteModel(handle_);
		handle_ = -1;
	}
}

//“–‚½‚è”»’èˆ—
void Object::HitCalculation(void)
{
	//€–Sˆ—
	isAlive_ = false;
	velocity_ = MY_MATH::ZERO_VECTOR_3D;
}
