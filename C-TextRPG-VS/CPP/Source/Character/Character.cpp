#include "Character.h"

#include "pch.h"

Character::Character()
    : type(CharacterType::BASE),
      name("Character"),
      class_of_character(Class::COMMON),
      max_hp(COMMON_MAXHP_ORIGIN),
      hp(max_hp),
      atk(COMMON_ATK_ORIGIN),
      def(COMMON_DEF_ORIGIN),
      spd(COMMON_SPD_ORIGIN),
      lvl(1),
      turn_spd(0),
      turn_waiter(0),
      is_dead(false) {
  // std::cout << "기본 생성자 호출" << std::endl;
}

Character::Character(std::string _name, Class class_of_character, int _lvl)
    : type(CharacterType::BASE),
      class_of_character(class_of_character),
      lvl(_lvl),
      turn_spd(0),
      turn_waiter(0),
      is_dead(false) {
  // std::cout << "매개변수 생성자 호출" << std::endl;
  if (_name.length() > NAME_LIMIT) {
    std::cout << "ERROR : name out of range (name limit : " << NAME_LIMIT << ")"
              << std::endl;
    _name = "Character";
  }
  name = _name;
  int lvl_for_stat = 0;
  if (_lvl > 0) {
    lvl_for_stat = _lvl - 1;
  } else if (_lvl > 10) {
    std::cout << "ERROR : over level max" << std::endl;
    lvl_for_stat = 10;
  } else {
    std::cout << "ERROR : lvl out of range" << std::endl;
    lvl_for_stat = 1;
  }
  switch (class_of_character) {
    case Class::COMMON: {
      max_hp = COMMON_MAXHP_ORIGIN + COMMON_MAXHP_PER_LVL * lvl_for_stat;
      atk = COMMON_ATK_ORIGIN + COMMON_ATK_PER_LVL * lvl_for_stat;
      def = COMMON_DEF_ORIGIN + COMMON_DEF_PER_LVL * lvl_for_stat;
      spd = COMMON_SPD_ORIGIN + COMMON_SPD_PER_LVL * lvl_for_stat;
      hp = max_hp;
      break;
    }
    case Class::TANKER: {
      max_hp = TANKER_MAXHP_ORIGIN + TANKER_MAXHP_PER_LVL * lvl_for_stat;
      atk = TANKER_ATK_ORIGIN + TANKER_ATK_PER_LVL * lvl_for_stat;
      def = TANKER_DEF_ORIGIN + TANKER_DEF_PER_LVL * lvl_for_stat;
      spd = TANKER_SPD_ORIGIN + TANKER_SPD_PER_LVL * lvl_for_stat;
      hp = max_hp;
      break;
    }
    case Class::THIEF: {
      max_hp = THIEF_MAXHP_ORIGIN + THIEF_MAXHP_PER_LVL * lvl_for_stat;
      atk = THIEF_ATK_ORIGIN + THIEF_ATK_PER_LVL * lvl_for_stat;
      def = THIEF_DEF_ORIGIN + THIEF_DEF_PER_LVL * lvl_for_stat;
      spd = THIEF_SPD_ORIGIN + THIEF_SPD_PER_LVL * lvl_for_stat;
      hp = max_hp;
      break;
    }
      // case Class::ARCHOR: {
      //  max_hp =    ARCHOR_MAXHP_ORIGIN + ARCHOR_MAXHP_PER_LVL * lvl_for_stat;
      //  atk =       ARCHOR_ATK_ORIGIN   + ARCHOR_ATK_PER_LVL * lvl_for_stat;
      //  def =       ARCHOR_DEF_ORIGIN   + ARCHOR_DEF_PER_LVL * lvl_for_stat;
      //  spd =       ARCHOR_SPD_ORIGIN   + ARCHOR_SPD_PER_LVL * lvl_for_stat;
      //  hp = max_hp;
      //}
  }
}

