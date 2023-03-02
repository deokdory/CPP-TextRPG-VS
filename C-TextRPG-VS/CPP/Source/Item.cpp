#include "Item.h"

#include "pch.h"

Item::Item()
    : index(0),
      name("null"),
      description("null"),
      item_type(ItemType::NONE),
      price(0) {}
Item::Item(int _index, std::string _name, std::string _description,
           ItemType _type, int _price)
    : index(_index),
      name(_name),
      description(_description),
      item_type(_type),
      price(_price) {}

void Item::SetName(std::string _name) { name = _name; }
void Item::SetItemType(ItemType _item_type) { item_type = _item_type; }

void Item::Use(Character& character) { std::cout << "NULL ITEM" << std::endl; }

Item::~Item() {}

Potion::Potion(int _index, std::string _name, std::string _description,
               ItemType _item_type, int _amount, PotionType _potion_type,
               int _price)
    : Item(_index, _name, _description, _item_type, _price),
      amount(_amount),
      potion_type(_potion_type) {}

void Potion::Use(Character& character) {
  switch (potion_type) {
    case PotionType::HP_RECOVER: {
      int recovered = 0;
      if (character.GetMaxHp() - character.GetHp() < amount) {
        recovered = character.GetMaxHp() - character.GetHp();
      } else {
        recovered = amount;
      }
      character.SetHp(character.GetHp() + recovered);
      std::cout << character.GetName() << "�� ü���� " << recovered
                << "��ŭ ȸ���Ǿ���!" << std::endl;
      break;
    }
    default: {
      std::cout << "ERROR:Undefined Potion Type" << std::endl;
    }
  }
}

void Potion::PrintDescription() {
  switch (potion_type) {
    case PotionType::HP_RECOVER: {
      std::cout << "HP�� " << amount << "��ŭ ȸ���մϴ�." << std::endl;
      break;
    }
    default: {
      std::cout << "Undefined PotionType" << std::endl;
    }
  }
  std::cout << GetDescription() << std::endl;
}
Item* NewItem(int _index) {
  Item* new_item = nullptr;
  if (1 <= _index && _index <= 30) {
    return NewPotion(_index);
  }  // ���� Index
  // else if (1001 <= _index && _index <= 1500) {
  //  return NewQuestItem(_index);
  //}  // ����Ʈ������ Index
  else {
    // std::cout << "Undefined Item Index" << std::endl;
    // system("pause");
    return nullptr;
  }
}

Item* NewPotion(int _index) {
  if (_index > 30) {
    // std::cout << "ERROR:Potion Index is 1~30" << std::endl;
    // system("pause");
    return nullptr;
  }
  std::string name = "null";
  std::string description = "null";
  ItemType item_type = ItemType::POTION;
  int amount = 0;
  PotionType potion_type = PotionType::NONE;
  int price = 0;

  switch (_index) {
    case S_HP_POTION: {
      name = "HP����(��)";
      description = "���� ���� ���� ���� ��ü�� ����ִ�.";
      amount = 30;
      potion_type = PotionType::HP_RECOVER;
      price = 40;
      break;
    }
    case M_HP_POTION: {
      name = "HP����(��)";
      description = "������ ũ���� ���� ���� ���� ��ü�� ����ִ�.";
      amount = 50;
      potion_type = PotionType::HP_RECOVER;
      price = 60;
      break;
    }
    case L_HP_POTION: {
      name = "HP����(��)";
      description = "ū ���� ���� ���� ��ü�� ����ִ�.";
      amount = 80;
      potion_type = PotionType::HP_RECOVER;
      price = 100;
      break;
    }
    default: {
      // std::cout << "ERROR:Undefined Potion Index" << std::endl;
      // system("pause");
      return nullptr;
    }
  }
  return new Potion(_index, name, description, item_type, amount, potion_type,
                    price);
}

/*
Item* NewQuestItem(int _index) {
  if (1001 > _index && _index > 1500) {
    std::cout << "QuestItem index is 1001 ~ 1500" << std::endl;
    system("pause");
    return nullptr;
  }
  int index = _index;
  std::string name = "null";
  std::string description = "null";
  ItemType item_type = ItemType::QUEST_ITEM;

  switch (index) {
    case WOLF_TOOTH: {
      name = "������ �̻�";
      description = "���븦 ��� ���� ����ǰ�̴�.";
    }
    default: {
      std::cout << "Undefined QuestItem Index" << std::endl;
      system("pause");
      return nullptr;
    }
  }
  return new QuestItem(index, name, description, item_type);
}

QuestItem::QuestItem(int _index, std::string _name, std::string _description,
                     ItemType _item_type)
    : Item(_index, _name, _description, _item_type) {}

void QuestItem::PrintDescription() {
  std::cout << GetDescription() << std::endl;
}
*/