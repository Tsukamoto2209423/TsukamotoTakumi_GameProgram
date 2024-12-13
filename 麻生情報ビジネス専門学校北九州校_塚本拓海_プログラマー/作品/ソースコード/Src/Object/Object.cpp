#include "Object.h"
#include "Math/MyMath.h"

namespace BOUDAMA
{
	//‰Šú‰»ˆ—ŠÖ”
	void Object::Init(void)
	{
		//‰Šú‰»
		handle_ = -1;
		isAlive_ = true;
		pos_ = MyMath::ZERO_VECTOR_3D;
		velocity_ = MyMath::ZERO_VECTOR_3D;
		rot_ = MyMath::ZERO_VECTOR_3D;
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
		velocity_ = MyMath::ZERO_VECTOR_3D;
	}

	//“–‚½‚è”»’èˆ—
	void Object::HitCalculation(int damage)
	{
		hp_ -= damage;

		if (hp_ <= 0)
		{
			//€–Sˆ—
			isAlive_ = false;
			velocity_ = MyMath::ZERO_VECTOR_3D;
		}
	}
}
