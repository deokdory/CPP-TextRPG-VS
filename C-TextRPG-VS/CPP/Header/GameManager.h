#pragma once
#include "Quest.h"
#include "Item.h"

enum class Place { TOWN, WORLD_MAP, FOREST, CAVE, MOUNTAIN };

class GameManager {
  int gold;
  int top_lvl_of_player;

  Quest* ProgressQuest;
  
 public:
  int GetGold();
  void SetGold(int _gold);
  void AddGold(int _gold);

  
};