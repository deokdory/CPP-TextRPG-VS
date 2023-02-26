#pragma once
#include "Quest.h"

enum class Place { TOWN, WORLD_MAP, FOREST, CAVE, MOUNTAIN };

class GameManager {
  int gold;
  
 public:
  int GetGold();
  void SetGold(int _gold);
  void AddGold(int _gold);
};