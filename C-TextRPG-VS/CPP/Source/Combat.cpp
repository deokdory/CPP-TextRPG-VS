#include "Combat.h"
#include "pch.h"

void Combat(GameManager& Game, Hero** Player, Place _place) {
  
  QuestList::NewQuestList(1);

  Inventory::GotItem(1);
  Inventory::GotItem(1);

  int allies_personnel = GetNumOfPlayableHeroes(Player);  // ���� ������ ���� ��
  int enemies_personnel = GetEnemiesPersonnel(_place);  // ������ �� ��
  int total_combat_personnel =
      allies_personnel + enemies_personnel;  // �̹� ������ ��ü ĳ���� ��

  Enemy* enemy[PARTY_MAX] = {};

  int total_reward_gold = 0;
  int total_reward_exp = 0;

  for (int i = 0; i < enemies_personnel; i++) {
    enemy[i] = new Enemy(GetEnemyIndex(_place), GetEnemyLvl(_place));
    total_reward_gold += enemy[i]->GetRewardGold();
    total_reward_exp += enemy[i]->GetRewardExp();
  }

  Character* TurnWaiting[PARTY_MAX * 2];  // �� ���� ������ �迭
  {
    int index = 0;
    for (int i = 0; i < allies_personnel;
         i++) {  // �� ���� ������ �迭�� �÷��̾� ĳ���� �ּ� �Ҵ�
      if (Player[i] != nullptr) {
        TurnWaiting[index] = Player[i];
        TurnWaiting[index]->SetTurnWaiter(0);
        index++;
      }
    }
    for (int i = 0; i < enemies_personnel;
         i++) {  // �� ���� ������ �迭�� �� ĳ���� �ּ� �Ҵ�
      TurnWaiting[index] = enemy[i];
      TurnWaiting[index]->SetTurnWaiter(0);
      index++;
    }
  }
  int allies_alive = 0;
  int enemies_alive = 0;
  bool ranaway = false;
  while (true) {
    allies_alive = enemies_alive = 0;
    for (int i = 0; i < allies_personnel;
         i++) {  // ���� �÷��̾� ĳ���� �� Ȯ��
      if (!(Player[i]->CheckIsDead())) {
        allies_alive++;
      }
    }
    for (int i = 0; i < enemies_personnel; i++) {  // ���� �� ĳ���� �� Ȯ��
      if (!(enemy[i]->CheckIsDead())) {
        enemies_alive++;
      }
    }

    // ��� ������ �������� �� ���� ����
    if (!allies_alive || !enemies_alive) break;
    // ������ �������� �� ���� ����
    if (ranaway) break;

    system("cls");

    gotoy(0);
    for (int i = 0; i < allies_personnel; i++) {
      if (Player[i]->CheckIsDead()) {
        TextColor(DARK_GRAY, BLACK);
      }
      Player[i]->PrintStatus();
      TextColor();
    }
    gotoxy(35, 0);
    for (int i = 0; i < 21; i++) {
      gotox(34);
      std::cout << "||" << std::endl;
    }
    gotoy(0);
    for (int i = 0; i < enemies_personnel; i++) {
      if (enemy[i]->CheckIsDead()) {
        TextColor(DARK_GRAY, BLACK);
      }
      enemy[i]->PrintStatus(40);
      TextColor();
    }
    gotoxy(0, 22);
    {
      int top_spd = 0;
      for (int i = 0; i < total_combat_personnel;
           i++) {  // �ӵ� ������ ���� ���� ĳ���� �˻�
        if (TurnWaiting[i]->GetSpd() > top_spd) {
          top_spd = TurnWaiting[i]->GetSpd();
        }
      }
      for (int i = 0; i < total_combat_personnel;
           i++) {  // ���� ���� �ӵ� ������ �������� �ٸ� ĳ������ �ӵ� ����
                   // ������ �� ���ƿ��� �ӵ� ����
        if (TurnWaiting[i]->CheckIsDead() == false) {
          TurnWaiting[i]->SetTurnSpd((double)(TurnWaiting[i]->GetSpd()) /
                                     top_spd);
        } else {
          TurnWaiting[i]->SetTurnSpd(
              0);  // ĳ���Ͱ� ���� ��� �� ���ƿ��� �ӵ� 0���� ����
        }
        // std::cout << TurnWaiting[i]->GetName()
        //          << " TurnSpd = " << TurnWaiting[i]->GetTurnSpd() <<
        //          std::endl;
      }
    }
    //�� ���
    Character* turn_now = 0;
    Character* turn_next = 0;
    bool turn_waiting = true;
    while (turn_waiting) {
      for (int i = 0; i < total_combat_personnel; i++) {
        if (TurnWaiting[i]->GetTurnWaiter() >= 100) {
          turn_now = TurnWaiting[i];

          int second_turn_waiter = 0;
          for (int i = 0; i < total_combat_personnel; i++) {
            if (TurnWaiting[i] != turn_now &&
                TurnWaiting[i]->GetTurnWaiter() > second_turn_waiter) {
              second_turn_waiter = TurnWaiting[i]->GetTurnWaiter();
              turn_next = TurnWaiting[i];
            }
          }
          turn_waiting = false;
          break;
        } else
          continue;
      }
      if (turn_waiting) {
        for (int i = 0; i < total_combat_personnel; i++) {
          TurnWaiting[i]->AddTurnWaiter(TurnWaiting[i]->GetTurnSpd());
        }
      }
    }

    std::cout << turn_now->GetName() << "�� �ൿ�� �����Դϴ�.";
    std::cout << "   ( ���� ���� : " << turn_next->GetName() << " )"
              << std::endl;
    if (turn_now->GetType() == CharacterType::ENEMY) SYSTEM_MESSAGE_DELAY;

    // �÷��̾� ��
    if (turn_now->GetType() == CharacterType::HERO) {
      Hero* TurnNowHero = dynamic_cast<Hero*>(turn_now);
      //�ൿ ����
      int action = 0;
      std::cout << "1. ����   2. ��ų ���   3. ������ ���   4. ����"
                << std::endl;
      std::cout << "�ൿ�� �������ֽʽÿ� : ";
      std::cin >> action;

      switch (action) {
        case COMBAT_ATTACK: {
          Character* Target = SelectTarget(enemy);
          if (Target != nullptr) {
            turn_now->Attack(*Target);
            TurnNowHero->TurnEnd();
          }
          break;
        }
        case COMBAT_USE_SKILL: {
          int skill_select = 0;
          Skill* UsingSkill = nullptr;
          TurnNowHero->PrintSkillsAll();
          std::cout << "0. ���" << std::endl << std::endl;
          while (true) {
            std::cout << "����� ��ų�� �������ּ��� : ";
            std::cin >> skill_select;

            if (skill_select == 0) break;  // ��ų ��� ���

            if (skill_select >= 1 && skill_select <= 3) {
              if (TurnNowHero->GetSkill(skill_select - 1) != nullptr) {
                if (TurnNowHero->GetSkill(skill_select - 1)->IsAvailable()) {
                  UsingSkill = TurnNowHero->GetSkill(skill_select - 1);
                  break;
                } else {
                  std::cout << "�ش� ��ų�� ���� ����� �� �����ϴ�."
                            << std::endl;
                }
              } else {
                std::cout << "�ش� ��ų ������ ����ֽ��ϴ�." << std::endl;
                SYSTEM_MESSAGE_DELAY;
              }
            } else {
              std::cout << "���� ������ ������ϴ�." << std::endl;
              SYSTEM_MESSAGE_DELAY;
            }
          }

          if (skill_select == 0) break;  // ��ų ��� ���

          switch (UsingSkill->GetSkillType()) {
            case SkillType::ATTACK: {
              Character* Target = SelectTarget(enemy);
              UsingSkill->Use(*Target);
              TurnNowHero->TurnEnd();
              break;
            }
            case SkillType::HEAL: {
              break;
            }
            case SkillType::BUFF: {
              break;
            }
            case SkillType::DEBUFF: {
              break;
            }
            default:
              std::cout << "ERROR : Undefined SkillType in Combat" << std::endl;
              break;
          }
          break;
        }
        case COMBAT_USE_ITEM: {
          Inventory::Open(*TurnNowHero, Player, enemy);
          break;
        }
        case COMBAT_RUNAWAY: {
          ranaway = RunAway(Player, enemy);
          TurnNowHero->TurnEnd();
          break;
        }
      }
    } else {  // �� ����
      int target_score[PARTY_MAX] = {};
      int dealt_damage[PARTY_MAX] = {};
      int max_dealt_damage = 0;
      int received_damage[PARTY_MAX] = {};
      int min_received_damage = 99999;
      int target_hp_remain[PARTY_MAX] = {};
      int min_target_hp_remain = 99999;
      bool attack_will_die[PARTY_MAX] = {};

      for (int i = 0; i < allies_personnel; i++) {
        if (Player[i] != nullptr) {
          if (Player[i]->CheckIsDead()) {
            continue;
          } else {
            dealt_damage[i] = turn_now->GetAtk() - Player[i]->GetDef();
            if (dealt_damage[i] > max_dealt_damage) {
              max_dealt_damage = dealt_damage[i];
            }
            // received_damage[i] = Player[i]->GetAtk() - turn_now->GetAtk();
            // if (received_damage[i] < min_received_damage) {
            //  min_received_damage = received_damage[i];
            //}
            // if (turn_now->GetHp() - received_damage[i] <= 0) {
            //  attack_will_die[i] = true;
            //}
            target_hp_remain[i] = Player[i]->GetHp() - dealt_damage[i];
            if (target_hp_remain[i] < min_target_hp_remain) {
              min_target_hp_remain = target_hp_remain[i];
            }
          }
        }
      }
      for (int i = 0; i < allies_personnel; i++) {
        if (Player[i] != nullptr) {
          if (Player[i]->CheckIsDead()) {
            continue;
          } else {
            if (dealt_damage[i] == max_dealt_damage) {
              target_score[i]++;
            }
            // if (received_damage[i] == min_received_damage) {
            //  target_score[i] += 1;
            //}
            // if (attack_will_die) {
            //  target_score[i] -= 1;
            //}
            if (target_hp_remain[i] = min_target_hp_remain) {
              target_score[i]++;
            }
            if (target_hp_remain[i] <= 0) {
              target_score[i]++;
            }
          }
        }
      }
      Character* Target = nullptr;
      int target_top_score = 0;
      for (int i = 0; i < allies_personnel; i++) {
        if (Player[i] != nullptr) {
          if (Player[i]->CheckIsDead()) {
            continue;
          } else {
            if (target_score[i] >= target_top_score) {
              target_top_score = target_score[i];
              Target = Player[i];
            }
          }
        }
      }
      turn_now->Attack(*Target);
      turn_now->SetTurnWaiter(0);
    }
  }  // ���� �������� ��

  if (allies_alive && !enemies_alive) {  // �¸�
    for (int i = 0; i < allies_personnel; i++) {
      if (Player[i]->CheckIsDead() == false) {
        Player[i]->GiveExp(total_reward_exp);
      }
    }
    Game.AddGold(total_reward_gold);
    std::cout << total_reward_gold << "G �� ȹ���߽��ϴ�" << std::endl;
    SYSTEM_MESSAGE_DELAY;
  } else if (!allies_alive && enemies_alive) {  //�й�
    std::cout << "����� �й��߽��ϴ�..." << std::endl;
    SYSTEM_MESSAGE_DELAY;
  } else {  // ����
  }
  QuestList::Open();
  for (int i = 0; i < enemies_personnel; i++) {
    delete enemy[i];
  }
}

