#include "Character.h"
#include "pch.h"

//��ų Ŭ����
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
    // std::cout << "���� ����� �� �����ϴ�" << std::endl;
    return false;
  }
}

void Skill::Use(Character& _Target) { std::cout << "null skills" << std::endl; }

// ���� ������
StrongAttack::StrongAttack(Character* _Owner)
    : Skill::Skill(STRONG_ATTACK, _Owner, 3, 0, SkillType::ATTACK,
                   "�� 1.25�� �� ���ϰ� ���� �����մϴ�.") {
  name = "���� ������";
}

void StrongAttack::Use(Character& _Target) {
  if (IsAvailable()) {
    int prev_atk = 0;
    std::cout << Owner->GetName() << "(��)�� " << GetName() << "�� ����ߴ�!"
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
  std::cout << protector->GetName() << "�� " << _is_protected->GetName()
            << "�� ��ȣ�Ѵ�!" << std::endl;

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

// ��ȣ
Protect::Protect(Character* _Owner)
    : Skill::Skill(PROTECT, _Owner, 1, 0, SkillType::PROTECT,
                   "��� �Ʊ��� ���ݹ��� �� 1�� ��� �¾��ݴϴ�."),
      protect_count(1) {}

void Protect::Use(Character& Target) {
  if (IsAvailable()) {
    
  }
}
    // �� �ٸ���
    PoisonInWeapon::PoisonInWeapon(Character * Owner) {}
    void PoisonInWeapon::Use() {}

    // ���Ž�
    Smash::Smash(Character * Owner) {}
    void Smash::Use(Character & Target) {}

    // ��ȿ
    Roar::Roar(Character * Owner) {}
    void Roar::Use(Hero * *player) {}
