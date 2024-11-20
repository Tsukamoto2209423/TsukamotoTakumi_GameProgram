#include <functional>
#include "DxLib.h"
#include "EnemyManager.h"
#include "Enemy.h"
#include "EnemyMonster.h"
#include "EnemyBomber.h"
#include "Player/Player.h"
#include "Common/Common.h"
#include <Input/GamePad/GamePad.h>
#include <Input/InputParameter.h>
#include <Effekseer/Effekseer.h>
#include <Effekseer/EffekseerParameter.h>

namespace BOUDAMA
{
	//コンストラクタ
	EnemyManager::EnemyManager()
	{
		exclamationMarkHandle_ = 0;
		appearCountTime_[0] = 0;
		deathCount_ = 0;
		feverTimeCount_ = 0;
		isFeverTime_ = false;
	}

	//デストラクタ
	EnemyManager::~EnemyManager()
	{

	}

	//敵情報初期化
	void EnemyManager::Init(const SCENE difficulty)
	{
		for (auto& countTime : appearCountTime_)
		{
			countTime = 0;
		}

		feverTimeCount_ = 0;

		isFeverTime_ = false;

		enemies_.clear();
		enemies_.shrink_to_fit();

		//敵一覧と生成方法を増やすだけで全ての敵を作成できるようにする
		const std::function<std::shared_ptr<EnemyBase>()> enemyList[static_cast<int>(ENEMY_MANAGER::ENEMY_LIST::ALL_NUM)] =
		{
			//赤いダルマ型の敵
			[]() { return std::make_shared<Enemy>(); },
			//紫の丸い怪物型の敵
			[]() { return std::make_shared<EnemyMonster>(); },
			//人型の爆弾を投げる敵
			[]() { return std::make_shared<EnemyBomber>(); },
		};

		//それぞれの敵の最大数分、領域確保する
		for (const auto enemyKindNum : ENEMY_MANAGER::ENEMY_LIST())
		{
			//ノーマルモードなら通常の数、それ以外なら多くする
			int maxEnemyNum =
				(difficulty == SCENE::NORMAL_PLAY) ?
				ENEMY_MANAGER::MAX_NUM_LIST[static_cast<int>(enemyKindNum)] :
				ENEMY_MANAGER::HARD_MAX_NUM_LIST[static_cast<int>(enemyKindNum)];

			//記憶領域確保
			for (int enemyIndex = 0; enemyIndex < maxEnemyNum; ++enemyIndex)
			{
				const auto& enemy = enemies_.emplace_back(enemyList[static_cast<int>(enemyKindNum)]());
				//初期化
				enemy->Init();
				enemy->SetStateMachineOwner(enemy);
			}
		}


		//最初に敵を出現させておく
		for (int appearNum = 0; const auto& enemy : enemies_)
		{
			enemy->AppearanceRequest();
			++appearNum;

			if (ENEMY_MANAGER::INIT_APPEAR_NUM <= appearNum)
			{
				break;
			}
		}
	}

	//読み込み処理関数
	void EnemyManager::Load(const SCENE difficulty)
	{
		auto&& enemy = enemies_.begin();

		//それぞれの敵の最大数分、モデル読み込み
		for (const auto enemyKindNum : ENEMY_MANAGER::ENEMY_LIST())
		{
			//元モデル読み込み処理
			const int origineHandle = MV1LoadModel(ENEMY_MANAGER::PATH_LIST[static_cast<int>(enemyKindNum)]);

			//ノーマルモードなら通常の数、それ以外なら多くする
			int maxEnemyNum =
				(difficulty == SCENE::NORMAL_PLAY ?
					ENEMY_MANAGER::MAX_NUM_LIST[static_cast<int>(enemyKindNum)] :
					ENEMY_MANAGER::HARD_MAX_NUM_LIST[static_cast<int>(enemyKindNum)]);

			//複製モデル読み込み処理
			for (int enemyIndex = 0; enemyIndex < maxEnemyNum; ++enemyIndex)
			{
				(*enemy)->Load(origineHandle);

				++enemy;
			}

			MV1DeleteModel(origineHandle);
		}

		exclamationMarkHandle_ = LoadGraph(ENEMY_MANAGER::EXCLAMATION_PATH);

	}

	//敵総合処理
	void EnemyManager::Step(const Vector3D& playerPos)
	{
		//行動処理
		for (const auto& enemy : enemies_)
		{
			enemy->Step(playerPos);
		}

		//出現処理計算
		AppearanceCountProcess();

	}

	//敵総合描画
	void EnemyManager::Draw(void)
	{
		//敵描画
		for (const auto& enemy : enemies_)
		{
			enemy->Draw();

			//プレイヤー発見状態なら「！」の画像を表示する
			if (enemy->GetState() == ENEMY::STATE::FIND_OUT)
			{
				DrawBillboard3D(enemy->GetPos() + ENEMY_MANAGER::ADD_EXCLAMATION_DISTANCE, 0.5f, 0.0f, 128.0f, 0.0f, exclamationMarkHandle_, true);
			}
		}
	}

	//敵情報破棄
	void EnemyManager::Fin(void)
	{
		//破棄処理
		DeleteGraph(exclamationMarkHandle_);
		exclamationMarkHandle_ = -1;

		//消去処理
		for (auto&& itr = enemies_.cbegin(); itr != enemies_.cend();)
		{
			//モデルデータ等消去
			(*itr)->Fin();
			//vectorから消去
			itr = enemies_.erase(itr);
		}

		//確保した記憶領域を再構築
		enemies_.clear();
		enemies_.shrink_to_fit();
	}

	//出現処理を纏めた関数
	void EnemyManager::AppearanceCountProcess(void)
	{
		if (isFeverTime_)
		{
			AppearanceRequest();

			return;
		}

		//敵の配列の添え字を指すときに使う変数
		int enemyArrayIndex = 0;

		//敵の出現処理
		for (const auto enemyKindNum : ENEMY_MANAGER::ENEMY_LIST())
		{
			int kindNum = static_cast<int>(enemyKindNum);

			//それぞれの敵の次に出現するまでの時間を計測する
			++appearCountTime_[kindNum];

			//経過していないなら実行しない
			if (appearCountTime_[kindNum] < ENEMY_MANAGER::APPEAR_MAX_TIME_LIST[kindNum])
			{
				//次の敵の配列ブロックの先頭位置を取得
				enemyArrayIndex += ENEMY_MANAGER::MAX_NUM_LIST[kindNum];

				continue;
			}

			//計測初期化
			appearCountTime_[kindNum] = 0;

			//経過していたら
			AppearanceRequest(kindNum, enemyArrayIndex);
		}
	}

	//実際に出現させる関数
	void EnemyManager::AppearanceRequest(int kindNum, int enemyArrayIndex)
	{
		//それぞれの敵の最大数分for文を回すために計算
		const int lastEnemyArrayIndex = enemyArrayIndex + ENEMY_MANAGER::MAX_NUM_LIST[kindNum];

		//出現処理処理
		for (int enemyIndex = enemyArrayIndex; enemyIndex < lastEnemyArrayIndex; ++enemyIndex)
		{
			//すでに出現している場合は次に移る
			if (enemies_[enemyIndex]->GetIsActive())
			{
				continue;
			}

			//敵を出現させる
			enemies_[enemyIndex]->AppearanceRequest();

			CEffekseerCtrl::Request(EFFECT::ENEMY_SPAWN, enemies_[enemyIndex]->GetPos(), false);

			break;
		}
	}
}
