#include "Item.h"
#include "pch.h"

enum { SHOP_BUY = 1, SHOP_SELL, SHOP_EXIT = 0 };

void Shop() {
  ClearFromY(9, 20);
  ShopListPotion();
  ShopMenu();
}

void ShopListPotion() {
  std::cout << "Shop  ===="
               "============================================================"
            << endll;
  // 포션 리스트 ( 1 ~ 30 )
  int index = 1;
  while (true) {
    Item* item = NewItem(index);
    if (item != nullptr && index <= 30) {
      std::cout << index << ". " << item->GetName() << " | " << item->GetPrice()
                << "G | ";
      item->PrintDescription();
      ENDL;
      delete item;
      index++;
    } else {
      break;
    }
  }
}

void ShopMenu() {
  while (true) {
    std::cout << "1. 아이템 구매   2. 아이템 판매   0. 나가기" << std::endl;
    std::cout << "입력 : " << std::endl;

    int select = 0;
    std::cin >> select;
    if (0 <= select && select <= 2) {
      switch (select) {
        case SHOP_EXIT: {
          return;
        }
        case SHOP_BUY: {
          BuyItem();
          break;
        }
        case SHOP_SELL: {
          SellItem();
          break;
        }
        default: {
          std::cout << "잘못된 입력입니다." << std::endl;
          Pause;
        }
      }
    }
  }
}

void BuyItem() {
  while (true) {
    int index;
    std::cout << "구입할 아이템의 고유번호를 입력해주세요. ( 0. 취소 ) : ";
    std::cin >> index;

    if (index == 0) return;

    Item* item = NewItem(index);

    if (item == nullptr) {
      delete item;
      std::cout << "해당 아이템은 존재하지 않습니다." << std::endl;
      SYSTEM_MESSAGE_DELAY;
      continue;
    }

    int count;
    std::cout << item->GetName()
              << "을(를) 몇 개 구매하시겠습니까? ( 0. 취소 ) : ";
    std::cin >> count;

    if (count == 0) continue;

    if (GameManager::GetGold() >= item->GetPrice() * count) {
      GameManager::SetGold(GameManager::GetGold() - item->GetPrice() * count);
      Inventory::GotItem(index, count);
      std::cout << item->GetName() << "을(를) " << count << "개 구매했습니다."
                << std::endl;
      SYSTEM_MESSAGE_DELAY;
    } else {
      std::cout << "골드가 부족합니다.." << std::endl;
      SYSTEM_MESSAGE_DELAY;
      continue;
    }
  }
}

void SellItem() { Inventory::OpenForSell(); }
