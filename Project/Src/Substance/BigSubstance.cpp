#include "BigSubstance.h"
#include "Math/MyMath.h"
#include "SubstanceParameter.h"

//コンストラクタ
BigSubstance::BigSubstance()
{

}

//デストラクタ
BigSubstance::~BigSubstance()
{

}

//初期化処理関数
void BigSubstance::Init(void)
{
	//初期化
	handle_ = -1;
	isAlive_ = false;
	pos_ = { static_cast<float>(GetRand(600)),20.0f ,static_cast<float>(GetRand(600)) };
	velocity_ = MY_MATH::ZERO_VECTOR_3D;
	rot_ = MY_MATH::ZERO_VECTOR_3D;
	radius_ = BIGSUBSTANCE::RADIUS;

	addScoreNum = BIGSUBSTANCE::ADD_SCORE_NUM;
}


//読み込み処理関数
void BigSubstance::Load(int origineHandle)
{
	//複製モデルデータ読み込み処理
	handle_ = MV1DuplicateModel(origineHandle);
	MV1SetScale(handle_, VECTOR(2.0f, 2.0f, 2.0f));
}
