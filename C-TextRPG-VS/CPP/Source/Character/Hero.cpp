#include "Character.h"
#include "pch.h"

// int Hero::num_of_heroes = 0;

Hero::Hero() : Character::Character(), exp(0) {
  for (int i = 0; i < HERO_SKILL_MAX; i++) {
    skill[i] = nullptr;
  }
  SetType(CharacterType::HERO);
  max_exp = GetMaxExpForCurrentLvl();
  // num_of_heroes++;
}

Hero::Hero(std::string _name, Class class_of_character, int _lvl)
    : Character::Character(_name, class_of_character, _lvl), exp(0) {
  for (int i = 0; i < HERO_SKILL_MAX; i++) {
    skill[i] = nullptr;
  }
  SetType(CharacterType::HERO);
  max_exp = GetMaxExpForCurrentLvl();
  // num_of_heroes++;
}

Hero::Hero(const Hero& other)
    : Character::Character(other), exp(other.exp), max_exp(other.max_exp) {
  for (int i = 0; i < HERO_SKILL_MAX; i++) {
    skill[i] = new Skill(*(other.skill[i]));
    skill[i]->SetOwner(this);
  }
  // num_of_heroes++;
}

int Hero::GetMaxExpForCurrentLvl() const {
  int max_exp_for_each_lvl[CHARACTER_LVL_MAX - 1] = {20, 30, 40, 50, 60,
                                                     70, 80, 90, 100};
  return max_exp_for_each_lvl[Character::GetLvl() - 1];
}

Skill* Hero::GetSkill(int slot_number) { return skill[slot_number]; }

// int Hero::GetNumOfHeroes() { return num_of_heroes; }

void Hero::GiveExp(int _exp) {
  int prev_lvl = GetLvl();
  exp += _exp;
  // std::cout << "����ġ�� " << exp << "��ŭ �����!" << std::endl;
  // SYSTEM_MESSAGE_DELAY;
  while (true) {
    if (exp >= max_exp) {
      LvlUp();
      exp -= max_exp;
      max_exp = GetMaxExpForCurrentLvl();
    } else {
      break;
    }
  }
}

void Hero::GiveSkill(int _index) {
  int slot = GetEmptySkillSlot();
  switch (_index) {
    case NONE: {
      break;
    }
    case STRONG_ATTACK: {
      skill[slot] = new StrongAttack(this);
      break;
    }
    case PROTECT: {
      skill[slot] = new Protect(this);
      break;
    }
    case FAIR_PARTY: {
      skill[slot] = new FairParty(this);
      break;
    }
    default: {
      std::cout << "ERROR:UNDEFINED SKILL INDEX" << std::endl;
    }
  }
}

void Hero::PrintSkillsAll() {
  std::cout << "Skill  "
               "==============================================================="
            << std::endl;
  for (int i = 0; i < HERO_SKILL_MAX; i++) {
    std::cout << i + 1 << ". ";
    if (skill[i] != nullptr) {
      std::cout << skill[i]->GetName() << " | ";
      if (skill[i]->GetCoolDownRemain()) {
        std::cout << "���� ��� �� ( " << skill[i]->GetCoolDownRemain()
                  << "�� �� ��밡�� ) |";
      } else {
        std::cout << "��밡�� | ";
      }
      std::cout << skill[i]->GetDescription() << std::endl;

    } else {
      std::cout << "��ų ����" << std::endl;
      continue;
    }
  }
  std::cout << "============================================================="
               "========="
            << std::endl;
}

int Hero::GetEmptySkillSlot() {
  int empty_slot = -1;
  for (int i = 0; i < HERO_SKILL_MAX; i++) {
    if (skill[i] == nullptr) {
      empty_slot = i;
      break;
    } else {
      continue;
    }
    if (empty_slot == -1) {
      std::cout << "YOU CANNOT LEARN SKILL NO MORE! ( DEVELOPING.. )"
                << std::endl;
    }
  }
  return empty_slot;
}

SkillType Hero::GetSkillType(int slot_number) {
  return skill[slot_number]->GetSkillType();
}

void Hero::UseSkill(int slot_number, Character& Target) {
  skill[slot_number]->Use(Target);
}

void Hero::TurnEnd() {
  SetTurnWaiter(0);
  for (int i = 0; i < HERO_SKILL_MAX; i++) {
    if (skill[i] != nullptr) {
      if (skill[i]->GetCoolDownRemain()) {
        skill[i]->SetCoolDownRemain(skill[i]->GetCoolDownRemain() - 1);
      }
    }
  }
}

