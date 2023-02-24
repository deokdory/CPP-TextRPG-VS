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
  int index;
  std::string name;
  ItemType item_type;
 public:
  Item();
  Item(std::string name, ItemType item_type);
  //Get
  int GetIndex() const { return index; }
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
  Potion(std::string _name, PotionType _type, int _amount, int duration);

  virtual void Use(Character& character);

  ~Potion();
};

void OpenInventory();

class Inventory {
 public:
  static void GotItem(Item* _item);

  static Inventory* GotNewItem(Item* item);
  void Push();

  void AddCount();

  Inventory* FindItem(Item* item);

  Item* GetItem() const { return item; }
  int GetItemCount() const { return item_count; }
  static const Inventory* GetNode(int index);

  static const int GetLength() { return Length; }

  static const Inventory* GetHead() { return Head; }
  static const Inventory* GetTail() { return Tail; }

  void RemoveItem(int index);
  void RemoveAll();

  private:
  void RemoveAll(Inventory* head);

  Item* item;
  int item_count;

  Inventory* Next;
  Inventory* Prev;

  static Inventory* Head;
  static Inventory* Tail;

  static int Length;
};