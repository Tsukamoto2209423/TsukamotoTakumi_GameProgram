#pragma once

#include <Vector/Vector3D.h>

namespace PLAYER
{
	//プレイヤーのパス
	constexpr char PATH[] = { "Data/Model/Player/PlayerSyobon.x" };

	//プレイヤーの最大HP
	constexpr int MAX_HP = 50;

	//プレイヤー初期位置
	constexpr Vector3D INIT_POS = { 0.0f,100.0f,0.0f };

	//プレイヤーのエフェクトを出す位置
	constexpr Vector3D EFFECT_POS = { 20.0f,50.0f,-10.0f };

	//プレイヤーが行ける最大のX軸とZ軸の位置
	constexpr float MAX_POS_X_Z = 7000.0f;

	//プレイヤーの速さ
	constexpr float SPEED = 1.5f;

	//プレイヤーの最大の速さ
	constexpr float MAX_SPEED = 50.0f;

	//プレイヤーの最大の速さの二乗
	constexpr float MAX_SPEED_SQUARE = MAX_SPEED * MAX_SPEED;

	//ターボ状態のとき、〇ずつ速さに加算する
	constexpr float TURBO_CHARGE_POWER = 5.5f;

	//敵を倒せるようになる速度の二乗
	constexpr float KILL_SPEED = 1000.0f;

	//プレイヤーにかける重力
	constexpr float GRAVITY = 8.5f;

	//地面に着地したときの位置
	constexpr float GROUND_POS_Y = 35.0f;

	//回転したときにかける補正係数
	constexpr float ROTATION_COEFFICIENT = 0.0625f;

	//回転したときの摩擦係数
	constexpr float KINETIC_FRICTION_COEFFICIENT = 0.984375f;

}
