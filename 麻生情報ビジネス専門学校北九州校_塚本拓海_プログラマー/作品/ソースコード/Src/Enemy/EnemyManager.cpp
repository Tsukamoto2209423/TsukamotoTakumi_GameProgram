#include <functional>

#include "DxLib.h"

#include "EnemyManager.h"
#include "Enemy.h"
#include "EnemyMonster.h"
#include "EnemyBomber.h"
#include "EnemyFlyweightImage.h"

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
	void EnemyManager::Init(const SCENE difficulty, const ItemManager& itemManager)
	{
		for (auto& countTime : appearCountTime_)
		{
			countTime = 0;
		}

		deathCount_ = 0;

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
			//お化けの爆弾を投げる敵
			[&]() { return std::make_shared<EnemyBomber>(itemManager.SearchItem(ITEM::ITEM_LIST::BOMB)); },
		};


		//それぞれの敵の最大数分、領域確保する
		for (const auto enemyKindNum : ENEMY_MANAGER::ENEMY_LIST())
		{
			//ノーマルモードなら通常の数、それ以外なら多くする
			int maxEnemyNum =
				(difficulty == SCENE::NORMAL_PLAY) ?
				ENEMY_MANAGER::MAX_NUM_LIST[static_cast<int>(enemyKindNum)] :
				ENEMY_MANAGER::HARD_MAX_NUM_LIST[static_cast<int>(enemyKindNum)];

			enemiesMaxNum_.emplace_back(maxEnemyNum);

			//記憶領域確保
			for (int enemyIndex = 0; enemyIndex < maxEnemyNum; ++enemyIndex)
			{
				enemies_.emplace_back(enemyList[static_cast<int>(enemyKindNum)]());
			}
		}

		//初期化
		for (const auto& enemy : enemies_)
		{
			enemy->Init();
			enemy->SetStateMachineOwner(enemy);
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
		int currentEnemyIndex = 0;

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
				enemies_[currentEnemyIndex]->Load(origineHandle);

				++currentEnemyIndex;
			}

			MV1DeleteModel(origineHandle);
		}

		EnemyFlyweightImage::Load();
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
		}

		if (isFeverTime_)
		{
			unsigned int color = GetColor(255, 0, 0);
			DrawFormatString(275, 300, color, "%d : FEVERTIME", deathCount_);
		}
	}

	//敵情報破棄
	void EnemyManager::Fin(void)
	{
		//破棄処理
		for (const auto& enemyItr : enemies_)
		{
			//モデルデータ等消去
			enemyItr->Fin();
		}

		enemiesMaxNum_.clear();
		enemiesMaxNum_.shrink_to_fit();

		EnemyFlyweightImage::Fin();
	}

	//出現処理を纏めた関数
	void EnemyManager::AppearanceCountProcess(void)
	{
		if (isFeverTime_)
		{
			AppearanceRequest();

			++feverTimeCount_;

			if (ENEMY_MANAGER::MAX_FEVER_TIME <= feverTimeCount_)
			{
				isFeverTime_ = false;
				feverTimeCount_ = 0;
			}

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

			//経過していたら実行
			if (ENEMY_MANAGER::APPEAR_MAX_TIME_LIST[kindNum] <= appearCountTime_[kindNum])
			{
				//計測初期化
				appearCountTime_[kindNum] = 0;

				//経過していたら
				AppearanceRequest(kindNum, enemyArrayIndex);
			}

			//次の敵の配列ブロックの先頭位置を取得
			enemyArrayIndex += enemiesMaxNum_[kindNum];
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
