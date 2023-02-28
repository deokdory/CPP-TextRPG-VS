#pragma once
#include <string>

#include "System.h"

#define PARTY_MAX 3  // 적, 아군 공용 캐릭터 최대 수

#define NAME_LIMIT 14
#define CLASS_TOTAL 4

#define COMMON_MAXHP_ORIGIN 50
#define COMMON_ATK_ORIGIN 25
#define COMMON_DEF_ORIGIN 10
#define COMMON_SPD_ORIGIN 30

#define COMMON_MAXHP_PER_LVL 5
#define COMMON_ATK_PER_LVL 5
#define COMMON_DEF_PER_LVL 1
#define COMMON_SPD_PER_LVL 5

#define THIEF_MAXHP_ORIGIN 45
#define THIEF_ATK_ORIGIN 25
#define THIEF_DEF_ORIGIN 10
#define THIEF_SPD_ORIGIN 32

#define THIEF_MAXHP_PER_LVL 4
#define THIEF_ATK_PER_LVL 6
#define THIEF_DEF_PER_LVL 1
#define THIEF_SPD_PER_LVL 5

#define TANKER_MAXHP_ORIGIN 55
#define TANKER_ATK_ORIGIN 22
#define TANKER_DEF_ORIGIN 13
#define TANKER_SPD_ORIGIN 25

#define TANKER_MAXHP_PER_LVL 6
#define TANKER_ATK_PER_LVL 3
#define TANKER_DEF_PER_LVL 2
#define TANKER_SPD_PER_LVL 4

#define CHARACTER_LVL_MAX 10

#define STATUS_LENGTH 30
#define HP_BAR_LENGTH 18

enum class Class {
  COMMON,
  TANKER,
  THIEF,
};

enum class CharacterType { BASE, HERO, ENEMY };

class Character {
 protected:
  CharacterType type;

  std::string name;
  Class class_of_character;

  int max_hp;
  double hp;
  int atk;
  int def;
  int spd;

  int lvl;

  double turn_spd;
  double turn_waiter;

  bool is_dead;

 public:
  //생성자
  Character();
  Character(std::string _name, Class class_of_character, int _lvl);
  Character(std::string _name, Class class_of_character, int _lvl,
            double _adjust);  // 스탯 보정치 적용 캐릭터 생성자
  Character(const Character& other);

  std::string GetClass() const;
  std::string GetName() const;
  void LvlUp();

  // Get
  CharacterType GetType() const;
  int GetMaxHp() const;
  double GetHp() const;
  double GetHpRemain() const;
  int GetAtk() const;
  int GetDef() const;
  int GetSpd() const;
  int GetLvl() const;
  double GetTurnSpd() const;
  double GetTurnWaiter() const;
  bool IsTurn() const;

  // Set
  void SetType(CharacterType _type);
  void SetMaxHp(int _max_hp);
  void SetHp(int _hp);
  void SetAtk(int _atk);
  void SetDef(int _Def);
  void SetSpd(int _spd);
  void SetLvl(int _lvl);
  void SetTurnSpd(double _turn_spd);
  void SetTurnWaiter(double _turn_waiter);
  void AddTurnWaiter(double _turn_waiter);

  // Boost

  // Combat
  void Attack(Character& target);

  // Check
  virtual bool CheckIsDead();

  // Print
  virtual void PrintStatus(short x = 0);
  virtual void PrintStatus(short x, short y);

  void PrintHp() const;
  void PrintHpBar() const;
  void PrintAtk() const;
  void PrintDef() const;
  void PrintSpd() const;
  void PrintLvl() const;

  // 소멸자
  virtual ~Character();
};

#define HERO_SKILL_MAX 3

enum class SkillType { ATTACK, DEBUFF, HEAL, BUFF, PROTECT };

enum SkillIndex {
  NONE,
  STRONG_ATTACK,
  PROTECT,
  POISON_IN_WEAPON,
  SMASH,
  ROAR,
  SPRAY_KNIFE
};

class Skill : public Character {
 protected:
  int index;

  Character* Owner;

  int cooldown;
  int cooldown_remain;

  SkillType type;

  std::string description;

