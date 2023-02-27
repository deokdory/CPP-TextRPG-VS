#pragma once

enum class Place { TOWN, WORLD_MAP, FOREST, CAVE, MOUNTAIN };

class GameManager {
  static int gold;
  
 public:
  static const int GetGold();
  static void SetGold(int _gold);
  static void AddGold(int _gold);
};

