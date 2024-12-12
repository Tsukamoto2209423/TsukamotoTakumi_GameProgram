#pragma once

#include "Vector/Vector3D.h"
#include <type_traits>

namespace BOUDAMA
{
	//敵の定義情報

	//ダルマ
	namespace DARUMA
	{
		//敵のパス
		constexpr char PATH[] = "Data/Model/Enemy/darumaEnemy.x";

		//敵の最大数
		constexpr int MAX_NUM = 40;

		//ハードモードかエンドレスモードの敵の最大数
		constexpr int HARD_MAX_NUM = 80;

		//体力
		constexpr int HP = 5;

		//半径
		constexpr float RADIUS = 50.0f;

		//速さ
		constexpr float SPEED = 7.5f;

		//重力
		constexpr float GRAVITY = 5.5f;

		//初期位置
		constexpr Vector3D INIT_POS = { 0.0f,100.0f,3750.0f };

		//敵のX軸の初期位置
		constexpr float INIT_POS_X = 500.0f;

		//敵のZ軸の初期位置
		constexpr float INIT_POS_Z = 3150.0f;

		//X軸とZ軸で行ける最大の位置
		constexpr float MAX_POS_X_Z = 7000.0f;

		//敵のX軸の出現範囲
		constexpr int INIT_MAX_APPEAR_RANGE_X = 1000;

		//敵のZ軸の出現範囲
		constexpr int INIT_MAX_APPEAR_RANGE_Z = 100;

		//〇Fごとに出現する
		constexpr int APPEAR_MAX_TIME = 30;

		//倒されたときにスコアに加算される点数
		constexpr unsigned int ADD_SCORE_NUM = 300;

	}

	//怪物
	namespace MONSTER
	{
		//敵のパス
		constexpr char PATH[] = "Data/Model/Enemy/MonsterEnemy.x";


		//敵の最大数
		constexpr int MAX_NUM = 5;

		//ハードモードかエンドレスモードの敵の最大数
		constexpr int HARD_MAX_NUM = 10;

		//体力
		constexpr int HP = 5;

		//移動する角度切り替え時間
		constexpr int DIRECTION_CHANGE_INTERVAL = 180;

		//移動する角度切り替え時間
		constexpr int REACTION_MAX_TIME = 120;

		//攻撃溜め最大時間
		constexpr int ATTACK_CHARGE_MAX_TIME = 60;

		//攻撃時間の最大値
		constexpr int ATTACK_MAX_TIME = 120;

		//攻撃後の硬直時間
		constexpr int ATTACK_STUN_TIME = 60;

		//〇Fごとに出現する
		constexpr int APPEAR_MAX_TIME = 90;


		//倒されたときにスコアに加算される点数
		constexpr unsigned int ADD_SCORE_NUM = 500;


		//X軸とZ軸で行ける最大の位置
		constexpr float MAX_POS_X_Z = 7000.0f;

		//地面に着地したときの位置
		constexpr float GROUND_POS_Y = 35.0f;

		//ノックバックのときに〇ずつ上昇させる
		constexpr float KNOCKBACK_Y_POWER = 6.5f;

		//半径
		constexpr float RADIUS = 80.0f;

		//速さ
		constexpr float SPEED = 2.0f;

		//追いかける速さ
		constexpr float CHASE_SPEED = 11.75f;

		//攻撃するときの速さ
		constexpr float ATTACK_SPEED = 50.0f;

		//移動時の最大の速さ
		constexpr float MAX_SPEED = 25.0f;

		//敵を発見できる範囲
		constexpr float FIND_OUT_RANGE = 1000.0f;

		//敵を発見できる範囲の二乗
		constexpr float SQUARE_FIND_OUT_RANGE = FIND_OUT_RANGE * FIND_OUT_RANGE;

		//重力
		constexpr float GRAVITY = 7.5f;


		//初期基準位置
		constexpr Vector3D INIT_POS = { 0.0f,100.0f,1450.0f };

		//敵の上に出現する「！」の距離(X軸,Y軸,Z軸)
		constexpr Vector3D ADD_EXCLAMATION_DISTANCE = { 0.0f, 75.0f, 0.0f };

	}

	//爆弾魔
	namespace BOMBER
	{
		//敵のパス
		constexpr char PATH[] = "Data/Model/Enemy/BomberEnemy.x";

		//敵の最大数
		constexpr int MAX_NUM = 1;

		//ハードモードかエンドレスモードの敵の最大数
		constexpr int HARD_MAX_NUM = 1;


		//移動する角度切り替え時間
		constexpr int DIRECTION_CHANGE_INTERVAL = 180;

		//敵を発見したときの驚いて反応する時間
		constexpr int REACTION_MAX_TIME = 120;


