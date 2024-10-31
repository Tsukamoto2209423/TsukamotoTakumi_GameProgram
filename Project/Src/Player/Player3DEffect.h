#pragma once

#include <vector>

#include <Vector/Vector3D.h>

#include <EffekseerParameter.h>

namespace BOUDAMA
{
	//エフェクトハンドル配列の添え字
	enum EFFECT_HANDLE
	{
		CHARGE_INDEX,
		ACCELERATOR_INDEX,
		DAMAGE_INDEX,
		DEATH_INDEX
	};

	//エフェクト自体を保存している配列の添え字を呼び出す時に使う番号
	constexpr int  EFFECT_CALL[] =
	{
		EFFECT::CHARGE,
		EFFECT::ACCELERATOR,
		EFFECT::HIT_EFFECT,

		EFFECT::PLAYER_DEATH,
	};


	//プレイヤーに関する3Dエフェクトを描画するクラス
	class Player3DEffect final
	{
	private:
		//呼び出したエフェクトのハンドルを保存する変数
		std::vector<int> effectHandle_;

	public:
		//コンストラクタ
		Player3DEffect() {};

		//デストラクタ
		~Player3DEffect() {};

		//初期化処理関数
		void Init(void);

		//読み込み処理関数
		void Load(void);

		//行動処理関数
		void Step(void);

		//描画処理関数
		void Draw(void);

		//破棄処理関数
		void Fin(void);

		//エフェクト表示
		void EffectRequest(EFFECT_HANDLE effectNum, const Vector3D& appearPos, float rotY);
	};
}
