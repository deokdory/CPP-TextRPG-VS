#pragma once
#include "System.h"
#include <string>

#define PARTY_MAX 3  // ��, �Ʊ� ���� ĳ���� �ִ� ��

#define NAME_LIMIT 14
#define CLASS_TOTAL 4

#define SET_FORMAT_WIDTH_L(length) \
  std::cout << std::setw(length) << std::setiosflags(std::ios::left)
#define SET_FORMAT_WIDTH_R(length) \
  std::cout << std::setw(length) << std::setiosflags(std::ios::right)
#define SET_FORMAT_2PREC \
  std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(2)

#define COMMON_MAXHP_ORIGIN 50
#define COMMON_ATK_ORIGIN 25
#define COMMON_DEF_ORIGIN 10
#define COMMON_SPD_ORIGIN 30

#define COMMON_MAXHP_PER_LVL 5
#define COMMON_ATK_PER_LVL 5
#define COMMON_DEF_PER_LVL 0
#define COMMON_SPD_PER_LVL 5

#define CHARACTER_LVL_MAX 10

#define STATUS_LENGTH 30
#define HP_BAR_LENGTH 18

enum class Class {
  COMMON,
  WARRIOR,
  ARCHOR,
  THIEF,
};

enum class CharacterType {
  BASE,
  HERO,
  ENEMY
};

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
  //������
  Character();
  Character(std::string _name, int _lvl);
  Character(std::string _name, int _lvl, double _adjust); // ���� ����ġ ���� ĳ���� ������
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

  // Combat
  void Attack(Character& target);

  // Boost
  void BoostMaxHp(int _amount, int duration);
  void BoostAtk(int _amount, int duration);
  void BoostDef(int _amount, int duration);
  void BoostSpd(int _amount, int duration);

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

  // �Ҹ���
  virtual ~Character();
};

#define HERO_SKILL_MAX 3

enum class SkillType {
  ATTACK,
  DEBUFF,
  HEAL,
  BUFF,
};

enum SkillIndex {
  NONE,
  STRONG_ATTACK
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
  Skill(int _index, Character* _owner, int _cooldown, int _cooldown_remain, SkillType _type, std::string _description);
  Skill(const Skill& other);

  // Get
  int GetCoolDown() const;
  int GetCoolDownRemain() const;
  std::string GetDescription() const;
  SkillType GetSkillType() const;

  // Set
  void SetCoolDown(int _cooldown);
  void SetOwner(Character* _character);

  bool IsAvailable();

  // Virtual
  virtual void Use(Character& _Target);
};

class StrongAttack : public Skill { // index : 1
 public:
  StrongAttack(Character* _Owner);

  virtual void Use(Character& _Target);
};

class Hero : public Character {
  //static int num_of_heroes;

  double exp;
  int max_exp;

  Skill* skill[HERO_SKILL_MAX];

 public:
  Hero();
  Hero(std::string _name, int _lvl);
  Hero(const Hero& other);

  // Get
  int GetMaxExpForCurrentLvl() const;
  Skill* GetSkill(int slot_number);
  //static int GetNumOfHeroes();

  // Set
  void GiveExp(int _exp);
  void GiveSkill(int _index);

  void PrintSkillsAll();
  int GetEmptySkillSlot();
  SkillType GetSkillType(int slot_number);
  void UseSkill(int slot_number, Character& Target);

  virtual void PrintStatus(short x = 0);
  virtual void PrintStatus(short x, short y);
  void PrintExp();

  ~Hero();
};

class Enemy : public Character {
  int reward_gold;
  int reward_exp;

 public:
  Enemy();
  Enemy(std::string _name, int _lvl);

  // Get
  int GetRewardGold() const;
  int GetRewardExp() const;

  // Get
  int GetRewardGoldForCurrentLvl();
  int GetRewardExpForCurrentLvl();

  virtual void PrintStatus(short x = 0);
  virtual void PrintStatus(short x, short y);
};

void NewPlayerCharacter(Hero** _Player, int _lvl);
void PlayerArrayAlign(Hero** Player);
int GetNumOfPlayableHeroes(Hero** _Player);
void Swap(Hero*, Hero*);