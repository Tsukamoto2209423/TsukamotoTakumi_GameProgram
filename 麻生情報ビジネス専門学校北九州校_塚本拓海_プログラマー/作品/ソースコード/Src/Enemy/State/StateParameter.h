#pragma once

namespace BOUDAMA
{
	enum class ENEMY_STATE
	{
		//待機
		IDLE,

		//プレイヤー探索
		SEARCH,

		//プレイヤー発見
		FIND_OUT,

		//プレイヤー追跡
		CHASE,

		//攻撃溜め
		CHARGE,

		//攻撃中
		ATTACK,

		//ノックバック
		KNOCK_BACK,

	};

}
