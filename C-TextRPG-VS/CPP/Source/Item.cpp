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

Item::Item() : index(0), name("NONE"), item_type(ItemType::NONE){}

void Item::SetName(std::string _name) { name = _name; }
void Item::SetItemType(ItemType _item_type) { item_type = _item_type; }

void Item::Use(Character& character) { std::cout << "NULL ITEM" << std::endl; }

Item::~Item() {}

Potion::Potion(int _index) { NewPotion(_index); }

void Potion::Use(Character& character) {
  switch (type) {
    case PotionType::HP_RECOVER: {
      int recovered = 0;
      if (character.GetMaxHp() - character.GetHp() < amount) {
        recovered = character.GetMaxHp() - character.GetHp();
      } else {
        recovered = amount;
      }
      character.SetHp(character.GetHp() + recovered);
      std::cout << character.GetName() << "의 체력이 " << recovered
                << "만큼 회복되었다!" << std::endl;
      break;
    }
    //case PotionType::MAXHP_INCREASE: {
    //  break;
    //}
    //case PotionType::ATK_INCREASE: {
    //  break;
    //}
    //case PotionType::DEF_INCREASE: {
    //  break;
    //}
    //case PotionType::SPD_INCREASE: {
    //  break;
    //}
    default: {
      std::cout << "ERROR:Undefined Potion Type" << std::endl;
    }
  }
}

void Potion::NewPotion(int _index) {
  item_type = ItemType::POTION;

  if (_index > 100) {
    std::cout << "ERROR:Potion Index is 1~100" << std::endl;
    index = 0;
    name = "NONE";
    amount = 0;
    type = PotionType::NONE;
    system("pause");
    return;
  }

  index = _index;
  switch (_index) {
    case S_HP_POTION: {
      name = "HP 포션(소)";
      amount = 30;
      type = PotionType::HP_RECOVER;
    }
    case M_HP_POTION: {
      name = "HP 포션(중)";
      amount = 50;
      type = PotionType::HP_RECOVER;
    }
    case L_HP_POTION: {
      name = "HP 포션(대)";
      amount = 80;
      type = PotionType::HP_RECOVER;
    }
    default: {
      std::cout << "ERROR:Undefined Potion Index" << std::endl;
      name = "NONE";
      amount = 0;
      type = PotionType::NONE;
      system("pause");
    }
  }
}

//인벤토리
void Inventory::GotItem(int _index) {
  Inventory* finder = Head;
  while (true) {
    if (Head != nullptr) {
      Inventory* node = GotNewItem(_index);
      node->Push();
      return;
    }

    if (finder->GetItem()->GetIndex() == _index) {
      finder->AddCount();
      return;
    } else if (finder->Next != nullptr) {
      finder = finder->Next;
    } else {
      Inventory* node = GotNewItem(_index);
      node->Push();
      return;
    }
  }
}
Inventory* Inventory::GotNewItem(int _index) {
  Inventory* node = new Inventory;

  if (0 < _index && _index <= 100) node->item = new Potion(_index);
  if (100 < _index && _index <= 200)  // EQUIP

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

  void Inventory::RemoveNode(int index) {
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

