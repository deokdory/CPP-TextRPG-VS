#pragma once
#include "Character.h"

class Enemy : public Character
{
	int reward_gold;
	int reward_exp;

public:
	Enemy();
	Enemy(std::string _name, int _lvl);

	//Get
	int GetRewardGold() const;
	int GetRewardExp() const;

	// Get
  int GetRewardGoldForCurrentLvl();
  int GetRewardExpForCurrentLvl();
};
