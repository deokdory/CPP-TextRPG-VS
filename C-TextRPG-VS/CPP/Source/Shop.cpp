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
  // ���� ����Ʈ ( 1 ~ 30 )
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
    std::cout << "1. ������ ����   2. ������ �Ǹ�   0. ������" << std::endl;
    std::cout << "�Է� : " << std::endl;

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
          std::cout << "�߸��� �Է��Դϴ�." << std::endl;
          Pause;
        }
      }
    }
  }
}

void BuyItem() {
  while (true) {
    int index;
    std::cout << "������ �������� ������ȣ�� �Է����ּ���. ( 0. ��� ) : ";
    std::cin >> index;

    if (index == 0) return;

    Item* item = NewItem(index);

    if (item == nullptr) {
      delete item;
      std::cout << "�ش� �������� �������� �ʽ��ϴ�." << std::endl;
      SYSTEM_MESSAGE_DELAY;
      continue;
    }

    int count;
    std::cout << item->GetName()
              << "��(��) �� �� �����Ͻðڽ��ϱ�? ( 0. ��� ) : ";
    std::cin >> count;

    if (count == 0) continue;

    if (GameManager::GetGold() >= item->GetPrice() * count) {
      GameManager::SetGold(GameManager::GetGold() - item->GetPrice() * count);
      Inventory::GotItem(index, count);
      std::cout << item->GetName() << "��(��) " << count << "�� �����߽��ϴ�."
                << std::endl;
      SYSTEM_MESSAGE_DELAY;
    } else {
      std::cout << "��尡 �����մϴ�.." << std::endl;
      SYSTEM_MESSAGE_DELAY;
      continue;
    }
  }
}

void SellItem() { Inventory::OpenForSell(); }
