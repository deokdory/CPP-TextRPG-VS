#include "Combat.h"

#include "pch.h"

void Combat(GameManager& Game, Hero** Player, Place _place) {
  int allies_personnel = GetNumOfPlayableHeroes(Player);  // ���� ������ ���� ��
  int enemies_personnel = GetEnemiesPersonnel(_place);  // ������ �� ��
  int total_combat_personnel =
      allies_personnel + enemies_personnel;  // �̹� ������ ��ü ĳ���� ��

  Enemy* enemy[PARTY_MAX] = {};

  int total_reward_gold = 0;
  int total_reward_exp = 0;

  for (int i = 0; i < enemies_personnel; i++) {
    if (i == 0 && _place == Place::MOUNTAIN) {
      enemy[i] = new Enemy(DEVILKING, 6);
    } else {
      enemy[i] = new Enemy(GetEnemyIndex(_place), GetEnemyLvl(_place));
    }
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

  Character* prev_turn = nullptr;

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
          // ĳ���Ͱ� ���� ��� �� ���ƿ��� �ӵ� �� �� ����� 0���� ����
          TurnWaiting[i]->SetTurnSpd(0);
          TurnWaiting[i]->SetTurnWaiter(0);
        }
        // std::cout << TurnWaiting[i]->GetName()
        //          << " TurnSpd = " << TurnWaiting[i]->GetTurnSpd() <<
        //          std::endl;
      }
    }
    //�� ���
    Character* turn_now = nullptr;

    bool turn_waiting = true;
    int turn_score[PARTY_MAX * 2] = {};
    int turn_now_count = 0;

    int turn_now_index = 0;  // �� ��ȣ �ٿ��ֱ� ����

    while (true) {
      for (int i = 0; i < total_combat_personnel; i++) {
        if (TurnWaiting[i]->IsTurn()) {
          turn_score[i]++;
          turn_now_count++;
        }
      }
      // ���� ���ƿ� ĳ���Ͱ� �ϳ���� �ش� ĳ������ ��

      if (turn_now_count > 1) {
        int top_score = 0;
        for (int i = 0; i < total_combat_personnel; i++) {
          if (turn_score[i] || turn_score[i] > top_score) {
            turn_now = TurnWaiting[i];
            top_score = turn_score[i];
            turn_now_index = i;
          }
        }
        break;

        // ���� ���ƿ� ĳ���Ͱ� ���ٸ�
      } else {
        for (int i = 0; i < total_combat_personnel; i++) {
          TurnWaiting[i]->AddTurnWaiter(TurnWaiting[i]->GetTurnSpd());
        }
      }
    }
    Clear;
    CombatPrintStatus(Player, enemy, allies_personnel, enemies_personnel);

    std::cout << (turn_now_index % 3) + 1 << ". " << turn_now->GetName()
              << "��(��) �ൿ�� �����Դϴ�." << std::endl;

    if (prev_turn != turn_now) {
      // �� ���� �� ó���� ���׵�
      // ���� ���̶�� ī��Ʈ--
      if (Hider* hider = Hider::FindIsHiding(turn_now)) {
        hider->DecreaseCount();
      }

      // ���� �������� ��ȣ ���̶�� ����
      if (Protector* protector = Protector::FindIsProtecting(turn_now)) {
        protector->Remove();
      }
      // �ߵ��ƴٸ� HP ���� �� ī��Ʈ--
      if (Poisoned* poisoned = Poisoned::FindIsPoisoned(turn_now)) {
        poisoned->PoisonDamage();
        // CombatPrintStatus(Player, enemy, allies_personnel,
        // enemies_personnel);
      }
      prev_turn = turn_now;
      continue;
    }

    //  system("cls");
    //
    //  CombatPrintStatus(Player, enemy, allies_personnel, enemies_personnel);

    // �÷��̾� ��
    if (turn_now->GetType() == CharacterType::HERO) {
      ClearFromY(23, 6);
      gotoy(23);
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
            if (Protector* protector = Protector::FindIsProtected(Target)) {
              Target = protector->GetProtector();
              protector->DecreaseCount();
            }
            turn_now->Attack(Target);
            TurnNowHero->TurnEnd();
          }
          break;
        }
        case COMBAT_USE_SKILL: {
          Skill* UsingSkill = SkillSelect(TurnNowHero);

          if (UsingSkill == nullptr) break;  // ��ų ��� ���

          switch (UsingSkill->GetSkillType()) {
            case SkillType::ATTACK: {
              Character* Target = SelectTarget(enemy);
              if (Target == nullptr) {
                break;
              }
              UsingSkill->Use(*Target);
              TurnNowHero->TurnEnd();
              break;
            }
            case SkillType::HEAL: {
              break;
            }
            case SkillType::BUFF: {
              UsingSkill->Use(*turn_now);
              TurnNowHero->TurnEnd();
              break;
            }
            case SkillType::DEBUFF: {
              break;
            }
            case SkillType::PROTECT: {
              Character* Target = SelectTarget(Player);
              if (Target == nullptr) {
                break;
              } else if (Target == turn_now) {
                std::cout << "�ڽ��� ��ȣ�� ���� �����ϴ�." << std::endl;
                SYSTEM_MESSAGE_DELAY;
                break;
              }
              UsingSkill->Use(*Target);
              TurnNowHero->TurnEnd();
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
      SYSTEM_MESSAGE_DELAY;

      if (!turn_now->CheckIsDead()) {
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
            if (Player[i]->CheckIsDead() || Hider::FindIsHiding(Player[i])) {
              continue;
            } else {
              dealt_damage[i] = turn_now->GetAtk() - Player[i]->GetDef();
              if (dealt_damage[i] > max_dealt_damage) {
                max_dealt_damage = dealt_damage[i];
              }
              received_damage[i] = Player[i]->GetAtk() - turn_now->GetAtk();
              if (received_damage[i] < min_received_damage) {
                min_received_damage = received_damage[i];
              }
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
            if (Player[i]->CheckIsDead() || Hider::FindIsHiding(Player[i])) {
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
              if (target_hp_remain[i] == min_target_hp_remain) {
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
              if (target_score[i] > target_top_score) {
                target_top_score = target_score[i];
                Target = Player[i];
              }
            }
          }
        }

        if (!Target) {
          std::cout << "������ �� �ִ� ����� ���� ���� �ѱ�ϴ�." << std::endl;
          SYSTEM_MESSAGE_DELAY;
        } else {
          turn_now->Attack(Target);
        }
        turn_now->SetTurnWaiter(0);
      }
    }
  }

  // ���� �������� ��
  Clear;
  CombatPrintStatus(Player, enemy, allies_personnel, enemies_personnel);

  for (int i = 0; i < allies_alive; i++) {  // ��Ÿ�� �ʱ�ȭ
    for (int j = 0; j < HERO_SKILL_MAX; j++) {
      if (Player[i]->GetSkill(j)) Player[i]->GetSkill(j)->SetCoolDownRemain(0);
    }
  }

  Protector::RemoveAll();  // ��� ��ȣ ����
  Poisoner::RemoveAll();   // ��� �� ������ ����
  Poisoned::RemoveAll();   // ��� �� ���� ����
  Hider::RemoveAll();      // ��� ���� ���� ����

  if (allies_alive && !enemies_alive) {  // �¸�
    std::cout << "����ġ�� " << total_reward_exp
              << "��ŭ ����ϴ�. ( ������ ���� ���� )" << std::endl;
    for (int i = 0; i < allies_personnel; i++) {
      if (Player[i]->CheckIsDead() == false) {
        Player[i]->GiveExp(total_reward_exp);
      }
    }
    if (_place == Place::MOUNTAIN) {
      std::cout << "������ �����ư� ������ ��ȭ�ο�����." << std::endl;
      SYSTEM_MESSAGE_DELAY;
      std::cout << "�غ�� ������ ��������Դϴ�. �����մϴ�. :)" << std::endl;
      GameManager::SetGameEnded(true);
      return;
    }

    Game.AddGold(total_reward_gold);
    std::cout << total_reward_gold << "G �� ȹ���߽��ϴ�" << std::endl;
    SYSTEM_MESSAGE_DELAY;
  } else if (!allies_alive && enemies_alive) {  //�й�
    std::cout << "��� ������ ���������ϴ�.." << std::endl;
    GameManager::SetGameEnded(true);
    SYSTEM_MESSAGE_DELAY;
  } else {  // ����
  }
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
  int lvl_range = lvl_max - lvl_min;

  ratio /= (lvl_range + 1);

  lvl = lvl_min;

  for (int i = 0; i < lvl_range; i++) {
    if (random >= ratio * (i + 1)) {
      lvl++;
    } else
      break;
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
      index = DEVIL;
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