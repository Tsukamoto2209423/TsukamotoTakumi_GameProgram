#pragma once

#include <vector>
#include <memory>
#include "ItemBase.h"
#include "ItemParameter.h"

#ifdef _DEBUG

#include <iostream>
#include <intrin.h>

#endif

namespace BOUDAMA
{
	//アイテム用管理クラス
	class ItemManager
	{
	private:
		//アイテム用ベクター
		std::vector<std::shared_ptr<ItemBase>> items_;

	public:
		//コンストラクタ
		ItemManager();

		//デストラクタ
		~ItemManager();

		//初期化処理関数
		void Init(void);

		//読み込み処理関数
		void Load(void);

		//行動処理関数
		void Step();

		//描画処理関数
		void Draw(void);

		//破棄処理関数
		void Fin(void);

		void AppearanceRequest(const ITEM::ITEM_LIST itemNum);

		const auto& SearchItem(const ITEM::ITEM_LIST itemNum) const
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

			return *items_.begin();
		}


		inline const std::vector<std::shared_ptr<ItemBase>>& GetItem() { return items_; }

	};
}
