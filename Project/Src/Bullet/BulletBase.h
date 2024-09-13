#pragma once

#include "Object/Object.h"

//弾用基底クラス
class BulletBase : public Object
{
protected:
	int type_;
	int lifeSpan_;
	Object* owner_;

public:
	//コンストラクタ
	BulletBase() 
	{
		owner_ = nullptr; type_ = -1; lifeSpan_ = 0;
	}

	//デストラクタ
	~BulletBase() {}

	//読み込み処理関数
	virtual void Load(int originalHandle)
	{
		if (handle_ == -1)
		{
			handle_ = MV1DuplicateModel(originalHandle);
		}
	}

	inline int GetType(void) const { return type_; }

	inline Object* GetOwner() const { return owner_; }
	inline void SetOwner(Object* const owner) { owner_ = owner; }
};
