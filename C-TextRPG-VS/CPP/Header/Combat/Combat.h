#pragma once

#include "Hero.h"
#include "Enemy.h"
//#include "Quest.h"

enum class Place {
	FOREST, CAVE, MOUNTAIN
};

enum ActionInCombat {
	ATTACK = 1, USE_SKILL, USE_ITEM, RUNAWAY
};

class Combat
{
  Enemy* enemy;

	int allies_alive, enemies_alive;
	int total_reward_gold;

public:
	Combat(Place _place); // 전투 시작
 ~Combat(); // delete enemy, 승리했을 시 보상골드 지급

 void SetEnemy(Place _place); // 장소에 따라 lvl 과 name 설정해서 Enemy 생성, total_reward_gold 할당
 void Action(Character _character); // 턴일 때 행동
 void RunAway(Character _character); // 적과 spd 비교해서 확률 설정 후 도망
};