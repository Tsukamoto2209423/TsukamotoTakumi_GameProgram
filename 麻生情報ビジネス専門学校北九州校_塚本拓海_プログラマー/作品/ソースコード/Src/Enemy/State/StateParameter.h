#pragma once

namespace BOUDAMA
{
	enum class ENEMY_STATE
	{
		//待機
		IDLE,

		//ランダムウォーク
		RANDOM_WALK,

		//プレイヤー探索
		SEARCH,

		//プレイヤー発見
		FIND_OUT,

		//プレイヤー追跡
		CHASE,

		//逃走中
		RUN_AWAY,

		//攻撃溜め
		CHARGE,

		//攻撃中
		ATTACK,

		//ノックバック
		KNOCK_BACK,

		//死体状態
		CORPSE
	};

}
