#pragma once

#include <memory>
#include "Object/Object.h"

namespace BOUDAMA
{
	//アイテム用基底クラス
	class ItemBase : public Object
	{
	protected:
		bool playerOnlyEffect_;

	public:
		//コンストラクタ
		ItemBase() : playerOnlyEffect_(false) {}

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

		//プレイヤーのみ効果を受けられるアイテムか？
		bool IsPlayerOnlyEffect(void) const { return playerOnlyEffect_; }
	};
}
