#pragma once
#include "Skill.h"
class StrongAttack : public Skill {
 private:
  Character Owner;
 public:
  StrongAttack(Character _Owner);

  virtual void Use(Character _Target);
};

