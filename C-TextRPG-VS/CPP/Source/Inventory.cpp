#include "pch.h"
#include "Item.h"

//인벤토리
Inventory* Inventory::Head = nullptr;
Inventory* Inventory::Tail = nullptr;
int Inventory::Length = 0;

Inventory::Inventory()
    : item(nullptr), item_count(0), Next(nullptr), Prev(nullptr) {}

Inventory::Inventory(int _index, int count)
    : item(NewItem(_index)), item_count(count), Next(nullptr), Prev(nullptr) {
  Inventory* node = new Inventory;
}

void Inventory::OpenForSell() {
  while (true) {
    ClearFromY(9, 20);
    Open();

    int sell_count = 1;
    int is_sure;
    while (true) {
      std::cout << "판매하실 ";
      Inventory* node = ItemSelect();
      if (node == nullptr) return;
      if (node->GetItemCount() > 1) {
        std::cout << "얼마나 판매하시겠습니까 ( 취소 : 0 ) : ";
        std::cin >> sell_count;
      }
      if (sell_count == 0) {
        break;
      } else if (sell_count > node->GetItemCount()) {
        sell_count = node->GetItemCount();
      }
      while (true) {
        std::cout << node->GetItem()->GetName() << "를 " << sell_count
                  << "개 판매합니다. 확실합니까? ( 1. 예   2. 아니오 ) : ";
        std::cin >> is_sure;
        if (is_sure == 1) {
          node->DecreaseItemCount(sell_count);
          GameManager::AddGold(node->GetItem()->GetPrice() * sell_count);
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
}

void Inventory::Open(Hero** player) {
  while (true) {
    ClearFromY(9, 20);
    Open();
    switch (MenuSelect()) {
      case INVENTORY_USE_ITEM: {
        MenuUseItem(player);
        break;
      }
      case INVENTORY_REMOVE_ITEM: {
        MenuRemoveItem();
        break;
      }
      case INVENTORY_CLOSE:
        return;
    }
  }
}

void Inventory::Open(Hero& turn_hero, Hero** player, Enemy** enemies) {
  Open();
  MenuUseItem(turn_hero, player, enemies);
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
  if (node->GetItem() != nullptr)
    node->Push();
  else {
    std::cout << "ERROR:Can't create inventory slot, item is null" << std::endl;
    system("pause");
    delete node;
  }
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

Inventory* Inventory::FindItem(int _index) {
  if (Head == nullptr) {
    // std::cout << "Inventory is null" << std::endl;
    return nullptr;
  }
  Inventory* finder = Head;
  while (true) {
    if (finder->GetItem() != nullptr) {
      if (finder->GetItem()->GetIndex() == _index) return finder;
    }
    if (finder->Next != nullptr)
      finder = finder->Next;
    else
      return nullptr;
  }
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
            << endll;
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
    return INVENTORY_CLOSE;
  }
  while (true) {
    std::cout << "1. 아이템 사용   2. 아이템 버리기   0. 인벤토리 닫기 : ";
    std::cin >> menu_select;
    if (0 <= menu_select && menu_select <= 2) {
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
      Character* target = SelectTarget(player);
      if (target != nullptr) {
        node->GetItem()->Use(*target);
        LobbyPlayerStatus(player);
        SYSTEM_MESSAGE_DELAY;
        node->DecreaseItemCount();
        return;
      } else {
        return;
      }
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
