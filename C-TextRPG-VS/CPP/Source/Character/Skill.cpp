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
    : Skill::Skill(STRONG_ATTACK, _Owner, 2, 0, SkillType::ATTACK,
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
    Owner->Attack(&_Target);
    Owner->SetAtk(prev_atk);
    cooldown_remain = cooldown + 1;
  }
}

Protector* Protector::Head = nullptr;
Protector* Protector::Tail = nullptr;
int Protector::Length = 0;

// ��ȣ ��� ( ���߿� ���� )
Protector::Protector(Character* _protector, int _count,
                     Character* _is_protected_1, Character* _is_protected_2)
    : protector(_protector), count(_count), Next(nullptr), Prev(nullptr) {
  is_protected[0] = _is_protected_1;
  is_protected[1] = _is_protected_2;
}

// void Protector::ProtectNow(Character* _is_protected) {
//  std::cout << protector->GetName() << "�� " << _is_protected->GetName()
//            << "�� ��ȣ�Ѵ�!" << std::endl;
//
//  Switch(protector, _is_protected);
//}
// void Protector::ProtectEnd(Character* _is_protected) {
//  Switch(protector, _is_protected);
//  DecreaseCount();
//}
//
// void Protector::Switch(Character* character1, Character* character2) {
//  Character* temp = character1;
//  character1 = character2;
//  character2 = temp;
//}

void Protector::NewProtector(Character* _protector, int _count,
                             Character* _is_protected_1,
                             Character* _is_protected_2) {
  if (_protector && _is_protected_1) {
    Protector* node =
        new Protector(_protector, _count, _is_protected_1, _is_protected_2);
    node->Push();
  }
}

Protector* Protector::FindIsProtected(Character* character) {
  if (!Head) return nullptr;

  Protector* finder = Head;
  for (int i = 0; i < Length; i++) {
    if (finder->is_protected[0] == character ||
        finder->is_protected[1] == character) {
      break;
    } else if (finder->Next) {
      finder = finder->Next;
    } else {
      return nullptr;
    }
  }
  return finder;
}

Protector* Protector::FindIsProtecting(Character* character) {
  if (!Head) return nullptr;

  Protector* finder = Head;
  for (int i = 0; i < Length; i++) {
    if (finder->protector == character) {
      break;
    } else if (finder->Next) {
      finder = finder->Next;
    } else {
      return nullptr;
    }
  }
  return finder;
}

void Protector::Push() {
  if (Head == nullptr) {
    Head = this;
    Tail = this;
  } else {
    Tail->Next = this;
    this->Prev = Tail;
    Tail = this;
  }
  Length++;
}

void Protector::DecreaseCount() {
  count--;
  if (count <= 0) {
    Remove();
  }
}

void Protector::Remove() {
  if (this == Head) {
    if (this->Next != nullptr) {
      this->Next->Prev = nullptr;
      Head = this->Next;
    } else {
      Head = nullptr;
      Tail = nullptr;
    }
  } else if (this == Tail) {
    this->Prev->Next = nullptr;
    Tail = this->Prev;
  } else {
    this->Prev->Next = this->Next;
    this->Next->Prev = this->Prev;
  }
  delete this;
  Length--;
  return;
}
void Protector::RemoveAll() {
  Length = 0;

  if (Head == nullptr) {
    // std::cout << "List is already NULL" << std::endl;
    return;
  } else if (Head->Next != nullptr) {
    RemoveAll(Head->Next);
  }
  Head->Remove();
  Head = nullptr;
  Tail = nullptr;
}

void Protector::RemoveAll(Protector* head) {
  if (head->Next != nullptr) {
    RemoveAll(head->Next);
  }
  head->Remove();
}

Character* Protector::ProtectorChecker(Character* target) {
  if (Protector* protector = FindIsProtected(target)) {
    std::cout << protector->GetProtector()->GetName() << "�� ���Ƽ���!";
    SYSTEM_MESSAGE_DELAY;
    target = protector->GetProtector();
    protector->DecreaseCount();
  }
  return target;
}

// ��ȣ
Protect::Protect(Character* _Owner)
    : Skill::Skill(
          PROTECT, _Owner, 1, 0, SkillType::PROTECT,
          "���� ���� ���ƿ��� ������ ��� �Ʊ��� ������ 1�� �����ݴϴ�."),
      protect_count(1) {
  name = "��ȣ";
}

