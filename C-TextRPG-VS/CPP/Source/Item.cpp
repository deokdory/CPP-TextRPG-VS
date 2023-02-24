#include "Item.h"
#include "pch.h"

Inventory* Inventory::Head = nullptr;
Inventory* Inventory::Tail = nullptr;
int Inventory::Length = 0;

void OpenInventory() {
    std::cout
        << "Inventory "
           "================================================================="
        << std::endl;
  if (Inventory::GetHead() == nullptr) {
    std::cout << "인벤토리에 아이템이 없습니다." << std::endl;
    return;
  }
  for (int i = 0; i < Inventory::GetLength(); i++) {
    std::cout << i + 1 << ". " << Inventory::GetNode(i)->GetItem()->GetName();
  }
}

Item::Item() : name("NONE"), item_type(ItemType::VALUABLE) {}

Item::Item(std::string _name, ItemType _item_type)
    : name(_name), item_type(_item_type) {}

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



//인벤토리
void Inventory::GotItem(Item* _item) {
  Inventory* find = FindItem(_item);
  if (find == nullptr) {
    Inventory* node = GotNewItem(_item);
    node->Push();
  } else {
    find->AddCount();
  }
}

Inventory* Inventory::GotNewItem(Item* _item) {
  Inventory* node = new Inventory;

  node->item = _item;
  node->item_count = 1;
  node->Next = nullptr;
  node->Prev = nullptr;

  return node;
}

void Inventory::Push() {
  if (Head == nullptr) {
    Head = this;
    Tail = this;
  } else {
    Tail->Next = this;
    this->Prev = Tail;
    Tail = this;
  }
  Length++;
}

void Inventory::AddCount() { item_count++; }

Inventory* Inventory::FindItem(Item* _item) {
  if (Head == nullptr) {
    std::cout << "Inventory is null" << std::endl;
  }
  Inventory* finder = Head;
  while (finder != nullptr) {
    if (finder->item == _item) {
      return finder;
    }
  }
  return nullptr;
}

const Inventory* Inventory::GetNode(int index) {
  if (Head == nullptr) {
    std::cout << "Inventory is null" << std::endl;
    return nullptr;
  }
  Inventory* finder = Head;
  while (finder != nullptr && --index >= 0) {
    finder = finder->Next;
  }
  return finder;
}

  void Inventory::RemoveItem(int index) {
  if (this == Head) {
    if (this->Next != nullptr) {
      this->Next->Prev = nullptr;
      Head = this->Next;
    }
  } else if (this == Tail) {
    this->Prev->Next = nullptr;
    Tail = this->Prev;
  } else {
    this->Prev->Next = this->Next;
    this->Next->Prev = this->Prev;
  }
  delete this;
  Length--;
  return;
}

void Inventory::RemoveAll() {
  Length = 0;

  if (Head == nullptr) {
    std::cout << "List is already NULL" << std::endl;
  }

  if (Head->Next != nullptr) {
    RemoveAll(Head->Next);
  }
  delete Head;

  Head = nullptr;
  Tail = nullptr;
}

void Inventory::RemoveAll(Inventory* head) {
  if (head->Next != nullptr) {
    RemoveAll(head->Next);
  }
  delete head;
}