// �� ����
int GetEnemiesPersonnel(Place _place) {
  int enemies_min = 1;
  int enemies_max = 1;
  double percent = 1;

  switch (_place) {
    case Place::FOREST: {
      enemies_min = FOREST_ENEMIES_MIN;
      enemies_max = FOREST_ENEMIES_MAX;
      percent = FOREST_ENEMY_ADD_PERCENTAGE;
      break;
    }
    case Place::CAVE: {
      enemies_min = CAVE_ENEMIES_MIN;
      enemies_max = CAVE_ENEMIES_MAX;
      percent = CAVE_ENEMY_ADD_PERCENTAGE;
      break;
    }
    case Place::MOUNTAIN: {
      enemies_min = MOUNTAIN_ENEMIES_MIN;
      enemies_max = MOUNTAIN_ENEMIES_MAX;
      percent = MOUNTAIN_ENEMY_ADD_PERCENTAGE;
      break;
    }
  }
  int enemies_personnel = enemies_min;
  double random = 0;

  if (enemies_min > enemies_max) {
    std::cout << "ERROR : enemies_min is higher than enemies_max ! so swapped"
              << std::endl;
    std::swap(enemies_min, enemies_max);
  }

  for (int i = 0; i < enemies_max - enemies_min; i++) {
    random = RealRandom();
    if (enemies_personnel >= enemies_max) {
      enemies_personnel = enemies_max;
      break;
    }
    if (random < percent) {
      enemies_personnel++;
    } else {
      continue;
    }
  }
  return enemies_personnel;
}
int GetEnemyLvl(Place _place) {
  int lvl_min = 1;
  int lvl_max = 1;
  int lvl = 1;
  switch (_place) {
    case Place::FOREST: {
      lvl_min = FOREST_ENEMIES_LVL_MIN;
      lvl_max = FOREST_ENEMIES_LVL_MAX;
      break;
    }
    case Place::CAVE: {
      lvl_min = CAVE_ENEMIES_LVL_MIN;
      lvl_max = CAVE_ENEMIES_LVL_MAX;
      break;
    }
    case Place::MOUNTAIN: {
      lvl_min = MOUNTAIN_ENEMIES_LVL_MIN;
      lvl_max = MOUNTAIN_ENEMIES_LVL_MAX;
      break;
    }
  }
  double random = RealRandom();
  double ratio = 1.0;
  if (lvl_min > lvl_max) {
    std::cout << "ERROR : lvl_min is higher than lvl_max ! so swapped"
              << std::endl;
    std::swap(lvl_min, lvl_max);
  }
  int lvl_range = lvl_max - lvl_min + 1;

  ratio /= lvl_range;

  for (int i = 0; i < lvl_range; i++) {
    if (random < ratio * (i + 1)) {
      lvl = lvl_min + i;
      break;
    } else {
      continue;
    }
  }
  return lvl;
}