void Hero::PrintStatus(short x) {
  int OriginColor = LIGHT_GRAY;
  bool is_hiding = false;
  bool is_poisoner = false;
  bool is_poisoned = false;

  if (CheckIsDead()) {
    OriginColor = RED;
  } else {
    if (Hider::FindIsHiding(this)) is_hiding = true;
    if (Poisoner::FindIsPoisoner(this)) is_poisoner = true;
    if (Poisoned::FindIsPoisoned(this)) is_poisoned = true;
  }
  if (is_hiding) {
    OriginColor = DARK_GRAY;
  }
  TextColor(OriginColor);

  gotox(x);
  for (int i = 0; i < STATUS_LENGTH; i++) {
    std::cout << "=";
  }
  ENDL;

  gotox(x);

  SET_FORMAT_WIDTH_L(NAME_LIMIT + 2);
  std::cout << Character::GetName();
  RESET_FORMAT;
  SET_FORMAT_WIDTH_R(STATUS_LENGTH - NAME_LIMIT - 2);
  std::cout << GetClass() << std::endl;

  gotox(x);
  RESET_FORMAT;

  if (is_poisoned) TextColor(GREEN);
  PrintHp();
  PrintHpBar();
  if (is_poisoned) TextColor(OriginColor);
  ENDL;

  gotox(x);
  if (is_poisoner) TextColor(GREEN);
  Character::PrintAtk();
  if (is_poisoner) TextColor(OriginColor);
  Character::PrintDef();
  Character::PrintSpd();
  ENDL;

  gotox(x);
  for (int i = 0; i < STATUS_LENGTH; i++) {
    std::cout << "-";
  }
  ENDL;

  gotox(x);
  PrintExp();
  std::cout << "           ";
  Character::PrintLvl();
  ENDL;

  gotox(x);
  for (int i = 0; i < STATUS_LENGTH; i++) {
    std::cout << "=";
  }
  ENDL;
}

void Hero::PrintStatus(short x, short y) {
  int OriginColor = LIGHT_GRAY;
  bool is_hiding = false;
  bool is_poisoner = false;
  bool is_poisoned = false;

  if (CheckIsDead()) {
    OriginColor = RED;
  } else {
    if (Hider::FindIsHiding(this)) is_hiding = true;
    if (Poisoner::FindIsPoisoner(this)) is_poisoner = true;
    if (Poisoned::FindIsPoisoned(this)) is_poisoned = true;
  }
  if (is_hiding) {
    OriginColor = DARK_GRAY;
  }
  TextColor(OriginColor);
  gotoxy(x, y);
  for (int i = 0; i < STATUS_LENGTH; i++) {
    std::cout << "=";
  }
  ENDL;

  gotox(x);
  SET_FORMAT_WIDTH_L(NAME_LIMIT + 2);
  std::cout << Character::GetName();
  RESET_FORMAT;
  SET_FORMAT_WIDTH_R(STATUS_LENGTH - NAME_LIMIT - 2);
  std::cout << GetClass() << std::endl;

  gotox(x);
  RESET_FORMAT;
  if (is_poisoned) TextColor(GREEN, BLACK);
  PrintHp();
  PrintHpBar();
  if (is_poisoned) TextColor(OriginColor);
  ENDL;

  gotox(x);
  if (is_poisoner) TextColor(GREEN, BLACK);
  Character::PrintAtk();
  if (is_poisoner) TextColor(OriginColor);
  Character::PrintDef();
  Character::PrintSpd();
  ENDL;
  gotox(x);

  for (int i = 0; i < STATUS_LENGTH; i++) {
    std::cout << "-";
  }
  ENDL;

  gotox(x);
  PrintExp();
  std::cout << "           ";
  Character::PrintLvl();
  ENDL;

  gotox(x);
  for (int i = 0; i < STATUS_LENGTH; i++) {
    std::cout << "=";
  }
  ENDL;
}

void Hero::PrintExp() {
  std::cout << "EXP ";
  SET_FORMAT_WIDTH_R(3);
  std::cout << exp;
  RESET_FORMAT;
  std::cout << " / ";
  SET_FORMAT_WIDTH_L(3);
  std::cout << max_exp;
  RESET_FORMAT;
}

Hero::~Hero() {
  for (int i = 0; i < HERO_SKILL_MAX; i++) {
    if (skill[i] != nullptr) {
      delete skill[i];
    }
  }
  // num_of_heroes--;
}