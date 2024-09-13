#pragma once

//全ての物質に共通する値
namespace ALL_SUBSTANCE
{
	//ゲーム開始時に湧かせる数
	constexpr int INIT_APPEAR_NUM = 20;

	//敵を倒したときに湧かせる数
	constexpr int MAX_APPEAR_NUM = 5;


	//重力
	constexpr float GRAVITY = 5.5f;

	//地面位置
	constexpr float GROUND_POS = 21.0f;

	//減速処理をするときにかける値
	constexpr float RESISTANCE_POWER = 0.9f;

	//X軸とZ軸で行ける最大の位置
	constexpr float MAX_POS_X_Z = 7000.0f;

}

//物質
namespace SUBSTANCE
{
	constexpr char PATH[] = "Data/Model/Substance/Substance.x";

	constexpr int ADD_SCORE_NUM = 150;

	constexpr short int MAX_NUM = 500;

	constexpr Vector3D INIT_POS = { 0.0f,70.0f,500.0f };

	constexpr float RADIUS = 17.0f;

	constexpr float GRAVITY = 5.5f;

}

//ドデカ物質
namespace BIGSUBSTANCE
{
	constexpr char PATH[] = "Data/Model/Substance/BigSubstance.x";

	constexpr int ADD_SCORE_NUM = 200;

	constexpr short int MAX_NUM = 100;

	constexpr Vector3D INIT_POS = { 0.0f,60.0f,500.0f };

	constexpr float RADIUS = 50.0f;
}