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

enum PotionIndex {
  S_HP_POTION = 1,
  M_HP_POTION,
  L_HP_POTION,
};

class Item {
 protected:
  int index;
  std::string name;
  ItemType item_type;

 public:
  Item();
  Item(int index);

  //Get
  int GetIndex() const { return index; }
  std::string GetName() const { return name; }
  ItemType GetItemType() const { return item_type; }
   
  //Set
  void SetName(std::string _name);
  void SetItemType(ItemType _item_type);

  //Use !
  virtual void Use(Character& character);

  ~Item();
};

enum class PotionType {
  NONE,
  HP_RECOVER,
  //MAXHP_INCREASE,
  //ATK_INCREASE,
  //DEF_INCREASE,
  //SPD_INCREASE
};

class Potion : public Item {
 protected:
  int amount;
  PotionType type;

 public:
  Potion(int _index);
  virtual void Use(Character& character);

  void NewPotion(int _index);

  ~Potion();
};

void OpenInventory();

class Inventory {
 public:
  static void GotItem(int _index);

  static Inventory* GotNewItem(int _index);
  void Push();

  void AddCount();
  static Inventory* FindItem(Item* item);

  Item* GetItem() const { return item; }
  int GetItemCount() const { return item_count; }
  static const Inventory* GetNode(int index);

  static const int GetLength() { return Length; }

  static const Inventory* GetHead() { return Head; }
  static const Inventory* GetTail() { return Tail; }

  void RemoveNode(int index);
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