void Protect::Use(Character& Target) {
  if (IsAvailable()) {
    Protector::NewProtector(Owner, protect_count, &Target);
    std::cout << Owner->GetName() << "(��)�� " << GetName() << "�� ����ߴ�!"
              << std::endl;
    cooldown_remain = cooldown + 1;
    SYSTEM_MESSAGE_DELAY;
  }
}
//// ���Ž�
// Smash::Smash(Character * Owner) {}
// void Smash::Use(Character & Target) {}
//
//// ��ȿ
// Roar::Roar(Character * Owner) {}
// void Roar::Use(Hero * *player) {}

// ����

Hider* Hider::Head = nullptr;
Hider* Hider::Tail = nullptr;
int Hider::Length = 0;

Hider::Hider(Character* _hided, int _count)
    : hided(_hided), count(_count), Next(nullptr), Prev(nullptr) {}
void Hider::NewHider(Character* _hided, int _count) {
  if (_hided) {
    Hider* node = new Hider(_hided, _count);
    node->Push();
  }
}

Hider* Hider::FindIsHiding(Character* character) {
  if (!Head) return nullptr;

  Hider* finder = Head;

  for (int i = 0; i < Length; i++) {
    if (finder->hided == character) {
      break;
    } else if (finder->Next) {
      finder = finder->Next;
    } else {
      return nullptr;
    }
  }
  return finder;
}

void Hider::Push() {
  if (Head == nullptr) {
    Head = this;
    Tail = this;
  } else {
    Tail->Next = this;
    this->Prev = Tail;
    Tail = this;
  }
  Length++;
}

void Hider::DecreaseCount() {
  count--;
  if (count <= 0) {
    Remove();
  }
}

void Hider::Remove() {
  if (this == Head) {
    if (this->Next != nullptr) {
      this->Next->Prev = nullptr;
      Head = this->Next;
    } else {
      Head = nullptr;
      Tail = nullptr;
    }
  } else if (this == Tail) {
    this->Prev->Next = nullptr;
    Tail = this->Prev;
  } else {
    this->Prev->Next = this->Next;
    this->Next->Prev = this->Prev;
  }
  delete this;
  Length--;
  return;
}
void Hider::RemoveAll() {
  Length = 0;

  if (Head == nullptr) {
    // std::cout << "List is already NULL" << std::endl;
    return;
  } else if (Head->Next != nullptr) {
    RemoveAll(Head->Next);
  }
  Head->Remove();
  Head = nullptr;
  Tail = nullptr;
}
void Hider::RemoveAll(Hider* head) {
  if (head->Next != nullptr) {
    RemoveAll(head->Next);
  }
  head->Remove();
}

// �� ������
Poisoner* Poisoner::Head = nullptr;
Poisoner* Poisoner::Tail = nullptr;
int Poisoner::Length = 0;

Poisoner::Poisoner(Character* _poisoner, int _count)
    : poisoner(_poisoner),
      count(_count),
      poison_dmg(_poisoner->GetAtk() * 0.2),
      Next(nullptr),
      Prev(nullptr) {}
void Poisoner::NewPoisoner(Character* _poisoner, int _count) {
  if (_poisoner) {
    Poisoner* node = new Poisoner(_poisoner, _count);
    node->Push();
  }
}

Poisoner* Poisoner::FindIsPoisoner(Character* character) {
  if (!Head) return nullptr;

  Poisoner* finder = Head;
  while (true) {
    if (finder->poisoner == character) {
      break;
    } else if (finder->Next) {
      finder = finder->Next;
    } else {
      return nullptr;
    }
  }
  return finder;
}
void Poisoner::Push() {
  if (Head == nullptr) {
    Head = this;
    Tail = this;
  } else {
    Tail->Next = this;
    this->Prev = Tail;
    Tail = this;
  }
  Length++;
}

void Poisoner::DecreaseCount() {
  count--;
  if (count <= 0) {
    Remove();
  }
}

void Poisoner::Remove() {
  if (this == Head) {
    if (this->Next != nullptr) {
      this->Next->Prev = nullptr;
      Head = this->Next;
    } else {
      Head = nullptr;
      Tail = nullptr;
    }
  } else if (this == Tail) {
    this->Prev->Next = nullptr;
    Tail = this->Prev;
  } else {
    this->Prev->Next = this->Next;
    this->Next->Prev = this->Prev;
  }
  delete this;
  Length--;
  return;
}
void Poisoner::RemoveAll() {
  Length = 0;

  if (Head == nullptr) {
    // std::cout << "List is already NULL" << std::endl;
    return;
  } else if (Head->Next != nullptr) {
    RemoveAll(Head->Next);
  }
  Head->Remove();
  Head = nullptr;
  Tail = nullptr;
}
void Poisoner::RemoveAll(Poisoner* head) {
  if (head->Next != nullptr) {
    RemoveAll(head->Next);
  }
  head->Remove();
}