Character::Character(std::string _name, Class class_of_character, int _lvl,
                     double _adjust)
    : type(CharacterType::BASE),
      class_of_character(class_of_character),
      lvl(_lvl),
      turn_spd(0),
      turn_waiter(0),
      is_dead(false) {
  // std::cout << "매개변수 생성자 호출" << std::endl;
  if (_name.length() > NAME_LIMIT) {
    std::cout << "ERROR : name out of range (name limit : " << NAME_LIMIT << ")"
              << std::endl;
    _name = "Character";
  }
  name = _name;
  int lvl_for_stat = 0;
  if (_lvl > 0) {
    lvl_for_stat = _lvl - 1;
  } else if (_lvl > 10) {
    std::cout << "ERROR : over level max" << std::endl;
    lvl_for_stat = 10;
  } else {
    std::cout << "ERROR : lvl out of range" << std::endl;
    lvl_for_stat = 1;
  }
  max_hp =
      (COMMON_MAXHP_ORIGIN + COMMON_MAXHP_PER_LVL * lvl_for_stat) * _adjust;
  hp = max_hp;
  atk = (COMMON_ATK_ORIGIN + COMMON_ATK_PER_LVL * lvl_for_stat) * _adjust;
  def = (COMMON_DEF_ORIGIN + COMMON_DEF_PER_LVL * lvl_for_stat) * _adjust;
  spd = (COMMON_SPD_ORIGIN + COMMON_SPD_PER_LVL * lvl_for_stat) * _adjust;
}

Character::Character(const Character& other)
    : type(other.type),
      name(other.name),
      class_of_character(other.class_of_character),
      max_hp(other.max_hp),
      hp(other.hp),
      atk(other.atk),
      def(other.def),
      spd(other.spd),
      lvl(other.lvl),
      turn_spd(other.turn_spd),
      turn_waiter(other.turn_waiter),
      is_dead(other.is_dead) {
  // std::cout << "복사 생성자 호출" << std::endl;
}

void Character::LvlUp() {
  lvl++;
  max_hp += COMMON_MAXHP_PER_LVL;
  hp += COMMON_MAXHP_PER_LVL;
  atk += COMMON_ATK_PER_LVL;
  def += COMMON_DEF_PER_LVL;
  spd += COMMON_SPD_PER_LVL;
  std::cout << name << "의 레벨이 올랐다!" << std::endl;
  SYSTEM_MESSAGE_DELAY;
}

std::string Character::GetClass() const {
  std::string class_name;
  switch (class_of_character) {
    case Class::COMMON:
      class_name = "COMMON";
      break;
    case Class::TANKER:
      class_name = "TANKER";
      break;
    case Class::THIEF:
      class_name = "THIEF";
      break;
    default:
      std::cout << "ERROR : no class like that" << std::endl;
  }
  return class_name;
}

std::string Character::GetName() const { return name; }

void Character::SetType(CharacterType _type) { type = _type; }

void Character::SetMaxHp(int _max_hp) { max_hp = _max_hp; }
void Character::SetHp(int _hp) {
  if (_hp > max_hp) {
    _hp = max_hp;
  }
  hp = _hp;
}
void Character::SetAtk(int _atk) { atk = _atk; }
void Character::SetDef(int _def) { def = _def; }
void Character::SetSpd(int _spd) { spd = _spd; }
void Character::SetLvl(int _lvl) {
  if (_lvl > CHARACTER_LVL_MAX) {
    _lvl = CHARACTER_LVL_MAX;
  }
  lvl = _lvl;
}

void Character::SetTurnSpd(double _turn_spd) { turn_spd = _turn_spd; }
void Character::SetTurnWaiter(double _turn_waiter) {
  turn_waiter = _turn_waiter;
}
bool Character::IsTurn() const { return turn_waiter >= 100; }

void Character::AddTurnWaiter(double _turn_waiter) {
  turn_waiter += _turn_waiter;
}

void Character::Attack(Character* target) {
  int damage = 0;
  std::cout << name << "가 " << target->name << "을 공격하려고 한다";
  for (int i = 0; i < 3; i++) {
    printf(" .");
    Sleep(500);
  }

  target = Protector::ProtectorChecker(target);

  ENDL;

  damage = atk - target->def;
  if (damage < 0) damage = 0;

  target->hp -= damage;
  std::cout << target->name << "은 " << damage << "의 피해를 입었다"
            << std::endl;

  if (Poisoner* node = Poisoner::FindIsPoisoner(this)) {
    Poisoned::NewPoisoned(target, 3, node->GetPoisonDmg());
  }

  SYSTEM_MESSAGE_DELAY;

  //
  //    if(!(target.CheckIsDead())) {
  //        std::cout << target.name << "은 반격했다";
  //        for (int i = 0; i < 3; i++) {
  //            printf(" .");
  //            Sleep(500);
  //        }
  //        if (damage = target.atk - def < 0) {
  //            damage = 0;
  //
  //        hp -= damage;
  //
  //        std::cout << name << "은 " << damage << "의 피해를 입었다" <<
  //        std::endl; SYSTEM_MESSAGE_DELAY; CheckIsDead();
  //        }
  //    }
}

