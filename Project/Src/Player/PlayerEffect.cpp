#include "Player/PlayerEffect.h"
#include <DxLib.h>
#include "PlayerParameter.h"
#include <FileLoader/CSVFileLoader.h>
#include <Effekseer/Effekseer.h>

#define IMAGE PLAYER_EFFECT::IMAGE

//コンストラクタ
PlayerEffect::PlayerEffect()
{
	concentrationLineIndex_ = 0;
	damageEffectAlpha_ = 0;
	chargeEffectHandle = 0;
	turboEffectHandle = 0;
}

//デストラクタ
PlayerEffect::~PlayerEffect()
{

}

//初期化処理関数
void PlayerEffect::Init(void)
{
	concentrationLineIndex_ = IMAGE::CONCENTRATION_LINE_1;
	damageEffectAlpha_ = 0;
	chargeEffectHandle = 0;
	turboEffectHandle = 0;
}

//読み込み処理関数
void PlayerEffect::Load(void)
{
	CSV_LOADER::LoadHandle(PLAYER_EFFECT::PATH, handles_);
}

//行動処理関数
void PlayerEffect::Step(void)
{
	if (damageEffectAlpha_ > 0)
	{
		damageEffectAlpha_ -= 3;
	}
}

//描画処理関数
void PlayerEffect::HPDraw(int playerHP)
{
	//HPに応じてHPバーの長さを変える
	for (int HP = 0; HP < playerHP; ++HP)
	{
		DrawRotaGraph(PLAYER_EFFECT::HP_POS_X + PLAYER_EFFECT::HP_SIZE * HP, PLAYER_EFFECT::HP_POS_Y, 1.0f, 0.0f, handles_[IMAGE::HP], true);
	}

	//「HP」の文字の画像表示
	DrawRotaGraph(PLAYER_EFFECT::HP_CHARA_POS_X, PLAYER_EFFECT::HP_CHARA_POS_Y, 0.5f, 0.0f, handles_[IMAGE::HP_CHARA], true);

}

//集中線描画関数
void PlayerEffect::LineDraw(void)
{
	//集中線描画
	DrawGraph(0, 0, handles_[concentrationLineIndex_], true);

	//集中線の繰り返し処理
	concentrationLineIndex_ >= IMAGE::CONCENTRATION_LINE_END ? 
		concentrationLineIndex_ = IMAGE::CONCENTRATION_LINE_1 : ++concentrationLineIndex_;
}

//ダメージを受けた時のエフェクト描画関数
void PlayerEffect::DamageDraw(void)
{
	if (damageEffectAlpha_ > 0)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, damageEffectAlpha_);
		DrawGraph(0, 0, handles_[IMAGE::DAMAGE], true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

//破棄処理関数
void PlayerEffect::Fin(void)
{
	for (auto&& image : handles_)
	{
		DeleteGraph(image);
	}
}

void PlayerEffect::DamageEffectRequest(void)
{
	damageEffectAlpha_ = 255;
}

void PlayerEffect::ChargeEffectRequest(const Vector3D& appearPos, float rotY)
{
	chargeEffectHandle = CEffekseerCtrl::Request(3, appearPos, false);
	CEffekseerCtrl::SetRot(chargeEffectHandle, VECTOR(0.0f, rotY, 0.0f));
}

void PlayerEffect::TurboEffectRequest(const Vector3D& appearPos, float rotY)
{
	turboEffectHandle = CEffekseerCtrl::Request(4, appearPos, false);
	CEffekseerCtrl::SetRot(turboEffectHandle, VECTOR(0.0f, rotY, 0.0f));
	CEffekseerCtrl::SetPosition(turboEffectHandle, appearPos);
}
