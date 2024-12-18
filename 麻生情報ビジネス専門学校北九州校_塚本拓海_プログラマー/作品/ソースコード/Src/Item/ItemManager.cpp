#include "ItemManager.h"
#include "ItemParameter.h"
#include "Item/Bomb/Bomb.h"
#include "Heal/Heal.h"


#ifdef _DEBUG

#include <iostream>
#include <intrin.h>

#endif

namespace BOUDAMA
{
	//コンストラクタ
	ItemManager::ItemManager()
	{

	}

	//デストラクタ
	ItemManager::~ItemManager()
	{

	}

	//初期化処理関数
	void ItemManager::Init(void)
	{
		for (int index = 0; index < BOMB::MAX_NUM; ++index)
		{
			const auto& item = items_.emplace_back(std::make_shared<Bomb>());
			item->Init();
		}

		for (int index = 0; index < HEAL::MAX_NUM; ++index)
		{
			const auto& item = items_.emplace_back(std::make_shared<Heal>());
			item->Init();
		}
	}

	//読み込み処理関数
	void ItemManager::Load(void)
	{
		int itemIndex = 0;

		const int origineBombHandle = MV1LoadModel(BOMB::PATH);

		for (int index = 0; index < BOMB::MAX_NUM; ++index)
		{
			items_[index]->Load(origineBombHandle);

			++itemIndex;
		}

		MV1DeleteModel(origineBombHandle);

		const int origineHealHandle = MV1LoadModel(HEAL::PATH);

		for (int index = 0; index < HEAL::MAX_NUM; ++index)
		{
			items_[itemIndex]->Load(origineHealHandle);

			++itemIndex;
		}

		MV1DeleteModel(origineHealHandle);
	}

	//行動処理関数
	void ItemManager::Step()
	{
		for (const auto& item : items_)
		{
			item->Step();
		}
	}

	//描画処理関数
	void ItemManager::Draw(void)
	{
		for (const auto& item : items_)
		{
			item->Draw();
		}
	}

	//破棄処理関数
	void ItemManager::Fin(void)
	{
		for (auto&& itemItr = items_.cbegin(); itemItr != items_.cend();)
		{
			(*itemItr)->Fin();
			itemItr = items_.erase(itemItr);
		}

		items_.clear();
		items_.shrink_to_fit();
	}

	//出現処理
	void ItemManager::AppearanceRequest(const ITEM::ITEM_LIST itemNum)
	{
		int vectorItemIndex = 0;

		int intItemNum = static_cast<int>(itemNum);

		//アイテムの位置探索
		for (int index = 0; index < intItemNum; ++index)
		{
			vectorItemIndex += ITEM::ITEM_MAX_NUM_LIST[index];
		}

		//アイテムの出現最大数取得
		const int maxNum = ITEM::ITEM_MAX_NUM_LIST[intItemNum];

		//出現していないアイテムを探す
		for (int count = 0; count < maxNum; ++count)
		{
			//既に出現しているなら実行しない
			if (items_[vectorItemIndex]->GetIsActive())
			{
				++vectorItemIndex;
				continue;
			}



			items_[vectorItemIndex]->AppearanceRequest();

			return;
		}
	}

	const std::shared_ptr<ItemBase>& ItemManager::SearchItem(const ITEM::ITEM_LIST itemNum) const
	{
		int vectorItemIndex = 0;

		int intItemNum = static_cast<int>(itemNum);

		//アイテムの位置探索
		for (int index = 0; index < intItemNum; ++index)
		{
			vectorItemIndex += ITEM::ITEM_MAX_NUM_LIST[index];
		}

		int maxNum = ITEM::ITEM_MAX_NUM_LIST[intItemNum];

		for (int num = 0; num < maxNum; ++num, ++vectorItemIndex)
		{
			if (items_[vectorItemIndex]->GetIsActive())
			{
				continue;
			}

			items_[vectorItemIndex]->SetIsActive(true);

			return items_[vectorItemIndex];

		}


#ifdef _DEBUG
		std::cerr << "Debug break : アイテムを見つけられませんでした！" << std::endl;
		__debugbreak();
#endif // _DEBUG

		return items_.front();
	}
}