// void Character::BoostMaxHp(int _amount, int duration) {
//  if (duration) {
//    max_hp = _amount;
//  }
//}
//
// void Character::BoostAtk(int _amount, int duration) {
//  if (duration) {
//    atk += _amount;
//  }
//}
// void Character::BoostDef(int _amount, int duration) {
//  if (duration) {
//    def += _amount;
//  }
//}
// void Character::BoostSpd(int _amount, int duration) {
//  if (duration) {
//    spd += _amount;
//  }
//}

bool Character::CheckIsDead() {
  if (hp <= 0) {
    if (!is_dead) {
      hp = 0;
      is_dead = true;
      std::cout << name << "은 쓰러졌다." << std::endl;
      Poisoned* node = Poisoned::FindIsPoisoned(this);

      if (node != nullptr) node->Remove();

      SYSTEM_MESSAGE_DELAY;
    }
  } else {
    is_dead = false;
  }
  return is_dead;
}

CharacterType Character::GetType() const { return type; }
int Character::GetMaxHp() const { return max_hp; }
double Character::GetHp() const { return hp; }
int Character::GetAtk() const { return atk; }
int Character::GetDef() const { return def; }
int Character::GetSpd() const { return spd; }
int Character::GetLvl() const { return lvl; }

double Character::GetTurnSpd() const { return turn_spd; }

double Character::GetTurnWaiter() const { return turn_waiter; }

void Character::PrintStatus(short x) {
  gotox(x);
  for (int i = 0; i < STATUS_LENGTH; i++) {
    std::cout << "=";
  }
  ENDL;

  gotox(x);
  SET_FORMAT_WIDTH_L(NAME_LIMIT + 2);
  std::cout << GetName();
  RESET_FORMAT;
  SET_FORMAT_WIDTH_R(STATUS_LENGTH - NAME_LIMIT - 2);
  std::cout << GetClass() << std::endl;

  gotox(x);
  RESET_FORMAT;

  PrintHp();
  PrintHpBar();
  ENDL;

  gotox(x);
  PrintAtk();
  PrintDef();
  PrintSpd();
  ENDL;

  gotox(x);
  for (int i = 0; i < STATUS_LENGTH; i++) {
    std::cout << "-";
  }
  ENDL;

  gotox(x);
  std::cout << "                        ";
  Character::PrintLvl();
  ENDL;

  gotox(x);
  for (int i = 0; i < STATUS_LENGTH; i++) {
    std::cout << "=";
  }
  ENDL;
}
void Character::PrintStatus(short x, short y) {
  gotoxy(x, y);
  for (int i = 0; i < STATUS_LENGTH; i++) {
    std::cout << "=";
  }
  ENDL;

  gotox(x);
  SET_FORMAT_WIDTH_L(NAME_LIMIT + 2);
  std::cout << GetName();
  RESET_FORMAT;
  SET_FORMAT_WIDTH_R(STATUS_LENGTH - NAME_LIMIT - 2);
  std::cout << GetClass() << std::endl;

  gotox(x);
  RESET_FORMAT;

  PrintHp();
  PrintHpBar();
  ENDL;

  gotox(x);
  PrintAtk();
  PrintDef();
  PrintSpd();
  ENDL;

  gotox(x);
  for (int i = 0; i < STATUS_LENGTH; i++) {
    std::cout << "-";
  }
  ENDL;

  gotox(x);
  std::cout << "                        ";
  Character::PrintLvl();
  ENDL;

  gotox(x);
  for (int i = 0; i < STATUS_LENGTH; i++) {
    std::cout << "=";
  }
  ENDL;
}

double Character::GetHpRemain() const {
  if (max_hp != 0) {
    return (hp / max_hp) * 100;
  } else {
    std::cout << "ERROR : max_hp == 0!!" << std::endl;
    return 0;
  }
}

void Character::PrintHp() {
  Poisoned* node = Poisoned::FindIsPoisoned(this);
  bool is_poisoned = node != nullptr;

  if (is_poisoned) TextColor(GREEN, BLACK);

  std::cout << "HP ";
  SET_FORMAT_WIDTH_R(3);
  std::cout << hp;
  RESET_FORMAT;
  std::cout << " / ";
  SET_FORMAT_WIDTH_L(3);
  std::cout << max_hp;
  RESET_FORMAT;

  if (is_poisoned) TextColor();
  // SET_FORMAT_2PREC;
  // std::cout << GetHpRemain() << "%)";
  // RESET_FORMAT;
}
void Character::PrintHpBar() {
  Poisoned* node = Poisoned::FindIsPoisoned(this);
  bool is_poisoned = node != nullptr;

  if (is_poisoned) TextColor(GREEN, BLACK);

  float hp_per_box;
  if (HP_BAR_LENGTH) {
    hp_per_box = 100 / HP_BAR_LENGTH;
  } else {
    printf("ERROR : HP_BAR_LENGTH = 0!!");
  }
  for (int i = 1; i <= HP_BAR_LENGTH; i++) {
    if ((int)GetHpRemain() > hp_per_box * i) {
      printf("■");
    } else {
      printf("□");
    }
  }
  if (is_poisoned) TextColor();
}

