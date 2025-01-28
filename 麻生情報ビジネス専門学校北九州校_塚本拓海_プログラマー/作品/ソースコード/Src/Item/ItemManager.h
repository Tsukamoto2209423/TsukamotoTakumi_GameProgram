#pragma once

#include <vector>
#include <memory>
#include "ItemBase.h"
#include "ItemParameter.h"


namespace BOUDAMA
{
	//�A�C�e���p�Ǘ��N���X
	class ItemManager
	{
	private:
		//�A�C�e���p�x�N�^�[
		std::vector<std::shared_ptr<ItemBase>> items_;

	public:
		//�R���X�g���N�^
		ItemManager();

		//�f�X�g���N�^
		~ItemManager();

		//�����������֐�
		void Init(void);

		//�ǂݍ��ݏ����֐�
		void Load(void);

		//�s�������֐�
		void Step();

		//�`�揈���֐�
		void Draw(void);

		//�j�������֐�
		void Fin(void);

		void AppearanceRequest(const ITEM::ITEM_LIST itemNum);

		const std::shared_ptr<ItemBase>& SearchItem(const ITEM::ITEM_LIST itemNum) const;

		inline const std::vector<std::shared_ptr<ItemBase>>& GetItem() { return items_; }

	};
}
