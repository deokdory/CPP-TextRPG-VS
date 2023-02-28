#include "Character.h"
#include "pch.h"

//스킬 클래스
Skill::Skill()
    : index(0),
      Owner(nullptr),
      cooldown(0),
      cooldown_remain(0),
      type(SkillType::ATTACK),
      description("NONE") {}

Skill::Skill(int _index, Character* _Owner, int _cooldown, int _cooldown_remain,
             SkillType _type, std::string _description)
    : index(_index),
      Owner(_Owner),
      cooldown(_cooldown),
      cooldown_remain(_cooldown_remain),
      type(_type),
      description(_description) {}

Skill::Skill(const Skill& other)
    : index(other.index),
      Owner(other.Owner),
      cooldown(other.cooldown),
      cooldown_remain(other.cooldown_remain),
      type(other.type),
      description(other.description) {}

int Skill::GetCoolDown() const { return cooldown; }
int Skill::GetCoolDownRemain() const { return cooldown_remain; }
std::string Skill::GetDescription() const { return description; }

SkillType Skill::GetSkillType() const { return type; }

void Skill::SetCoolDown(int _cooldown) { cooldown = _cooldown; }
void Skill::SetOwner(Character* _character) { Owner = _character; }

void Skill::SetCoolDownRemain(int _cooldown_remain) {
  cooldown_remain = _cooldown_remain;
}

bool Skill::IsAvailable() {
  if (!GetCoolDownRemain()) {
    return true;
  } else {
    // std::cout << "아직 사용할 수 없습니다" << std::endl;
    return false;
  }
}

void Skill::Use(Character& _Target) { std::cout << "null skills" << std::endl; }

// 세게 때리기
StrongAttack::StrongAttack(Character* _Owner)
    : Skill::Skill(STRONG_ATTACK, _Owner, 3, 0, SkillType::ATTACK,
                   "약 1.25배 더 강하게 적을 공격합니다.") {
  name = "세게 때리기";
}

void StrongAttack::Use(Character& _Target) {
  if (IsAvailable()) {
    int prev_atk = 0;
    std::cout << Owner->GetName() << "(이)가 " << GetName() << "을 사용했다!"
              << std::endl;
    prev_atk = Owner->GetAtk();
    Owner->SetAtk(Owner->GetAtk() * 1.25);
    Owner->Attack(_Target);
    Owner->SetAtk(prev_atk);
    cooldown_remain = cooldown + 1;
  }
}

Protector::Protector(Character* _protector, int _count,
                     Character* _is_protected_1, Character* _is_protected_2)
    : protector(_protector), count(_count) {
  is_protected[0] = _is_protected_1;
  is_protected[1] = _is_protected_2;
}

void Protector::ProtectNow(Character* _is_protected) {
  std::cout << protector->GetName() << "가 " << _is_protected->GetName()
            << "를 보호한다!" << std::endl;

  Switch(protector, _is_protected);
  count--;
} 

void Protector::ProtectEnd(Character* _is_protected) {
  Switch(protector, _is_protected);
}

void Protector::Switch(Character* character1, Character* character2) {
  Character* temp = character1;
  character1 = character2;
  character2 = temp;  
}

// 보호
Protect::Protect(Character* _Owner)
    : Skill::Skill(PROTECT, _Owner, 1, 0, SkillType::PROTECT,
                   "대상 아군이 공격받을 때 1번 대신 맞아줍니다."),
      protect_count(1) {}

void Protect::Use(Character& Target) {
  if (IsAvailable()) {
    
  }
}
    // 독 바르기
    PoisonInWeapon::PoisonInWeapon(Character * Owner) {}
    void PoisonInWeapon::Use() {}

    // 스매쉬
    Smash::Smash(Character * Owner) {}
    void Smash::Use(Character & Target) {}

    // 포효
    Roar::Roar(Character * Owner) {}
    void Roar::Use(Hero * *player) {}