void Character::PrintAtk() {
  std::cout << "ATK ";
  SET_FORMAT_WIDTH_L(4);

  Poisoner* poisoner = Poisoner::FindIsPoisoner(this);
  bool is_poisoner = poisoner != nullptr;

  if (is_poisoner) {
    TextColor(GREEN, BLACK);
  }
  std::cout << GetAtk();
  if (is_poisoner) {
    TextColor();
  }
}

void Character::PrintDef() {
  std::cout << "DEF ";
  SET_FORMAT_WIDTH_L(4);
  std::cout << GetDef();
  RESET_FORMAT;
}
void Character::PrintSpd() {
  std::cout << "SPD ";
  SET_FORMAT_WIDTH_L(4);
  std::cout << GetSpd();
  RESET_FORMAT;
}
void Character::PrintLvl() {
  std::cout << "lvl ";
  SET_FORMAT_WIDTH_R(2);
  std::cout << GetLvl();
  RESET_FORMAT;
}

Character::~Character() {
  // std::cout << "캐릭터 수 감소" << std::endl;
}

Skill* SkillSelect(Hero* TurnNowHero) {
  int skill_select = 0;
  Skill* UsingSkill = nullptr;
  TurnNowHero->PrintSkillsAll();
  std::cout << "0. 취소" << std::endl << std::endl;
  while (true) {
    std::cout << "사용할 스킬을 선택해주세요 : ";
    std::cin >> skill_select;

    if (skill_select == 0) break;  // 스킬 사용 취소

    if (skill_select >= 1 && skill_select <= 3) {
      if (TurnNowHero->GetSkill(skill_select - 1) != nullptr) {
        if (TurnNowHero->GetSkill(skill_select - 1)->IsAvailable()) {
          UsingSkill = TurnNowHero->GetSkill(skill_select - 1);
          break;
        } else {
          std::cout << "해당 스킬은 아직 사용할 수 없습니다." << std::endl;
        }
      } else {
        std::cout << "해당 스킬 슬롯은 비어있습니다." << std::endl;
        SYSTEM_MESSAGE_DELAY;
      }
    } else {
      std::cout << "선택 범위를 벗어났습니다." << std::endl;
      SYSTEM_MESSAGE_DELAY;
    }
  }
  return UsingSkill;
}

void NewPlayerCharacter(Hero** _Player, int _lvl) {
  int slot = GetNumOfPlayableHeroes(_Player);
  if (slot < PARTY_MAX) {
    std::string name;
    while (true) {
      std::string temp;
      std::cout << "영웅의 이름을 입력해주세요 : ";
      std::cin >> temp;

      if (temp.length() > NAME_LIMIT) {
        std::cout << "이름 길이 제한은 영어" << NAME_LIMIT << "자, 한글 "
                  << NAME_LIMIT / 2 << "자 입니다." << std::endl;
        SYSTEM_MESSAGE_DELAY;
      } else {
        name = temp;
        break;
      }
    }
    Class class_of_character = Class::COMMON;
    while (true) {
      int class_choice;
      std::cout << "1. 일반   2. 탱커   3. 도적" << std::endl;
      std::cout << "영웅의 직업을 선택해주세요 : ";
      std::cin >> class_choice;
      if (1 <= class_choice && class_choice <= 3) {
        switch (class_choice) {
          case 1:
            class_of_character = Class::COMMON;
            _Player[slot] = new Hero(name, class_of_character, _lvl);
            _Player[slot]->GiveSkill(STRONG_ATTACK);
            break;
          case 2:
            class_of_character = Class::TANKER;
            _Player[slot] = new Hero(name, class_of_character, _lvl);
            _Player[slot]->GiveSkill(PROTECT);
            break;
          case 3:
            class_of_character = Class::THIEF;
            _Player[slot] = new Hero(name, class_of_character, _lvl);
            _Player[slot]->GiveSkill(FAIR_PARTY);
            break;
        }
        break;
      } else {
        std::cout << "잘못된 입력입니다." << std::endl;
        continue;
      }
    }
  }
}
int GetNumOfPlayableHeroes(Hero** _Player) {
  int num_of_playble_heroes = 0;
  for (int i = 0; i < PARTY_MAX; i++) {
    if (_Player[i] != nullptr) {
      num_of_playble_heroes++;
    } else {
      break;
    }
  }
  return num_of_playble_heroes;
}

