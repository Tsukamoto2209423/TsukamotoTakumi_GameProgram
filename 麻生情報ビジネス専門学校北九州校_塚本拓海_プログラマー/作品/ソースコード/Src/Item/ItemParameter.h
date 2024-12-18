#pragma once

#include "Vector/Vector3D.h"

namespace BOUDAMA
{
	namespace BOMB
	{
		//モデルパス
		constexpr char PATH[] = "Data/Model/Bomb/Beta_Bomb.x";

		//持たれたときに上に移動させる値
		constexpr Vector3D HOLD_UP_DISTANCE = { 0.0f,115.0f,0.0f };

		//地面の位置
		constexpr float GROUND_POS = 40.5f;

		//重力
		constexpr float GRAVITY = 7.75f;

		//投擲時の速さ
		constexpr float THROW_SPEED = 55.0f;

		//半径
		constexpr float RADIUS = 55.0f;

		//爆発したときの半径
		constexpr float EXPLODE_RADIUS = 500.0f;

		//爆発したときに被弾相手に与える速さのブースト
		constexpr float EXPLOSION_BOOST = 35.0f;


		//初期基準位置
		constexpr float INIT_POS_X_Z = -1000.0f;

		//X軸とZ軸で行ける最大の位置
		constexpr float MAX_POS_X_Z = 7000.0f;

		//攻撃力
		constexpr int ATTACK_POWER = 5;

		//ランダムで配置するときに初期基準位置に足す最大値
		constexpr int INIT_POS_XZ_RAND_MAX_NUM = 2 * static_cast<int>(-INIT_POS_X_Z);

		//同時に出現できる最大数
		constexpr int MAX_NUM = 5;

		//爆発するまでの時間
		constexpr int MAX_EXPLODE_TIME_LIMIT = 200;

		//爆発している時間
		constexpr int MAX_EXPLOSION_TIME = 75;

		//爆発警告点滅
		constexpr int WARNING_BLINK_TIME = 80;

		enum STATE
		{
			NORMAL,
			IGNITION,
			TRIGGER,
			EXPLOSION,


			NUM
		};
	}

	using BOMB_STATE = BOMB::STATE;


	namespace HEAL
	{
		//画像パス
		constexpr char PATH[] = "Data/Model/Heal/HealItem.x";

		//最大数
		constexpr int MAX_NUM = 3;

		//回復させる値
		constexpr int HEAL_VALUE = 5;

		//半径
		constexpr float RADIUS = 85.0f;

		//地面の位置
		constexpr float GROUND_POS = 95.5f;

		//重力
		constexpr float GRAVITY = 6.0f;

		//初期基準位置
		constexpr float INIT_POS_X_Z = -1000.0f;

		//ランダムで配置するときに初期基準位置に足す最大値
		constexpr int INIT_POS_XZ_RAND_MAX_NUM = 2 * static_cast<int>(-INIT_POS_X_Z);


		//漂う動きをさせるために正弦波にかける係数
		constexpr float FLOAT_MOTION_BOOST = 1.5f;

		//上に移動させる値
		constexpr Vector3D UP_DISTANCE = { 0.0f,60.0f,0.0f };

	}

	namespace ITEM
	{
		enum class ITEM_LIST
		{
			BOMB,

			HEAL
		};


		constexpr int ITEM_MAX_NUM_LIST[] =
		{
			BOMB::MAX_NUM,
			HEAL::MAX_NUM
		};
	}

	using ITEM_LIST = ITEM::ITEM_LIST;
}
