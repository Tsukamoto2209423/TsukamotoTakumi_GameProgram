#include "SubstanceManager.h"
#include <DxLib.h>
#include "BigSubstance.h"
#include "Substance/SubstanceParameter.h"

//コンストラクタ
SubstanceManager::SubstanceManager()
{

}

//デストラクタ
SubstanceManager::~SubstanceManager()
{

}

//初期化処理関数
void SubstanceManager::Init(void)
{
	//容量確保
	for (int num = 0; num < SUBSTANCE::MAX_NUM; ++num)
	{
		substances_.emplace_back(std::make_shared<Substance>());
	}

	for (int num = 0; num < BIGSUBSTANCE::MAX_NUM; ++num)
	{
		substances_.emplace_back(std::make_shared<BigSubstance>());
	}

	//初期化
	for (const auto& substance : substances_)
	{
		substance->Init();
	}

	for (int appearNum = 0; const auto& substance : substances_)
	{
		//初期に湧く物質
		substance->FlyAppearCalculation(SUBSTANCE::INIT_POS);
		++appearNum;

		//一定個数以上湧いたら脱出
		if (appearNum >= ALL_SUBSTANCE::INIT_APPEAR_NUM)
		{
			break;
		}
	}

}

//読み込み処理関数
void SubstanceManager::Load(void)
{
	//元モデルデータ読み込み処理
	int originalHandle = MV1LoadModel(SUBSTANCE::PATH);

	int originalBigHandle = MV1LoadModel(BIGSUBSTANCE::PATH);

	auto&& substance = substances_.begin();

	//複製モデルデータ読み込み処理
	for (int num = 0; num < SUBSTANCE::MAX_NUM; ++num)
	{
		(*substance)->Load(originalHandle);

		++substance;
	}

	for (int num = 0; num < BIGSUBSTANCE::MAX_NUM; ++num, ++substance)
	{
		(*substance)->Load(originalBigHandle);
	}

	MV1DeleteModel(originalHandle);

	MV1DeleteModel(originalBigHandle);

}

//行動処理関数
void SubstanceManager::Step(void)
{
	//一括行動処理
	for (const auto& substance : substances_)
	{
		substance->Step();
	}
}

//描画処理関数
void SubstanceManager::Draw(void)
{
	for (const auto& substance : substances_)
	{
		substance->Draw();
	}
}

//破棄処理関数
void SubstanceManager::Fin(void)
{
	for (auto&& substanceItr = substances_.cbegin(); substanceItr != substances_.cend();)
	{
		(*substanceItr)->Fin();
		substanceItr = substances_.erase(substanceItr);
	}

	substances_.clear();
	substances_.shrink_to_fit();
}

//引数の場所から飛び散りながら出現する処理
void SubstanceManager::FlyAppearCalculation(const Vector3D& appearPos)
{
	for (int appearNum = 0; const auto& substance : substances_)
	{
		if (substance->GetIsActive())
		{
			continue;
		}

		substance->FlyAppearCalculation(appearPos);

		++appearNum;

		//4個出現したら戻る
		if (appearNum >= ALL_SUBSTANCE::MAX_APPEAR_NUM)
		{
			return;
		}
	}
}

//ランダムに物質を抽選して引数の場所から飛び散りながら出現する処理
void SubstanceManager::RandomFlyAppearCalculation(const Vector3D& appearPos)
{
	std::vector<std::shared_ptr<SubstanceBase>> appearSubstances;

	std::vector<int> randomNums;

	//まだ出現していないものだけ抽出する
	for (int num = 0; const auto& substance : substances_)
	{
		if (substance->GetIsActive())
		{
			continue;
		}

		appearSubstances.emplace_back(substance);

		randomNums.emplace_back(num);

		++num;
	}

	/*
	*	出現させる数を決める
	*	出現できる数が、敵を倒したときに湧かせる数以上なら、敵を倒したときに湧かせる数を代入
	*	敵を倒したときに湧かせる数より、出現できる数が小さかった場合、出現できる数を代入
	*/
	unsigned int maxAppearNum = (ALL_SUBSTANCE::MAX_APPEAR_NUM <= randomNums.back() + 1 ? ALL_SUBSTANCE::MAX_APPEAR_NUM : randomNums.back() + 1);

	//後ろから範囲を縮小していくフィッシャー?イェーツのシャッフルを使う
	for (unsigned int appearCount = 0; appearCount < maxAppearNum; ++appearCount)
	{
		//出現させる添え字をランダムで決める
		int appearIndex = GetRand((maxAppearNum - 1) - appearCount);

		//出現処理
		appearSubstances[appearIndex]->FlyAppearCalculation(appearPos);

		//値交換処理
		int tempNum = randomNums[appearIndex];
		randomNums[appearIndex] = *(randomNums.end() - appearCount);
		*(randomNums.end() - appearCount) = tempNum;
	}
}