		//攻撃後の硬直時間
		constexpr int ATTACK_STUN_TIME = 550;

		//〇Fごとに出現する
		constexpr int APPEAR_MAX_TIME = 90;

		//体力
		constexpr int HP = 10;


		//倒されたときにスコアに加算される点数
		constexpr unsigned int ADD_SCORE_NUM = 550;

		//初期位置
		constexpr Vector3D INIT_POS = { 0.0f,150.0f,3150.0f };

		//敵の上に出現する「！」の距離(X軸,Y軸,Z軸)
		constexpr Vector3D ADD_EXCLAMATION_DISTANCE = { 0.0f, 75.0f, 0.0f };

		//X軸とZ軸で行ける最大の位置
		constexpr float MAX_POS_X_Z = 7000.0f;

		//1フレームで移動する速さ
		constexpr float SPEED = 1.75f;

		//最大の速さ
		constexpr float MAX_SPEED = 10.5f;

		//追いかける速さ
		constexpr float CHASE_SPEED = 7.5f;
		
		//漂う動きをさせるために正弦波にかける係数
		constexpr float FLOAT_MOTION_BOOST = 3.5f;

		//地面に着地したときの位置
		constexpr float GROUND_POS_Y = 100.0f;

		//重力
		constexpr float GRAVITY = 1.5f;

		//半径
		constexpr float RADIUS = 50.0f;


		//敵を発見できる範囲
		constexpr float FIND_OUT_RANGE = 850.0f;

		//敵を発見できる範囲の二乗
		constexpr float SQUARE_FIND_OUT_RANGE = FIND_OUT_RANGE * FIND_OUT_RANGE;


		//敵を発見したときに近づく最小の範囲
		constexpr float CHASE_MIN_RANGE = 655.0f;

		//敵を発見したときに近づく最小の範囲の二乗
		constexpr float SQUARE_CHASE_MIN_RANGE = CHASE_MIN_RANGE * CHASE_MIN_RANGE;

	}

	/*
		敵管理クラスの情報
		これより下に
		namespace 〇〇(敵の情報)
		を書くとエラーが起こるので追加しない
	*/
	namespace ENEMY_MANAGER
	{
		//ゲーム開始時に湧かせる数
		constexpr int INIT_APPEAR_NUM = 15;

		//敵は〇Fごとに出現する
		constexpr int APPEAR_TIME_INTERVAL = 20;

		//X軸とZ軸で行ける最大の位置
		constexpr float MAX_POS_X_Z = 7000.0f;

		//敵の上に出現する「！」の距離(X軸,Y軸,Z軸)
		constexpr Vector3D ADD_EXCLAMATION_DISTANCE = { 0.0f, 75.0f, 0.0f };

		//敵一覧
		enum class ENEMY_LIST
		{
			DARUMA,
			MONSTER,
			BOMBER,

			ALL_NUM
		};

		//通常の敵の数
		constexpr int MAX_NUM_LIST[static_cast<int>(ENEMY_LIST::ALL_NUM)] =
		{
			DARUMA::MAX_NUM,
			MONSTER::MAX_NUM,
			BOMBER::MAX_NUM
		};

		//ハードモードかエンドレスモードの敵の数
		constexpr int HARD_MAX_NUM_LIST[static_cast<int>(ENEMY_LIST::ALL_NUM)] =
		{
			DARUMA::HARD_MAX_NUM,
			MONSTER::HARD_MAX_NUM,
			BOMBER::HARD_MAX_NUM
		};

		//敵の出現間隔一覧表
		constexpr int APPEAR_MAX_TIME_LIST[static_cast<int>(ENEMY_LIST::ALL_NUM)] =
		{
			DARUMA::APPEAR_MAX_TIME,
			MONSTER::APPEAR_MAX_TIME,
			BOMBER::APPEAR_MAX_TIME
		};

		//敵のパス一覧表
		constexpr const char* PATH_LIST[static_cast<int>(ENEMY_LIST::ALL_NUM)] =
		{
			DARUMA::PATH,
			MONSTER::PATH,
			BOMBER::PATH
		};



		//範囲for文でつかうもの
		constexpr ENEMY_LIST begin(ENEMY_LIST) { return ENEMY_LIST::DARUMA; }

		constexpr ENEMY_LIST end(ENEMY_LIST) { return ENEMY_LIST::ALL_NUM; }

		constexpr ENEMY_LIST operator*(ENEMY_LIST dir) { return dir; }

		constexpr ENEMY_LIST operator++(ENEMY_LIST& dir)
		{
			return dir = ENEMY_LIST(std::underlying_type_t<ENEMY_LIST>(dir) + 1);
		}

	}
}
