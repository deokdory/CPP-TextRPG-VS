#pragma once
#include "Character.h"
#include "GameManager.h"

enum class ItemType { WEAPON, EQUIP, POTION, VALUABLE, QUEST_ITEM, NONE };

enum PotionIndex {  // 1 ~ 30
  S_HP_POTION = 1,
  M_HP_POTION,
  L_HP_POTION,
};

enum QuestItemIndex {  // 1001 ~ 1500
  WOLF_TOOTH = 1001,
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
  std::string description;
  ItemType item_type;

  int price;
 public:
  Item();
  Item(int _index, std::string _name, std::string _description, ItemType _type, int _price);

  // Get
  int GetIndex() const { return index; }
  std::string GetName() const { return name; }
  std::string GetDescription() const { return description; }
  ItemType GetItemType() const { return item_type; }
  int GetPrice() const { return price; }

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
  PotionType potion_type;

 public:
  Potion(int _index, std::string _name, std::string _description, ItemType _item_type, int _amount,
         PotionType _potion_type, int _price);

  virtual void Use(Character& character);

  virtual void PrintDescription();
};


class QuestItem : public Item {
 public:
  QuestItem(int _index, std::string _name, std::string _description, ItemType _item_type, Enemy* _drop_from);

  virtual void PrintDescription();

  private:
  Enemy* drop_from;
};

Item* NewItem(int _index);
Item* NewPotion(int _index);
//Item* NewQuestItem(int _index);

class Inventory {
 public:
  Inventory();
  Inventory(int _index, int count = 1);

  // ������ ��Ȳ���� �κ��丮 ����
  static void Open(Hero** player);

  // �������� ����
  static void OpenForSell();

  // ���� �� �κ��丮 ���� ( ���� �������� �ִ� ��� or ��ü ���� �� ���� �����
  // �� �ֵ��� �ش� ���� ����, �÷��̾� ��, �� ���� ��� �Ű������� ���� )
  static void Open(Hero& turn_hero, Hero** player, Enemy** enemies);

  static void GotItem(int _index, int count = 1);

  static void GotNewItem(int _index, int count = 1);
  void Push();

  void IncreaseItemCount(int increase = 1);
  void DecreaseItemCount(int decrease = 1);
  static Inventory* FindItem(Item* item);
  static Inventory* FindItem(int _index);

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

void Shop();
void ShopListPotion();
void ShopMenu();

void BuyItem();
void SellItem();