#pragma once

#include "Hero.h"
//#include "Enemy.h"
//#include "Quest.h"

enum class Place {
	FOREST, CAVE, MOUNTAIN
};

enum ActionInCombat {
	ATTACK = 1, USE_SKILL, USE_ITEM, RUNAWAY
};

void Combat();

class Combat
{
	int total_reward_gold;

public:
	Combat(Place _place);
};

