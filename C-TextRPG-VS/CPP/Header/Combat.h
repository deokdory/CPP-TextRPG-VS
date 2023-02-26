#pragma once
#include "Character.h"
#include "Item.h"
#include "System.h"
#include "GameManager.h"

enum ActionInCombat { COMBAT_ATTACK = 1, COMBAT_USE_SKILL, COMBAT_USE_ITEM, COMBAT_RUNAWAY };

void Combat(GameManager& Game, Hero** Player, Place _place);  // 전투 시작

//적 세팅
int GetEnemiesPersonnel(Place _place);  // 적 전체 인원 수 계산
int GetEnemyLvl(Place _place);          // 적 레벨 계산
int GetEnemyIndex(Place _place);

void RunAway(Character& _character);  // 적과 spd 비교해서 확률 설정 후 도망