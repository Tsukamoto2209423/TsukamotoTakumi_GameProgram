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
	//�R���X�g���N�^
	ItemManager::ItemManager()
	{

	}

	//�f�X�g���N�^
	ItemManager::~ItemManager()
	{

	}

	//�����������֐�
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

	//�ǂݍ��ݏ����֐�
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

	//�s�������֐�
	void ItemManager::Step()
	{
		for (const auto& item : items_)
		{
			item->Step();
		}
	}

	//�`�揈���֐�
	void ItemManager::Draw(void)
	{
		for (const auto& item : items_)
		{
			item->Draw();
		}
	}

	//�j�������֐�
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

	//�o������
	void ItemManager::AppearanceRequest(const ITEM::ITEM_LIST itemNum)
	{
		int vectorItemIndex = 0;

		int intItemNum = static_cast<int>(itemNum);

		//�A�C�e���̈ʒu�T��
		for (int index = 0; index < intItemNum; ++index)
		{
			vectorItemIndex += ITEM::ITEM_MAX_NUM_LIST[index];
		}

		//�A�C�e���̏o���ő吔�擾
		const int maxNum = ITEM::ITEM_MAX_NUM_LIST[intItemNum];

		//�o�����Ă��Ȃ��A�C�e����T��
		for (int count = 0; count < maxNum; ++count)
		{
			//���ɏo�����Ă���Ȃ���s���Ȃ�
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

		//�A�C�e���̈ʒu�T��
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
		std::cerr << "Debug break : �A�C�e�����������܂���ł����I" << std::endl;
		__debugbreak();
#endif // _DEBUG

		return items_.front();
	}
}