 public:
  Skill();
  Skill(int _index, Character* _owner, int _cooldown, int _cooldown_remain,
        SkillType _type, std::string _description);
  Skill(const Skill& other);

  // Get
  int GetCoolDown() const;
  int GetCoolDownRemain() const;
  std::string GetDescription() const;
  SkillType GetSkillType() const;

  // Set
  void SetCoolDown(int _cooldown);
  void SetOwner(Character* _character);
  void SetCoolDownRemain(int _cooldown_remain);

  bool IsAvailable();

  // Virtual
  virtual void Use(Character& _Target);
};

class StrongAttack : public Skill {  // index : 1
 public:
  StrongAttack(Character* _Owner);

  virtual void Use(Character& _Target);
};

class Protect : public Skill {  // 2
 public:
  Protect(Character* _Owner);

  virtual void Use(Character& Target);

 private:
  int protect_count;
};

class Protector {
 public:
  Protector(Character* _protector, int _count, Character* _is_protected_1, Character* _is_protected_2 = nullptr);
  void ProtectNow(Character* _is_protected);
  void ProtectEnd(Character* _is_protected); // Now와 같은 변수 전달
  void Switch(Character*, Character*);

  static Protector* NewProtector(Character* _protector, int _count,
                                 Character* _is_protected_1,
                                 Character* _i2_protected2 = nullptr);
  void Push();

  void DecreaseCount();

  void Remove();
  void RemoveAll();

  static Protector* GetHead();
  static Protector* GetTail();

 private:
  Character* is_protected[PARTY_MAX - 1];
  Character* protector;

  static Protector* Head;
  static Protector* Tail;

  static int Length;

  int count;
};

class PoisonInWeapon : public Skill {  // 3
 public:
  PoisonInWeapon(Character* Owner);

  virtual void Use();
};

class Smash : public Skill {  // 4
 public:
  Smash(Character* Owner);

  virtual void Use(Character& Target);

 private:
  bool is_charging;
  Character& Target;
};

class Roar : public Skill {
 public:
  Roar(Character* Owner);

  virtual void Use(Hero** player);
};

class Hero : public Character {
  // static int num_of_heroes;

  double exp;
  int max_exp;

  Skill* skill[HERO_SKILL_MAX];

 public:
  Hero();
  Hero(std::string _name, Class class_of_character, int _lvl);
  Hero(const Hero& other);

  // Get
  int GetMaxExpForCurrentLvl() const;
  Skill* GetSkill(int slot_number);
  // static int GetNumOfHeroes();

  // Set
  void GiveExp(int _exp);
  void GiveSkill(int _index);

  void PrintSkillsAll();
  int GetEmptySkillSlot();
  SkillType GetSkillType(int slot_number);
  void UseSkill(int slot_number, Character& Target);

  void TurnEnd();

  virtual void PrintStatus(short x = 0);
  virtual void PrintStatus(short x, short y);
  void PrintExp();

  ~Hero();
};

Skill* SkillSelect(Hero* TurnNowHero);

enum EnemyIndex { WOLF = 1, GOBLIN, DEVILKING };

class Enemy : public Character {
  int index;

  int reward_gold;
  int reward_exp;

 public:
  Enemy();
  Enemy(int _index, int _lvl);

  // Get
  static const std::string GetNameWithIndex(int _index);
  int GetRewardGold() const;
  int GetRewardExp() const;

  int GetRewardGoldForCurrentLvl();
  int GetRewardExpForCurrentLvl();

  // Set

  virtual void PrintStatus(short x = 0);
  virtual void PrintStatus(short x, short y);

  virtual bool CheckIsDead();

  ~Enemy();
};

void NewPlayerCharacter(Hero** _Player, int _lvl);
void PlayerArrayAlign(Hero** Player);
int GetNumOfPlayableHeroes(Hero** _Player);
void Swap(Hero*, Hero*);

Character* SelectTarget(Enemy**);
Character* SelectTarget(Hero**);

// 포인터배열을 전달받아 평균 레벨을 구함
const int GetAvgLvlOfTeam(Hero** team);
const int GetAvgLvlOfTeam(Enemy** team);

void LobbyPlayerStatus(Hero** player);