int GetEnemyIndex(Place _place) {
  int index = 0;
  switch (_place) {
    case Place::FOREST: {
      index = WOLF;
      break;
    }
    case Place::CAVE: {
      index = GOBLIN;
      break;
    }
    case Place::MOUNTAIN: {
      index = DEVILKING;
      break;
    }
  }
  return index;
}

bool RunAway(Hero** player, Enemy** enemy) {
  double player_spd_avg = GetSpdAvgAlive(player);
  double enemies_spd_avg = GetSpdAvgAlive(enemy);

  double runaway_chance = GetRunAwayChance(player_spd_avg, enemies_spd_avg);

  // std::cout << runaway_chance * 100 << std::endl; // ����ĥ Ȯ�� üũ��

  std::cout << "������ �� ������";
  for (int i = 0; i < 4; i++) {
    std::cout << " .";
    Sleep(500);
  }

  if (RealRandom() < runaway_chance) {
    std::cout << "���������� �����ƴ�!" << std::endl;
    SYSTEM_MESSAGE_DELAY;
    return true;
  } else {
    std::cout << "����ġ�� ���ߴ�.." << std::endl;
    SYSTEM_MESSAGE_DELAY;
    return false;
  }
}

double GetSpdAvgAlive(Hero** team) {
  int team_spd_sum = 0;
  int team_alive = 0;
  for (int i = 0; i < PARTY_MAX; i++) {
    if (team[i] != nullptr) {
      if (team[i]->CheckIsDead() == false) {
        team_spd_sum += team[i]->GetSpd();
        team_alive++;
      }
    } else {
      break;
    }
  }
  return (double)team_spd_sum / team_alive;
}

double GetSpdAvgAlive(Enemy** team) {
  int team_spd_sum = 0;
  int team_alive = 0;
  for (int i = 0; i < PARTY_MAX; i++) {
    if (team[i] != nullptr) {
      if (team[i]->CheckIsDead() == false) {
        team_spd_sum += team[i]->GetSpd();
        team_alive++;
      }
    } else {
      break;
    }
  }
  return (double)team_spd_sum / team_alive;
}

double GetRunAwayChance(double player_spd_avg, double enemy_spd_avg) {
  double runaway_chance = 0.0;
  if (player_spd_avg >= enemy_spd_avg) {
    runaway_chance = RUNAWAY_CHANCE_MAX;
  } else if (enemy_spd_avg) {
    runaway_chance = (player_spd_avg / enemy_spd_avg) * RUNAWAY_CHANCE_MAX;
  }
  return runaway_chance;
}