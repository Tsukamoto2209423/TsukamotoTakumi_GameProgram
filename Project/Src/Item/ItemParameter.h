#pragma once

#include "Vector/Vector3D.h"

namespace BOUDAMA
{
	namespace BOMB
	{
		//画像パス
		constexpr char PATH[] = "Data/Model/Bomb/Beta_Bomb.x";

		//持たれたときに上に移動させる値
		constexpr Vector3D HELD_UP_DISTANCE = { 0.0f,50.0f,0.0f };

		//地面の位置
		constexpr float GROUND_POS = 20.5f;

		//重力
		constexpr float GRAVITY = 5.75f;

		//投擲の速さ
		constexpr float THROW_SPEED = 20.0f;

		//半径
		constexpr float RADIUS = 55.0f;

		//爆発の炎の半径
		constexpr float EXPLODE_RADIUS = 300.0f;

		//初期基準位置
		constexpr float INIT_POS_X_Z = -1000.0f;

		//X軸とZ軸で行ける最大の位置
		constexpr float MAX_POS_X_Z = 7000.0f;

		//攻撃力
		constexpr int ATTACK_POWER = 5;

		//ランダムで配置するときに初期基準位置に足す最大値
		constexpr int INIT_POS_XZ_RAND_MAX_NUM = 2 * static_cast<int>(-INIT_POS_X_Z);

		//同時に出現できる最大値
		constexpr int MAX_NUM = 3;

		//爆発するまでの制限時間
		constexpr int MAX_EXPLODE_TIME_LIMIT = 600;

		//爆発している時間
		constexpr int MAX_EXPLOSION_TIME = 90;

		enum STATE
		{
			NORMAL,
			THROW,
			EXPLOSION,

			NUM
		};
	}

	using BOMB_STATE = BOMB::STATE;


	namespace HEAL
	{
		//最大数
		constexpr int MAX_NUM = 3;

		//回復させる値
		constexpr int HEAL_VALUE = 5;

		//地面の位置
		constexpr float GROUND_POS = 20.5f;

		//重力
		constexpr float GRAVITY = 6.0f;

		//初期基準位置
		constexpr float INIT_POS_X_Z = -1000.0f;

		//ランダムで配置するときに初期基準位置に足す最大値
		constexpr int INIT_POS_XZ_RAND_MAX_NUM = 2 * static_cast<int>(-INIT_POS_X_Z);


		//上に移動させる値
		constexpr Vector3D UP_DISTANCE = { 0.0f,60.0f,0.0f };

	}

	namespace ITEM
	{
		enum class ITEM_LIST
		{
			BOMB,

			HEAL,

			ALL_NUM
		};


		constexpr int ITEM_MAX_NUM_LIST[static_cast<int>(ITEM_LIST::ALL_NUM)] =
		{
			BOMB::MAX_NUM,
			HEAL::MAX_NUM
		};
	}
}
