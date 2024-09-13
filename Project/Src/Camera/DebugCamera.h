#pragma once

#include "CameraBase.h"

class DebugCamera : public CameraBase
{
private:

public:
	//コンストラクタ
	DebugCamera() {}

	//デストラクタ
	~DebugCamera() {}

	//初期化処理関数
	void Init(void) override;

	//移動処理関数
	void Step(const Vector3D& playerPos) override;

	//更新関数
	void UpDate(void) override;
};