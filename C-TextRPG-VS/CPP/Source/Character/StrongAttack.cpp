#include "StrongAttack.h"

#include "pch.h"

StrongAttack::StrongAttack(Character _Owner) : Owner(_Owner) {
  name = "���� ������";
}

void StrongAttack::Use(Character _Target) {
  if (IsAvailable()) {
    std::cout << Owner.GetName() << "(��)�� " << GetName() << "�� ����ߴ�!"
              << std::endl;
    Owner.SetAtk(Owner.GetAtk() * 1.3);
    Owner.Attack(_Target);
  }
}