#pragma once
#include <string>

#include "System.h"

#define PARTY_MAX 3  // ��, �Ʊ� ���� ĳ���� �ִ� ��

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
  //������
  Character();
  Character(std::string _name, Class class_of_character, int _lvl);
  Character(std::string _name, Class class_of_character, int _lvl,
            double _adjust);  // ���� ����ġ ���� ĳ���� ������
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
  void Attack(Character* target);

  // Check
  virtual bool CheckIsDead();

  // Print
  virtual void PrintStatus(short x = 0);
  virtual void PrintStatus(short x, short y);

  void PrintHp();
  void PrintHpBar();
  void PrintAtk();
  void PrintDef();
  void PrintSpd();
  void PrintLvl();

  // �Ҹ���
  virtual ~Character();
};

#define HERO_SKILL_MAX 3

enum class SkillType { ATTACK, DEBUFF, HEAL, BUFF, PROTECT };

enum SkillIndex {
  NONE,
  STRONG_ATTACK,
  PROTECT,
  FAIR_PARTY,
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

class Protector {
 public:
  Protector(Character* _protector, int _count, Character* _is_protected_1,
            Character* _is_protected_2 = nullptr);
  // void ProtectNow(Character* _is_protected);
  // void ProtectEnd(Character* _is_protected);  // Now�� ���� ���� ����
  // void Switch(Character*, Character*);

  static void NewProtector(Character* _protector, int _count,
                           Character* _is_protected_1,
                           Character* _is_protected_2 = nullptr);

  static Protector* FindIsProtected(Character* character);
  static Protector* FindIsProtecting(Character* character);
  Character* GetProtector() { return protector; }

  static Character* ProtectorChecker(Character* target);

  void Push();

  void DecreaseCount();

  void Remove();
  static void RemoveAll();

  static const Protector* GetHead() { return Head; }
  static const Protector* GetTail() { return Tail; }

 private:
  static void RemoveAll(Protector* head);

 private:
  Character* is_protected[PARTY_MAX - 1];
  Character* protector;
  int count;

  static Protector* Head;
  static Protector* Tail;

  Protector* Next;
  Protector* Prev;

  static int Length;
};

class Hider {
 public:
  Hider(Character* _hided, int _count);

  static void NewHider(Character* _hided, int _count);

  static Hider* FindIsHiding(Character* character);
  Character* GetHided() { return hided; }

  void Push();

  void DecreaseCount();

  void Remove();
  static void RemoveAll();

  static const Hider* GetHead() { return Head; }
  static const Hider* GetTail() { return Tail; }

 private:
  static void RemoveAll(Hider* head);

 private:
  Character* hided;
  int count;

  static Hider* Head;
  static Hider* Tail;

  Hider* Next;
  Hider* Prev;

  static int Length;
};

class Poisoner {
 public:
  Poisoner(Character* _poisoner, int _count);
  static void NewPoisoner(Character* _poisoner, int _count);

  static Poisoner* FindIsPoisoner(Character* character);
  Character* GetPoisoner() { return poisoner; }
  int GetPoisonDmg() const { return poison_dmg; }

  void Push();

  void DecreaseCount();

  void Remove();
  static void RemoveAll();

  static const Poisoner* GetHead() { return Head; }
  static const Poisoner* GetTail() { return Tail; }

 private:
  static void RemoveAll(Poisoner* head);

 private:
  Character* poisoner;
  int count;
  int poison_dmg;

  static Poisoner* Head;
  static Poisoner* Tail;

  Poisoner* Next;
  Poisoner* Prev;

  static int Length;
};

#define POISON_STACK_MAX 2

class Poisoned {
 public:
  Poisoned(Character* _poisoner, int _count, int _dmg);
  static void NewPoisoned(Character* _poisoner, int _count, int _dmg);

  static Poisoned* FindIsPoisoned(Character* character);
  Character* GetPoisoner() { return poisoned; }

  int GetPoisonDmg() const { return poison_dmg; }

  // bool IsFullStack();

  void Push();

  void DecreaseCount();
  void PoisonDamage();

  void Remove();
  static void RemoveAll();

  static const Poisoned* GetHead() { return Head; }
  static const Poisoned* GetTail() { return Tail; }

 private:
  static void RemoveAll(Poisoned* head);

 private:
  Character* poisoned;
  int count;
  int poison_dmg;
  // int stack;

  static Poisoned* Head;
  static Poisoned* Tail;

  Poisoned* Next;
  Poisoned* Prev;

  static int Length;
};

class StrongAttack : public Skill {  // 1 ���� ������
 public:
  StrongAttack(Character* _Owner);

  virtual void Use(Character& _Target);
};

class Protect : public Skill {  // 2 ��ȣ
 public:
  Protect(Character* _Owner);

  virtual void Use(Character& Target);

 private:
  int protect_count;
};

class FairParty
    : public Skill {  // 3 ��������� �º� ( �� �� ���� & �Ϲݰ��� 3�� ���� ��
                      // �ο� ) ( �� : ���ݷ��� 25�ۼ�Ʈ )
 public:
  FairParty(Character* Owner);

  virtual void Use(Character& Owner);
};

class Smash : public Skill {  // 4 ȥ���� �ϰ� ( �� �� ��ŵ & ���� ������ 3����
                              // ����� ) ��Ÿ�� : 3��
 public:
  Smash(Character* Owner);

  virtual void Use(Character& Target);

 private:
  bool is_charging;
  Character& Target;
};

class Roar : public Skill {  // 5 ������ ��ȿ ( ���� + 5, �̹� �� ���� ���
                             // ���� ��� ) ��Ÿ�� : 2��
 public:
  Roar(Character* Owner);

  virtual void Use();
  virtual void Use(Hero** player);
};

class EvilParty : public Skill {  // 6 ����� ���� ( ��� ������ ���ݷ���
                                  // 70%��ŭ�� ����� , �� �ο� )
 public:
  EvilParty(Character* Owner);

  virtual void Use(Enemy** enemy);
};

void NewPlayerCharacter(Hero** _Player, int _lvl);
// void PlayerArrayAlign(Hero** Player);
int GetNumOfPlayableHeroes(Hero** _Player);
void Swap(Hero*, Hero*);

Character* SelectTarget(Enemy**);
Character* SelectTarget(Hero**);

// �����͹迭�� ���޹޾� ��� ������ ����
const int GetAvgLvlOfTeam(Hero** team);
const int GetAvgLvlOfTeam(Enemy** team);

void LobbyPlayerStatus(Hero** player);
void CombatPrintStatus(Hero** player, Enemy** enemy, int allies_personnel,
                       int enemies_personnel);