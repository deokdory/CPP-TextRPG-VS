#pragma once
#include "Character.h"

enum class ItemType { WEAPON, EQUIP, POTION, VALUABLE, QUEST, NONE };

enum PotionIndex {
  S_HP_POTION = 1,
  M_HP_POTION,
  L_HP_POTION,
};

enum ACTION_IN_INVENTORY {
  INVENTORY_CLOSE,
  INVENTORY_USE_ITEM,
  INVENTORY_REMOVE_ITEM,
};

class Item {
 protected:
  int index;
  std::string name;
  ItemType item_type;

 public:
  Item();

  // Get
  int GetIndex() const { return index; }
  std::string GetName() const { return name; }
  ItemType GetItemType() const { return item_type; }

  // Set
  void SetName(std::string _name);
  void SetItemType(ItemType _item_type);

  // Use !
  virtual void Use(Character& character);
  virtual void PrintDescription() = 0;

  ~Item();
};

enum class PotionType {
  NONE,
  HP_RECOVER,
  // MAXHP_INCREASE,
  // ATK_INCREASE,
  // DEF_INCREASE,
  // SPD_INCREASE
};

class Potion : public Item {
 protected:
  int amount;
  PotionType type;

 public:
  Potion(int _index);
  void NewPotion(int _index);

  virtual void Use(Character& character);

  virtual void PrintDescription();

  ~Potion();
};

class Inventory {
 public:
  Inventory();
  Inventory(int _index, int count = 1);

  // ������ ��Ȳ���� �κ��丮 ����
  static void Open(Hero** player);

  // ���� �� �κ��丮 ���� ( ���� �������� �ִ� ��� or ��ü ���� �� ���� ����� �� �ֵ���
  // �ش� ���� ����, �÷��̾� ��, �� ���� ��� �Ű������� ���� )
  static void Open(Hero& turn_hero, Hero** player, Enemy** enemies);  

  static void GotItem(int _index, int count = 1);

  static void GotNewItem(int _index, int count = 1);
  void Push();

  void IncreaseItemCount(int increase = 1);
  void DecreaseItemCount(int decrease = 1);
  static Inventory* FindItem(Item* item);

  Item* GetItem() const { return item; }
  int GetItemCount() const { return item_count; }
  static Inventory* GetNode(int index);

  static const int GetLength() { return Length; }

  static const Inventory* GetHead() { return Head; }
  static const Inventory* GetTail() { return Tail; }

  void Remove();
  void RemoveAll();

 private:
  static void Open();  // �κ��丮 ���� ���ο�
  static int MenuSelect();
  static Inventory* ItemSelect();
  static void MenuUseItem(Hero** player);
  static void MenuUseItem(Hero& turn_hero, Hero** player, Enemy** enemies);
  static void MenuRemoveItem();

  void RemoveAll(Inventory* head);

  Item* item;
  int item_count;

  Inventory* Next;
  Inventory* Prev;

  static Inventory* Head;
  static Inventory* Tail;

  static int Length;
};