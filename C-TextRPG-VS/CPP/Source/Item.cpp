#include "Item.h"

#include "pch.h"

Item::Item()
    : index(0), name("null"), description("null"), item_type(ItemType::NONE) {}
Item::Item(int _index, std::string _name, std::string _description,
           ItemType _type)
    : index(_index), name(_name), description(_description), item_type(_type) {}

void Item::SetName(std::string _name) { name = _name; }
void Item::SetItemType(ItemType _item_type) { item_type = _item_type; }

void Item::Use(Character& character) { std::cout << "NULL ITEM" << std::endl; }

Item::~Item() {}

Potion::Potion(int _index, std::string _name, std::string _description,
               ItemType _item_type, int _amount, PotionType _potion_type)
    : Item(_index, _name, _description, _item_type),
      amount(_amount),
      potion_type(_potion_type) {}

void Potion::Use(Character& character) {
  switch (potion_type) {
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
  switch (potion_type) {
    case PotionType::HP_RECOVER: {
      std::cout << "HP를 " << amount << "만큼 회복합니다." << std::endl;
      break;
    }
    default: {
      std::cout << "Undefined PotionType" << std::endl;
    }
  }
  std::cout << GetDescription() << std::endl;
}
Item* NewItem(int _index) {
  Item* new_item = nullptr;
  if (1 <= _index && _index <= 100) {
    return NewPotion(_index);
  }  // 포션 Index
  // else if (1001 <= _index && _index <= 1500) {
  //  return NewQuestItem(_index);
  //}  // 퀘스트아이템 Index
  else {
    std::cout << "Undefined Item Index" << std::endl;
    system("pause");
    return nullptr;
  }
}

Item* NewPotion(int _index) {
  if (_index > 100) {
    std::cout << "ERROR:Potion Index is 1~100" << std::endl;
    system("pause");
    return nullptr;
  }
  std::string name = "null";
  std::string description = "null";
  ItemType item_type = ItemType::POTION;
  int amount = 0;
  PotionType potion_type = PotionType::NONE;

  switch (_index) {
    case S_HP_POTION: {
      name = "HP포션(소)";
      description = "작은 병에 붉은 색의 액체가 들어있다.";
      amount = 30;
      potion_type = PotionType::HP_RECOVER;
      break;
    }
    case M_HP_POTION: {
      name = "HP포션(중)";
      description = "적당한 크기의 병에 붉은 색의 액체가 들어있다.";
      amount = 50;
      potion_type = PotionType::HP_RECOVER;
      break;
    }
    case L_HP_POTION: {
      name = "HP포션(대)";
      description = "큰 병에 붉은 색의 액체가 들어있다.";
      amount = 80;
      potion_type = PotionType::HP_RECOVER;
      break;
    }
    default: {
      std::cout << "ERROR:Undefined Potion Index" << std::endl;
      system("pause");
      return nullptr;
    }
  }
  return new Potion(_index, name, description, item_type, amount, potion_type);
}
/*
Item* NewQuestItem(int _index) {
  if (1001 > _index && _index > 1500) {
    std::cout << "QuestItem index is 1001 ~ 1500" << std::endl;
    system("pause");
    return nullptr;
  }
  int index = _index;
  std::string name = "null";
  std::string description = "null";
  ItemType item_type = ItemType::QUEST_ITEM;

  switch (index) {
    case WOLF_TOOTH: {
      name = "늑대의 이빨";
      description = "늑대를 잡고 얻은 전리품이다.";
    }
    default: {
      std::cout << "Undefined QuestItem Index" << std::endl;
      system("pause");
      return nullptr;
    }
  }
  return new QuestItem(index, name, description, item_type);
}

QuestItem::QuestItem(int _index, std::string _name, std::string _description,
                     ItemType _item_type)
    : Item(_index, _name, _description, _item_type) {}

void QuestItem::PrintDescription() {
  std::cout << GetDescription() << std::endl;
}
*/

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
