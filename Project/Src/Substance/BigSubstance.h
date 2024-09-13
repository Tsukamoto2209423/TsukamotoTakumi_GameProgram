#pragma once

#include "SubstanceBase.h"

//大物質クラス
class BigSubstance : public SubstanceBase
{
private:

public:
	//コンストラクタ
	BigSubstance();

	//デストラクタ
	~BigSubstance();

	//初期化処理関数
	void Init(void) override;

	//読み込み処理関数
	void Load(int origineHandle) override;
};
