#pragma once
#include "Character.h"
#include "Item.h"
#include "Quest.h"
#include "System.h"
#include "GameManager.h"

#define RUNAWAY_CHANCE_MAX 0.9

//장소 별 적 인원 및 확률

#define FOREST_ENEMIES_MIN 1
#define FOREST_ENEMIES_MAX 2
#define FOREST_ENEMIES_LVL_MIN 1
#define FOREST_ENEMIES_LVL_MAX 2
#define FOREST_ENEMY_ADD_PERCENTAGE 0.5

#define CAVE_ENEMIES_MIN 1
#define CAVE_ENEMIES_MAX 3
#define CAVE_ENEMIES_LVL_MIN 3
#define CAVE_ENEMIES_LVL_MAX 3
#define CAVE_ENEMY_ADD_PERCENTAGE 0.5

#define MOUNTAIN_ENEMIES_MIN 1
#define MOUNTAIN_ENEMIES_MAX 1
#define MOUNTAIN_ENEMIES_LVL_MIN 10
#define MOUNTAIN_ENEMIES_LVL_MAX 10
#define MOUNTAIN_ENEMY_ADD_PERCENTAGE 0.75

enum ActionInCombat { COMBAT_ATTACK = 1, COMBAT_USE_SKILL, COMBAT_USE_ITEM, COMBAT_RUNAWAY };

void Combat(GameManager& Game, Hero** Player, Place _place);  // 전투 시작

//적 세팅
int GetEnemiesPersonnel(Place _place);  // 적 전체 인원 수 계산
int GetEnemyLvl(Place _place);          // 적 레벨 계산
int GetEnemyIndex(Place _place);

bool RunAway(Hero** player, Enemy** enemy);  // 적과 spd 비교해서 확률 설정 후 도망
double GetSpdAvgAlive(Hero** player);
double GetSpdAvgAlive(Enemy** enemy); 
double GetRunAwayChance(double player_spd_avg, double enemy_spd_avg);

