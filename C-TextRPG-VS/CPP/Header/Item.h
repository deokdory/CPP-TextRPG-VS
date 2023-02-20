#pragma once
#include "Character.h"

enum class ItemType { 
  WEAPON,
  EQUIP,
  POTION,
  VALUABLE,
  QUEST,
  NONE
};

class Item {
 protected:
  std::string name;
  ItemType item_type;
 public:
  Item();
  Item(std::string name, ItemType item_type);
  //Get
  std::string GetName() const;
  ItemType GetItemType() const;

  //Set
  void SetName(std::string _name);
  void SetItemType(ItemType _item_type);

  //Use !
  virtual void Use(Character& character);

  ~Item();
};

enum class PotionType {
  HP_RECOVER,
  MAXHP_INCREASE,
  ATK_INCREASE,
  DEF_INCREASE,
  SPD_INCREASE
};

class Potion : public Item {
 protected:
  int amount;
  unsigned int duration;
  PotionType type;

 public:
  Potion();
  Potion(std::string _name, PotionType _type, int _amount, int duration);

  virtual void Use(Character& character);

  ~Potion();
};