// �� �ߵ���
Poisoned* Poisoned::Head = nullptr;
Poisoned* Poisoned::Tail = nullptr;
int Poisoned::Length = 0;

Poisoned::Poisoned(Character* _poisoned, int _count, int _dmg)
    : poisoned(_poisoned), count(_count), poison_dmg(_dmg), Next(nullptr), Prev(nullptr) {
  std::cout << poisoned->GetName() << "��(��) �ߵ��Ǿ���." << std::endl;
  SYSTEM_MESSAGE_DELAY;
}
void Poisoned::NewPoisoned(Character* _poisoned, int _count, int _dmg) {
  if (_poisoned) {
    if (Poisoned* node = FindIsPoisoned(_poisoned)) {
      // if (node->IsFullStack()) {
      //  node->poison_dmg[0] = node->poison_dmg[1];
      //  node->count[0] = node->count[1];
      //  node->stack--;
      //}
      if (node->poison_dmg < _dmg) node->poison_dmg = _dmg;
      if (node->count < _count) node->count = _count;
      // node->stack++;
    } else {
      node = new Poisoned(_poisoned, _count, _dmg);
      node->Push();
    }
  }
}

Poisoned* Poisoned::FindIsPoisoned(Character* character) {
  if (!Head) return nullptr;

  Poisoned* finder = Head;
  for (int i = 0; i < Length; i++) {
    if (finder->poisoned == character) {
      break;
    } else if (finder->Next != nullptr) {
      finder = finder->Next;
    } else {
      return nullptr;
    }
  }
  return finder;
}
// bool Poisoned::IsFullStack() { return stack >= POISON_STACK_MAX; }
void Poisoned::Push() {
  if (Head == nullptr) {
    Head = this;
    Tail = this;
  } else {
    Tail->Next = this;
    this->Prev = Tail;
    Tail = this;
  }
  Length++;
}

void Poisoned::DecreaseCount() {
  if (count > 0) count--;
  if (count <= 0) {
    Remove();
  }
}

void Poisoned::PoisonDamage() {
  int dmg = poison_dmg;
  std::cout << poisoned->GetName() << "�� " << dmg << "��ŭ�� �� ���ظ� �Ծ���."
            << std::endl;
  SYSTEM_MESSAGE_DELAY;

  poisoned->SetHp(poisoned->GetHp() - poison_dmg);
  DecreaseCount();
  poisoned->CheckIsDead();
}

void Poisoned::Remove() {
  if (this == Head) {
    if (this->Next != nullptr) {
      this->Next->Prev = nullptr;
      Head = this->Next;
    } else {
      Head = nullptr;
      Tail = nullptr;
    }
  } else if (this == Tail) {
    this->Prev->Next = nullptr;
    Tail = this->Prev;
  } else {
    this->Prev->Next = this->Next;
    this->Next->Prev = this->Prev;
  }
  delete this;
  Length--;
  return;
}
void Poisoned::RemoveAll() {
  Length = 0;

  if (Head == nullptr) {
    // std::cout << "List is already NULL" << std::endl;
    return;
  } else if (Head->Next != nullptr) {
    RemoveAll(Head->Next);
  }
  Head->Remove();
  Head = nullptr;
  Tail = nullptr;
}
void Poisoned::RemoveAll(Poisoned* head) {
  if (head->Next != nullptr) {
    RemoveAll(head->Next);
  }
  head->Remove();
}

// ��������� �º�
FairParty::FairParty(Character* _Owner)
    : Skill::Skill(FAIR_PARTY, _Owner, 3, 0, SkillType::BUFF,
                   "�� �� ���� ��� ���⿡ ���� �����ϴ�.") {
  name = "��������� �º�";
}

void FairParty::Use(Character& Target) {
  if (IsAvailable()) {
    Hider::NewHider(Owner, 1);
    Poisoner::NewPoisoner(Owner, 2);
    std::cout << Owner->GetName() << "(��)�� " << GetName() << "�� ����ߴ�!"
              << std::endl;
    if (IsAvailable()) cooldown_remain = cooldown + 1;
    SYSTEM_MESSAGE_DELAY;
  }
}