#pragma once

#include <vector>
#include "Vector/Vector3D.h"
#include "Player.h"

namespace PLAYER_EFFECT
{
	//プレイヤー情報をまとめたCSVファイル
	constexpr char PATH[] = "Data/Image/Player/ImageList.csv";

	//画像用
	enum IMAGE
	{
		//HP表示用のハンドル
		HP,

		//"HP"の画像のハンドル
		HP_CHARA,

		//集中線
		CONCENTRATION_LINE_1,
		CONCENTRATION_LINE_2,
		CONCENTRATION_LINE_3,
		CONCENTRATION_LINE_END,

		//ダメージを受けたときに画面に表示するダメージエフェクト画像
		DAMAGE,

		//画像の総数
		ALL_NUM
	};

	//HPバーの大きさ
	constexpr int HP_SIZE = 16;

	//HPバーの表示位置
	constexpr int HP_POS_X = 96;
	constexpr int HP_POS_Y = 32;

	//HPの表示位置
	constexpr int HP_CHARA_POS_X = 48;
	constexpr int HP_CHARA_POS_Y = 32;
}

//プレイヤーに関する画像を描画するクラス
class Player2DEffect
{
private:
	//参照するプレイヤーのポインタ
	Player* playerPointer_;

	//画像一覧表
	std::vector<int> handles_;

	//今描画している集中線の番号
	int concentrationLineIndex_;

	//ダメージ画像のα値
	int damageEffectAlpha_;

public:
	//コンストラクタ
	Player2DEffect(Player* const player) : playerPointer_(player),concentrationLineIndex_(0),damageEffectAlpha_(0) {};

	//デストラクタ	
	~Player2DEffect() {} ;

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

	void EffectRequest(void);

};
