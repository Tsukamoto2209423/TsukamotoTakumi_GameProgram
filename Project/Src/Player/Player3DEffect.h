#pragma once

#include <vector>
#include <type_traits>

#include <Vector/Vector3D.h>
#include "Player.h"

//プレイヤーに関する3Dエフェクトを描画するクラス
class Player3DEffect
{
private:
	//参照するプレイヤーのポインタ
	Player* playerPointer_;

	//呼び出したエフェクトのハンドルを保存する変数
	std::vector<int> effectHandle_;

	//エフェクトを呼び出すときに使う変数
	std::vector<int> effectCallNum_;

public:
	//コンストラクタ
	Player3DEffect(Player* const player) : playerPointer_(player) {};

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
	void EffectRequest(EFFECT_3D effectNum);
};

//エフェクト配列の添え字
enum EFFECT_3D
{
	CHARGE,
	ACCELERATOR,
};

//エフェクト自体を保存している配列の添え字を呼び出す時に使う番号
enum class EFFECT_CALL
{
	CHARGE = EFFECT::CHARGE,
	ACCELERATOR = EFFECT::ACCELERATOR,

	ALL_NUM
};

constexpr EFFECT_CALL begin(EFFECT_CALL) { return EFFECT_CALL::CHARGE; }

constexpr EFFECT_CALL end(EFFECT_CALL) { return EFFECT_CALL::ALL_NUM; }

constexpr EFFECT_CALL operator*(EFFECT_CALL dir) { return dir; }

constexpr EFFECT_CALL operator++(EFFECT_CALL& dir)
{
	return dir = EFFECT_CALL(std::underlying_type_t<EFFECT_CALL>(dir) + 1);
}
