#pragma once

#include <memory>
#include "Vector/Vector3D.h"
#include "Object/Object.h"

//固有の状態の抽象クラス
class StateBase
{
protected:
	//状態の所有者
	std::weak_ptr<Object> owner_;

public:
	StateBase() = default;
	StateBase(const std::shared_ptr<Object>& owner) : owner_(owner) {};

	~StateBase() = default;

	//初期化処理関数
	virtual void Init(void) = 0;

	//行動処理関数
	virtual void Step(void) = 0;

};