void Swap(Hero* _Hero1, Hero* _Hero2) {
  Hero* temp = _Hero1;
  _Hero1 = _Hero2;
  _Hero2 = temp;
}

// 대상 선택
Character* SelectTarget(Enemy** enemy) {
  Character* Target = nullptr;
  int personnel = 0;

  for (int i = 0; i < PARTY_MAX; i++) {
    if (enemy[i] != nullptr) {
      if (i) std::cout << "   ";
      std::cout << i + 1 << ". " << enemy[i]->GetName();
      if (enemy[i]->CheckIsDead()) std::cout << "(쓰러짐)";
      personnel++;
    } else {
      break;
    }
  }
  std::cout << "   0. 취소";
  ENDL;
  int target;
  while (true) {
    std::cout << "대상을 선택해주십시오 : ";
    std::cin >> target;

    if (target == 0) return nullptr;

    if (target > 0 && target <= personnel) {
      if (enemy[target - 1] != nullptr) {
        if (enemy[target - 1]->CheckIsDead() == false) {
          Target = enemy[target - 1];
          break;
        } else {  // 대상이 이미 죽었을 경우
          std::cout << "대상이 이미 쓰러졌습니다." << std::endl;
          SYSTEM_MESSAGE_DELAY;
        }
      }
    } else {  // 선택 범위를 벗어났을 경우
      std::cout << "선택 범위를 벗어났습니다." << std::endl;
      SYSTEM_MESSAGE_DELAY;
    }
  }
  if (Target != nullptr) {
    return Target;
  } else {
    return nullptr;
  }
}
Character* SelectTarget(Hero** Player) {
  Character* Target = nullptr;
  int personnel = 0;

  for (int i = 0; i < PARTY_MAX; i++) {
    if (Player[i] != nullptr) {
      if (i) std::cout << "   ";
      std::cout << i + 1 << ". " << Player[i]->GetName();
      if (Player[i]->CheckIsDead()) std::cout << "(쓰러짐)";
      personnel++;
    } else {
      break;
    }
  }
  std::cout << "   0. 취소";
  ENDL;
  int target;
  while (true) {
    std::cout << "대상을 선택해주십시오 : ";
    std::cin >> target;

    if (target == 0) return nullptr;

    if (target > 0 && target <= personnel) {
      if (Player[target - 1]->CheckIsDead() == false) {
        Target = Player[target - 1];
        break;
      } else {  // 대상이 이미 죽었을 경우
        std::cout << "대상이 이미 쓰러졌습니다." << std::endl;
      }
    } else {  // 선택 범위를 벗어났을 경우
      std::cout << "선택 범위를 벗어났습니다." << std::endl;
      SYSTEM_MESSAGE_DELAY;
    }
  }
  return Target;
}

const int GetAvgLvlOfTeam(Hero** team) {
  int personnel = 0;
  int sum = 0;

  for (int i = 0; i < PARTY_MAX; i++) {
    if (team[i] != nullptr) {
      sum += team[i]->GetLvl();
      personnel++;
    }
  }
  return sum / personnel;
}

const int GetAvgLvlOfTeam(Enemy** team) {
  int personnel = 0;
  int sum = 0;

  for (int i = 0; i < PARTY_MAX; i++) {
    if (team[i] != nullptr) {
      sum += team[i]->GetLvl();
      personnel++;
    }
  }
  return sum / personnel;
}

void LobbyPlayerStatus(Hero** player) {
  for (int i = 0; i < PARTY_MAX; i++) {
    player[i]->PrintStatus(i * 32, 0);
  }
}
void CombatPrintStatus(Hero** player, Enemy** enemy, int allies_personnel,
                       int enemies_personnel) {
  ClearFromY(0, 21);

  gotoy(0);
  for (int i = 0; i < allies_personnel; i++) {
    if (player[i]->CheckIsDead()) {
      TextColor(RED, BLACK);
    } else if (Hider::FindIsHiding(player[i])) {
      TextColor(DARK_GRAY, BLACK);
    }
    player[i]->PrintStatus();
    TextColor();
  }
  gotoxy(35, 0);
  for (int i = 0; i < 21; i++) {
    gotox(34);
    std::cout << "||" << std::endl;
  }
  gotoy(0);
  for (int i = 0; i < enemies_personnel; i++) {
    if (enemy[i]->CheckIsDead()) {
      TextColor(RED, BLACK);
    }
    enemy[i]->PrintStatus(40);
    TextColor();
  }
  gotoxy(0, 22);
}
