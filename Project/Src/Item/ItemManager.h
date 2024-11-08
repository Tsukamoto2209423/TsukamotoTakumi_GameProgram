#pragma once

#include <vector>
#include <memory>
#include "ItemBase.h"
#include "ItemParameter.h"

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

		void AppearanceRequest(const std::shared_ptr<Object>& owner, const ITEM::ITEM_LIST itemNum);

		inline const std::vector<std::shared_ptr<ItemBase>>& GetItemManager() { return items_; }

	};
}
