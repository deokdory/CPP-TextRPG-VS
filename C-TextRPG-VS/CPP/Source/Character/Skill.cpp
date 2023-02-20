#include "pch.h"
#include "Skill.h"

Skill::Skill() : cooldown(0) { name = "NULL"; }

int Skill::GetCoolDown() const { return cooldown; }
int Skill::GetCoolDownRemain() const { return cooldown_remain; }
void Skill::SetCoolDown(int _cooldown) { cooldown = _cooldown; }

void Skill::Use() { std::cout << "NULL SKILL" << std::endl; }
bool Skill::IsAvailable() {
  if (!GetCoolDownRemain()) {
    return true;
  } else {
    std::cout << "���� ����� �� �����ϴ�" << std::endl;
    return false;
  }
}