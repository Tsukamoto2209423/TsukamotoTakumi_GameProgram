#include "Player/Player3DEffect.h"
#include "Effekseer/Effekseer.h"
#include "Effekseer/EffekseerParameter.h"

//初期化処理関数
void Player3DEffect::Init(void)
{
	for (int index = 0; const auto& effectCallNum : EFFECT_CALL())
	{
		effectCallNum_[index] = static_cast<int>(effectCallNum);
	}
}

//読み込み処理関数
void Player3DEffect::Load(void)
{

}

//行動処理関数
void Player3DEffect::Step(void)
{

}

//描画処理関数
void Player3DEffect::Draw(void)
{

}

//破棄処理関数
void Player3DEffect::Fin(void)
{

}

//エフェクト表示
void Player3DEffect::EffectRequest(EFFECT_3D effectNum)
{
	effectHandle_[effectNum] = CEffekseerCtrl::Request(effectCallNum_[effectNum], playerPointer_->GetPos(), false);
	CEffekseerCtrl::SetRot(effectHandle_[effectNum], VECTOR(0.0f, playerPointer_->GetRotY(), 0.0f));
	CEffekseerCtrl::SetPosition(effectHandle_[effectNum], playerPointer_->GetPos());
}