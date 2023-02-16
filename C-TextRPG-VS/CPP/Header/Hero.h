#pragma once
#include "Character.h"
class Hero : public Character {
  double exp;
  int max_exp;

  static int gold;

 public:
  Hero();
  Hero(const Hero& _hero);
  ~Hero();
};