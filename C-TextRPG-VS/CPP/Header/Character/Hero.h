#pragma once
#include "Character.h"
#include "Skill.h"
//int gold = 0;

#define HERO_SKILL_MAX 3

class Hero : public Character {

  double exp;
  int max_exp;

  Skill * skills;

 public:
  Hero();
  Hero(std::string _name, int _lvl);
  Hero(const Hero& other);

  //Gold

  //Get
  int GetMaxExpForCurrentLvl() const;

  //Set
  void SetSkills(int _slot, Skill& _skills);

  void GiveExp(int _exp);

  virtual void PrintStatus(short x = 0);
  virtual void PrintStatus(short x, short y);
  void PrintExp();

  ~Hero();
};