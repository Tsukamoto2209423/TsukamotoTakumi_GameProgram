#pragma once

#include "Vector/Vector3D.h"

//天球クラス
class SkyBox
{
private:
	//ハンドル
	int handle_;

	//位置
	Vector3D pos_;

	//角度θ
	Vector3D rot_;

public:
	//コンストラクタ
	SkyBox();
	//デストラクタ
	~SkyBox();

	//初期化処理関数
	void Init(void);

	//読み込み処理関数
	void Load(void);

	//更新処理関数
	void Step(void);

	//描画処理関数
	void Draw(void);

	//破棄処理関数
	void Fin(void);
};