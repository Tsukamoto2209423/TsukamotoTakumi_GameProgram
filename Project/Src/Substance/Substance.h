#pragma once

#include "SubstanceBase.h"

//物質クラス
class Substance : public SubstanceBase
{
private:

public:
	//コンストラクタ
	Substance() {}

	//デストラクタ
	~Substance() {}

	//初期化処理関数
	void Init();
};
