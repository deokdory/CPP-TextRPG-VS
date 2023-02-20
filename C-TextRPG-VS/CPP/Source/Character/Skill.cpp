#include "pch.h"
#include "Skill.h"

//��ų Ŭ����
Skill::Skill() : cooldown(0) { name = "NULL"; }

int Skill::GetCoolDown() const { return cooldown; }
int Skill::GetCoolDownRemain() const { return cooldown_remain; }
void Skill::SetCoolDown(int _cooldown) { cooldown = _cooldown; }

void Skill::Use() { std::cout << "NULL SKILL" << std::endl; }
bool Skill::IsAvailable() {
  if (!GetCoolDownRemain()) {
    return true;
  } else {
    // std::cout << "���� ����� �� �����ϴ�" << std::endl;
    return false;
  }
}

//���� ������
StrongAttack::StrongAttack(Character _Owner) : Owner(_Owner) {
  name = "���� ������";
}

void StrongAttack::Use(Character _Target) {
  if (IsAvailable()) {
    int prev_atk = 0;
    std::cout << Owner.GetName() << "(��)�� " << GetName() << "�� ����ߴ�!"
              << std::endl;
    prev_atk = Owner.GetAtk();
    Owner.SetAtk(Owner.GetAtk() * 1.3);
    Owner.Attack(_Target);
    Owner.SetAtk(prev_atk);
  }
}