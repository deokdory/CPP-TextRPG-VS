#include "pch.h"
#include "Skill.h"

//스킬 클래스
Skill::Skill() 
    : cooldown(0), cooldown_remain(0), skill_type(SkillType::ATTACK) {
  std::cout << "^^";
  name = "NULL";
}

Skill::Skill(int _cooldown, int _cooldown_remain, SkillType _type)
    : cooldown(_cooldown),
      cooldown_remain(_cooldown_remain),
      skill_type(_type) {}

Skill::Skill(const Skill& other)
    : cooldown(other.cooldown),
      cooldown_remain(other.cooldown_remain),
      skill_type(other.skill_type) {}

int Skill::GetCoolDown() const { return cooldown; }
int Skill::GetCoolDownRemain() const { return cooldown_remain; }
void Skill::SetCoolDown(int _cooldown) { cooldown = _cooldown; }

void Skill::Use() { std::cout << "NULL SKILL" << std::endl; }
bool Skill::IsAvailable() {
  if (!GetCoolDownRemain()) {
    return true;
  } else {
    // std::cout << "아직 사용할 수 없습니다" << std::endl;
    return false;
  }
}

//세게 때리기
StrongAttack::StrongAttack(Character _Owner) : Skill::Skill(3, 0, SkillType::ATTACK), Owner(_Owner) {
  name = "세게 때리기";
}

void StrongAttack::Use(Character _Target) {
  if (IsAvailable()) {
    int prev_atk = 0;
    std::cout << Owner.GetName() << "(이)가 " << GetName() << "을 사용했다!"
              << std::endl;
    prev_atk = Owner.GetAtk();
    Owner.SetAtk(Owner.GetAtk() * 1.3);
    Owner.Attack(_Target);
    Owner.SetAtk(prev_atk);
  }
}