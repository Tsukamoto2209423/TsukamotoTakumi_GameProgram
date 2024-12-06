#pragma once

#include <memory>
#include "Object/Object.h"

namespace BOUDAMA
{
	//アイテム用基底クラス
	class ItemBase : public Object
	{
	protected:
		std::weak_ptr<Object> owner_;

	public:
		//コンストラクタ
		ItemBase() {}

		//デストラクタ
		virtual ~ItemBase() = default;

		//読み込み処理関数
		virtual void Load(const int originalHandle)
		{
			if (handle_ == -1)
			{
				handle_ = MV1DuplicateModel(originalHandle);
			}
		}

		//出現処理関数
		virtual void AppearanceRequest(void) = 0;

		//アイテムの効果実行
		virtual void EffectExecute(const std::shared_ptr<Object>& targetObject) = 0;

		//所有者取得
		inline std::weak_ptr<Object> GetOwner(void) const { return owner_; }

		//所有者設定
		inline void SetOwner(const std::shared_ptr<Object>& owner) { owner_ = owner; }

	};
}
