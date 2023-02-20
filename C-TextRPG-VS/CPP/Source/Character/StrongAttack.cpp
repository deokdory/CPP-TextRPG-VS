#include "StrongAttack.h"

#include "pch.h"

StrongAttack::StrongAttack(Character _Owner) : Owner(_Owner) {
  name = "세게 때리기";
}

void StrongAttack::Use(Character _Target) {
  if (IsAvailable()) {
    std::cout << Owner.GetName() << "(이)가 " << GetName() << "을 사용했다!"
              << std::endl;
    Owner.SetAtk(Owner.GetAtk() * 1.3);
    Owner.Attack(_Target);
  }
}