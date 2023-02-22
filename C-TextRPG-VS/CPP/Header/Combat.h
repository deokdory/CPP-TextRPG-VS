#pragma once
#include "Character.h"
#include "Common.h"

enum class Place { FOREST, CAVE, MOUNTAIN };

enum ActionInCombat { ATTACK = 1, USE_SKILL, USE_ITEM, RUNAWAY };

void Combat(Hero** Player, Place _place);  // 전투 시작

int GetEnemiesPersonnel(Place _place);  // 적 전체 인원 수 계산
int GetEnemyLvl(Place _place);          // 적 레벨 계산
std::string GetEnemyName(Place _place);
void Action(Character _character);  // 턴일 때 행동
void RunAway(Character _character);  // 적과 spd 비교해서 확률 설정 후 도망
