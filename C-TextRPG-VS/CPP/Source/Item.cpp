#include "Item.h"

#include "pch.h"

Item::Item() : index(0), name("NONE"), item_type(ItemType::NONE) {}

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
    // case PotionType::MAXHP_INCREASE: {
    //  break;
    //}
    // case PotionType::ATK_INCREASE: {
    //  break;
    //}
    // case PotionType::DEF_INCREASE: {
    //  break;
    //}
    // case PotionType::SPD_INCREASE: {
    //  break;
    //}
    default: {
      std::cout << "ERROR:Undefined Potion Type" << std::endl;
    }
  }
}

void Potion::PrintDescription() {
  switch (type) {
    case PotionType::HP_RECOVER: {
      std::cout << "HP를 " << amount << "만큼 회복합니다." << std::endl;
      break;
    }
    default: {
      std::cout << "Undefined PotionType" << std::endl;
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
      break;
    }
    case M_HP_POTION: {
      name = "HP 포션(중)";
      amount = 50;
      type = PotionType::HP_RECOVER;
      break;
    }
    case L_HP_POTION: {
      name = "HP 포션(대)";
      amount = 80;
      type = PotionType::HP_RECOVER;
      break;
    }
    default: {
      std::cout << "ERROR:Undefined Potion Index" << std::endl;
      name = "NONE";
      amount = 0;
      type = PotionType::NONE;
      system("pause");
      break;
    }
  }
}

//인벤토리
Inventory* Inventory::Head = nullptr;
Inventory* Inventory::Tail = nullptr;
int Inventory::Length = 0;

Inventory::Inventory()
    : item(nullptr), item_count(0), Next(nullptr), Prev(nullptr) {}

Inventory::Inventory(int _index, int count) {
  Inventory* node = new Inventory;
  if (1 <= _index && _index <= 100) item = new Potion(_index);
  item_count += count;
}

void Inventory::Open(Hero** player) {
  while (true) {
    Open();
    switch (MenuSelect()) {
      case INVENTORY_USE_ITEM: {
        MenuUseItem(player);
      }
      case INVENTORY_REMOVE_ITEM: {
        MenuRemoveItem();
      }
      case INVENTORY_CLOSE:
        return;
    }
  }
}

void Inventory::Open(Hero& turn_hero, Hero** player, Enemy** enemies) {
  while (true) {
    Open();
    switch (MenuSelect()) {
      case INVENTORY_USE_ITEM: {
        MenuUseItem(turn_hero, player, enemies);
        if (turn_hero.GetTurnWaiter() == 0) {
          return;
        }
        break;
      }
      case INVENTORY_REMOVE_ITEM: {
        MenuRemoveItem();
        break;
      }
      case INVENTORY_CLOSE: {
        return;
      }
      default:
        std::cout << "undefined menuselect" << std::endl;
        system("pause");
    }
  }
}

