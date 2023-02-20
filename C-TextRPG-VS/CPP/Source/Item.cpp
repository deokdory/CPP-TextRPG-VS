#include "pch.h"
#include "Item.h"

Item::Item() : name("NONE"), item_type(ItemType::VALUABLE) {}

Item::Item(std::string _name, ItemType _item_type) : name(_name), item_type(_item_type) {}


std::string Item::GetName() const { return name; }
ItemType Item::GetItemType() const { return item_type; }

void Item::SetName(std::string _name) { name = _name; }
void Item::SetItemType(ItemType _item_type) { item_type = _item_type; }

void Item::Use(Character& character) { std::cout << "NULL ITEM" << std::endl; }

Item::~Item() {}

Potion::Potion(std::string _name, PotionType _type, int _amount, int _duration)
    : Item::Item(_name, ItemType::POTION),
      type(_type),
      amount(_amount),
      duration(_duration) {
  if (_type != PotionType::HP_RECOVER) {
    if (!duration) {
      duration = 1;
    }
  } else {
    duration = 0;
  }
}

void Potion::Use(Character& character) {
  switch (type) {
    case PotionType::HP_RECOVER:
      character.SetHp(character.GetHp() + amount);
      break;
    case PotionType::MAXHP_INCREASE: {
      character.BoostMaxHp(amount, duration);
      break;
    }
    case PotionType::ATK_INCREASE: {
      character.BoostAtk(amount, duration);
      break;
    }
    case PotionType::DEF_INCREASE: {
      character.BoostDef(amount, duration);
      break;
    }
    case PotionType::SPD_INCREASE: {
      character.BoostSpd(amount, duration);
      break;
    }
    default: {
      std::cout << "ERROR : PotionType is Wrong" << std::endl;
    }
  }
}