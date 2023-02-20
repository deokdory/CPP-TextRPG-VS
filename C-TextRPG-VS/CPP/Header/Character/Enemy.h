#pragma once
#include "Character.h"

enum class EnemyType {WOLF, GOBLIN, DEVILKING};

class Enemy : public Character
{
  EnemyType enemy_type;

	int reward_gold;
	int reward_exp;

public:
	Enemy();
	Enemy(std::string _name, int _lvl);

	int GetRewardGold() const;
	int GetRewardExp() const;
};