void Inventory::GotItem(int _index, int count) {
  Inventory* finder = Head;
  while (true) {
    if (Head == nullptr) {
      GotNewItem(_index, count);
      return;
    }

    if (finder->GetItem()->GetIndex() == _index) {
      finder->IncreaseItemCount(count);
      return;
    } else if (finder->Next != nullptr) {
      finder = finder->Next;
    } else {
      GotNewItem(_index, count);
      return;
    }
  }
}
void Inventory::GotNewItem(int _index, int count) {
  Inventory* node = new Inventory(_index, count);
  node->Push();
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

void Inventory::IncreaseItemCount(int increase) { item_count += increase; }
void Inventory::DecreaseItemCount(int decrease) {
  item_count -= decrease;
  if (item_count <= 0) {
    Remove();
  }
}

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

Inventory* Inventory::GetNode(int index) {
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

void Inventory::Remove() {
  if (this == Head) {
    if (this->Next != nullptr) {
      this->Next->Prev = nullptr;
      Head = this->Next;
    } else {
      Head = nullptr;
      Tail = nullptr;
    }
  } else if (this == Tail) {
    this->Prev->Next = nullptr;
    Tail = this->Prev;
  } else {
    this->Prev->Next = this->Next;
    this->Next->Prev = this->Prev;
  }
  if (item != nullptr) delete item;
  delete this;
  Length--;
  return;
}

void Inventory::RemoveAll() {
  Length = 0;

  if (Head == nullptr) {
    std::cout << "List is already NULL" << std::endl;
    return;
  } else if (Head->Next != nullptr) {
    RemoveAll(Head->Next);
  }
  Head->Remove();
  Head = nullptr;
  Tail = nullptr;
}

void Inventory::Open() {
  std::cout << "Inventory "
               "============================================================"
            << std::endl
            << std::endl;
  if (Head == nullptr) {
    std::cout << "인벤토리에 아이템이 없습니다." << std::endl;
  } else {
    const Inventory* node = nullptr;
    for (int i = 0; i < Length; i++) {
      node = GetNode(i);
      std::cout << i + 1 << ". " << node->GetItem()->GetName() << " : "
                << node->GetItemCount() << "개 | ";
      node->GetItem()->PrintDescription();
    }
  }
  std::cout << std::endl
            << "============================================================="
               "========="
            << std::endl;
}

int Inventory::MenuSelect() {
  int menu_select;
  if (Head == nullptr) {
    SYSTEM_MESSAGE_DELAY;
    return 3;
  }
  while (true) {
    std::cout << "1. 아이템 사용   2. 아이템 버리기   3. 인벤토리 닫기 : ";
    std::cin >> menu_select;
    if (1 <= menu_select && menu_select <= 3) {
      break;
    } else {
      std::cout << "잘못된 입력입니다." << std::endl;
      SYSTEM_MESSAGE_DELAY;
    }
  }
  return menu_select;
}

Inventory* Inventory::ItemSelect() {
  Inventory* node;
  int select;
  while (true) {
    std::cout << "아이템의 번호를 입력해주세요. ( 취소 : 0 ) : ";
    std::cin >> select;

    if (select == 0)
      return nullptr;
    else if (GetNode(select - 1) != nullptr) {
      node = GetNode(select - 1);
      break;
    } else {
      std::cout << "해당 번호에는 아이템이 존재하지 않습니다." << std::endl;
      SYSTEM_MESSAGE_DELAY;
    }
  }
  return node;
}

void Inventory::MenuUseItem(Hero** player) {
  while (true) {
    Inventory* node = ItemSelect();
    if (node == nullptr) return;
    if (node->GetItem()->GetItemType() != ItemType::VALUABLE) {
      node->GetItem()->Use(*SelectTarget(player));
      SYSTEM_MESSAGE_DELAY;
      node->DecreaseItemCount();
      return;
    } else {
      std::cout << "사용할 수 없는 아이템입니다." << std::endl;
      SYSTEM_MESSAGE_DELAY;
    }
  }
}

void Inventory::MenuUseItem(Hero& turn_hero, Hero** player, Enemy** enemies) {
  while (true) {
    Inventory* node = ItemSelect();
    if (node == nullptr) return;
    if (node->GetItem()->GetItemType() != ItemType::VALUABLE) {
      node->GetItem()->Use(turn_hero);
      SYSTEM_MESSAGE_DELAY;
      node->DecreaseItemCount();
      turn_hero.TurnEnd();
      return;
    } else {
      std::cout << "사용할 수 없는 아이템입니다." << std::endl;
      SYSTEM_MESSAGE_DELAY;
    }
  }
}

void Inventory::MenuRemoveItem() {
  int remove_count = 1;
  int is_sure;
  while (true) {
    Inventory* node = ItemSelect();
    if (node == nullptr) return;
    if (node->GetItemCount() > 1) {
      std::cout << "얼마나 버리시겠습니까 ( 취소 : 0 ) : ";
      std::cin >> remove_count;
    }
    if (remove_count == 0) {
      break;
    } else if (remove_count > node->GetItemCount()) {
      remove_count = node->GetItemCount();
    }
    while (true) {
      std::cout << node->GetItem()->GetName() << "를 " << remove_count
                << "개 버립니다. 확실합니까? ( 1. 예   2. 아니오 ) : ";
      std::cin >> is_sure;
      if (is_sure == 1) {
        node->DecreaseItemCount(remove_count);
        return;
      } else if (is_sure == 2) {
        return;
      } else {
        std::cout << "잘못된 입력입니다." << std::endl;
        SYSTEM_MESSAGE_DELAY;
      }
    }
  }
}

void Inventory::RemoveAll(Inventory* head) {
  if (head->Next != nullptr) {
    RemoveAll(head->Next);
  }
  head->Remove();
}
