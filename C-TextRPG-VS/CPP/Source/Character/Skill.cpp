#include "pch.h"
#include "Character.h"

//��ų Ŭ����
Skill::Skill()
    : Owner(nullptr),
      cooldown(0),
      cooldown_remain(0),
      skill_type(SkillType::ATTACK),
      description("NONE") {}

Skill::Skill(Character* _Owner, int _cooldown, int _cooldown_remain,
             SkillType _type, std::string _description)
    : Owner(_Owner),
      cooldown(_cooldown),
      cooldown_remain(_cooldown_remain),
      skill_type(_type),
      description(_description) {}

Skill::Skill(const Skill& other)
    : Owner(other.Owner),
      cooldown(other.cooldown),
      cooldown_remain(other.cooldown_remain),
      skill_type(other.skill_type),
      description(other.description) {}

int Skill::GetCoolDown() const { return cooldown; }
int Skill::GetCoolDownRemain() const { return cooldown_remain; }
void Skill::SetCoolDown(int _cooldown) { cooldown = _cooldown; }
bool Skill::IsAvailable() {
  if (!GetCoolDownRemain()) {
    return true;
  } else {
    // std::cout << "���� ����� �� �����ϴ�" << std::endl;
    return false;
  }
}

//���� ������
StrongAttack::StrongAttack(Character* _Owner)
    : Skill::Skill(_Owner, 3, 0, SkillType::ATTACK,
                   "�� 1.25�� �� ���ϰ� ���� �����մϴ�.") {
  name = "���� ������";
}

void StrongAttack::Use(Character& _Target) {
  if (IsAvailable()) {
    int prev_atk = 0;
    std::cout << Owner->GetName() << "(��)�� " << GetName() << "�� ����ߴ�!"
              << std::endl;
    int prev_atk = Owner->GetAtk();
    Owner->SetAtk(Owner->GetAtk() * 1.25);
    Character::Attack(_Target);
    Owner->SetAtk(prev_atk);
    cooldown_remain = cooldown;
  }
}