#include "ItemManager.h"
#include "ItemParameter.h"
#include "Item/Bomb/Bomb.h"


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
	}

	//読み込み処理関数
	void ItemManager::Load(void)
	{
		const int origineHandle = MV1LoadModel(BOMB::PATH);

		for (const auto& item : items_)
		{
			item->Load(origineHandle);
		}

		MV1DeleteModel(origineHandle);
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

			//if (owner)
			//{
			//	//所有者設定
			//	items_[vectorItemIndex]->SetOwner(owner);
			//	items_[vectorItemIndex]->SetPos(owner->GetPos());
			//}

			items_[vectorItemIndex]->AppearanceRequest();

			return;
		}
	}

}
