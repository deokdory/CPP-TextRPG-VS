#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>

#undef random
#define random() ((double)rand()/RAND_MAX)
#define CLASS_TOTAL 4

#define SYSTEM_MESSAGE_DELAY 1500

#define ENEMY_TYPE_FOREST 1
#define ENEMY_TYPE_CAVE 2
#define ENEMY_TYPE_DESSERT 2
#define ENEMY_TYPE_MOUNTAIN 1
#define ENEMY_TYPE_TOTAL 6

#define HEALTH_BAR_LENGTH 15
#define COMBAT_INFO_ROW 4

#define CHARACTER_LVL_MAX 10
#define NAME_LIMIT 16
#define PARTY_MAX 4 // 파티 최대 인원 (아군, 적군 공통)

enum CHARACTER_CLASS {
	WARRIOR,
	ARCHOR,
	THIEF,
	COMMON
};
enum CHARACTER_TYPE {
	HERO,
	ENEMY,
};
enum ENEMY_TYPE {
	WOLF,
	GOBLIN,
	TROLL,
	SCORPION,
	MUMMY,
	DEMON_KING
};
enum ITEM_TYPE {
	CONSUMABLE,
	WEAPON,
	HEAD,
	ARMOR,
	SHOES,
	NONE
};
enum ACTION_IN_COMBAT {
	ATTACK = 1,
	USE_SKILL,
	USE_ITEM,
	RUNAWAY
};
enum QUEST_STATUS {
	WAITING,
	IN_PROGRESS,
	COMPLETED,
	FAILED
};
enum PLACE {
	FOREST,
	VILLAGE,
	CAVE,
	DESSERT,
	MOUNTAIN,
	ETC
};
enum COMBAT_INFO {
	NAME_AND_LEVEL,
	CLASS_AND_HEALTH,
	HEALTH_BAR,
	STAT
};

typedef struct {
	char* name;
	int cooldown;
	int duration;
	float atkIncrease;
	float defIncrease;
	int hpIncrease;
	int maxHpIncrease;
	int spdIncrease;
} Skill;
typedef struct {
	int type; //ITEM_TYPE
	char* name;
	int hp;
	int mp;
	int atk;
	int def;
	int spd;
	int price;
} Item;
typedef struct {
	char* name;
	int class; // CHARACTER_CLASS
	int type; // CHARACTER_TYPE
	int hp;
	int maxHp;
	int atk;
	int def;
	int spd;
	float exp;
	int lvl;
	Item iWeapon;
	Item iHead;
	Item iArmor;
	Item iShoes;
	bool isAlive;
	int gold;
} Character;
typedef struct {
	char* name;
	Character* ObjEnemy; // 목표 적 유닛
	Item ObjItem; // 목표 아이템
	int status; //QUEST_STATUS
	Item* rewardItem;
} Quest;

void Initialize();

void Compareint(int*, int*); //

//캐릭터 관련 함수
void SetHero(Character*, int class, int lvl);
void InitCharacter(Character* Who, int class, int lvl);

//전투 관련 함수
//적 생성 함수
int HowManyEnemies(int PLACE);
int SetEnemyLvl(int PLACE);
int SetEnemyType(int PLACE);
void SetEnemies(int PLACE, Character* Enemy, int enemiesAlive);

//전투 정보 표시 함수
void PrintClass(int class);
void PrintHealth(Character* Who);
void PrintHealthBar(Character* Who);
void CombatPrintCharacters(Character* Ally, Character* Enemy);

//전투모드
void Combat(int PLACE);

//턴 행동
void CommonAttack(Character* Attacker, Character* Defender);

int alliesAlive;
int enemiesAlive;
int gold;

Character StatOrigin[CLASS_TOTAL];
Character StatPerLvl[CLASS_TOTAL];
Character Hero[PARTY_MAX];
Character Enemy[PARTY_MAX];
Character EnemyType[ENEMY_TYPE_TOTAL];

Item None = { NONE, "NONE", 0, 0, 0, 0, 0, 0 };

int main() {
	Initialize();
	SetHero(&Hero[0], ARCHOR, 3);
	SetHero(&Hero[1], WARRIOR, 3);
	SetHero(&Hero[2], THIEF, 3);
	SetHero(&Hero[3], COMMON, 3);

	printf("1.숲 2.동굴 3.사막 4.산\n");
	printf("전투를 진행합니다. 장소는? : ");

	int place;
	scanf_s("%d", &place);
	switch (place) {
	case 1:
		Combat(FOREST);
		break;
	case 2:
		Combat(CAVE);
		break;
	case 3:
		Combat(DESSERT);
		break;
	case 4:
		Combat(MOUNTAIN);
		break;
	}
	
	system("pause");
}

void Initialize() {
	srand((unsigned)time(NULL)); // 난수 seed 생성

	{ //클래스별 기본스탯 초기화
		{ //WARRIOR 기본스탯
			StatOrigin[WARRIOR].class = WARRIOR;
			StatOrigin[WARRIOR].maxHp = 60;
			StatOrigin[WARRIOR].atk = 25;
			StatOrigin[WARRIOR].def = 15;
			StatOrigin[WARRIOR].spd = 12;
		}
		{ //ARCHOR 기본스탯
			StatOrigin[ARCHOR].class = ARCHOR;
			StatOrigin[ARCHOR].maxHp = 45;
			StatOrigin[ARCHOR].atk = 30;
			StatOrigin[ARCHOR].def = 10;
			StatOrigin[ARCHOR].spd = 15;
		}
		{ //THIEF 기본스탯
			StatOrigin[THIEF].class = THIEF;
			StatOrigin[THIEF].maxHp = 50;
			StatOrigin[THIEF].atk = 30;
			StatOrigin[THIEF].def = 15;
			StatOrigin[THIEF].spd = 18;
		}
		{//COMMON 기본스탯
			StatOrigin[COMMON].class = COMMON;
			StatOrigin[COMMON].maxHp = 55;
			StatOrigin[COMMON].atk = 30;
			StatOrigin[COMMON].def = 10;
			StatOrigin[COMMON].spd = 15;
		}
	}
	{ //클래스별 레벨 당 스탯 증가 수치 설정
		{ //WARRIOR 레벨 당 스탯 증가 수치
			StatPerLvl[WARRIOR].maxHp = 30;
			StatPerLvl[WARRIOR].atk = 10;
			StatPerLvl[WARRIOR].def = 15;
			StatPerLvl[WARRIOR].spd = 10;
		}
		{ //ARCHOR 레벨 당 스탯 증가 수치
			StatPerLvl[ARCHOR].maxHp = 20;
			StatPerLvl[ARCHOR].atk = 15;
			StatPerLvl[ARCHOR].def = 10;
			StatPerLvl[ARCHOR].spd = 10;
		}
		{ //THIEF 레벨 당 스탯 증가 수치
			StatPerLvl[THIEF].maxHp = 25;
			StatPerLvl[THIEF].atk = 10;
			StatPerLvl[THIEF].def = 10;
			StatPerLvl[THIEF].spd = 13;
		}
		{ //COMMON 레벨 당 스탯 증가 수치
			StatPerLvl[COMMON].maxHp = 25;
			StatPerLvl[COMMON].atk = 12;
			StatPerLvl[COMMON].def = 12;
			StatPerLvl[COMMON].spd = 10;
		}
	}
	{ //적 데이터 초기화
		{ //숲에 사는 적들
			EnemyType[WOLF].name = "WOLF";
			EnemyType[WOLF].class = COMMON;
		}
		{ //동굴에 사는 적들
			EnemyType[GOBLIN].name = "GOBLIN";
			EnemyType[GOBLIN].class = COMMON;

			EnemyType[TROLL].name = "TROLL";
			EnemyType[TROLL].class = COMMON;
		}
		{ //사막에 사는 적들
			EnemyType[SCORPION].name = "SCORPION";
			EnemyType[SCORPION].class = THIEF;

			EnemyType[MUMMY].name = "MUMMY";
			EnemyType[MUMMY].class = WARRIOR;
		}
		{ //산에 사는 적들(마왕)
			EnemyType[DEMON_KING].name = "DEMON KING";
			EnemyType[DEMON_KING].class = COMMON;
		}
	}
}

void delay(clock_t n) {
	clock_t start = clock();
	while (clock() - start < n);
}

void Compareint(int* a, int* b) {
	if (*a > *b) {
		int temp = *a;
		*a = *b;
		*b = temp;
	}
}
void InitCharacter(Character* Who, int class, int lvl) {
	float adjust = 1.0;
	if (Who->type == ENEMY) {
		adjust = 0.9;
	}
	Who->class = class; // CLASS_TYPE
	Who->maxHp = (StatOrigin[class].maxHp + (StatPerLvl[class].maxHp * lvl)) * adjust;
	Who->atk = (StatOrigin[class].atk + (StatPerLvl[class].atk * lvl)) * adjust;
	Who->def = (StatOrigin[class].def + (StatPerLvl[class].def * lvl)) * adjust;
	Who->spd = (StatOrigin[class].spd + (StatPerLvl[class].spd * lvl)) * adjust;
	Who->hp = Who->maxHp;

	Who->iWeapon = None;  Who->iHead = None;  Who->iArmor = None;  Who->iShoes = None;
	Who->exp = 0; Who->lvl = lvl; Who->gold = 0;  Who->isAlive = true;
}

void SetHero(Character* Hero, int class, int lvl) {
	Hero->name = &"HERO";
	InitCharacter(Hero, class, lvl);
	Hero->type = HERO;
}


int HowManyEnemies(int PLACE) {
	double random = 0.0f;
	double percent = 1.0f;
	int enemiesMin = 0;
	int enemiesMax = 0;

	switch (PLACE) {
	case FOREST: {
		percent = 0.5;
		enemiesMin = 1;
		enemiesMax = 2;
	} break;
	case CAVE: {
		percent = 0.5;
		enemiesMin = 2;
		enemiesMax = 4;
	} break;
	case DESSERT: {
		percent = 0.75;
		enemiesMin = 2;
		enemiesMax = 4;
	} break;
	}
	int enemiesAlive = enemiesMin;
	for (int i = 0; i < enemiesMax - enemiesMin; i++) {
		random = random(); // 추후 Real Random 함수를 작성 후 교체
		if (enemiesAlive >= enemiesMax) {
			enemiesAlive = enemiesMax; break;
		} if (random < percent) {
			enemiesAlive++;
			percent /= 2;
		}
		else {
			continue;
		}
	}return enemiesAlive;
}
int SetEnemyLvl(int PLACE) {
	\
		int lvl = 0;

	double random = 0.0f;
	double percent = 1.0f;

	int lvlMin = 1;
	int lvlMax = 1;
	switch (PLACE) {
	case FOREST: {
		lvlMin = 1;
		lvlMax = 1;
		break;
	}
	case CAVE: {
		lvlMin = 2;
		lvlMax = 3;
		break;
	}
	case DESSERT: {
		lvlMin = 3;
		lvlMax = 4;
		break;
	}
	case MOUNTAIN: {
		lvlMin = 5;
		lvlMax = 5;
		break;
	}
	}
	Compareint(&lvlMin, &lvlMax);

	int lvlRange = lvlMax - lvlMin + 1;

	percent = 1.0 / lvlRange;
	for (int i = 0; i < lvlRange; i++) {
		random = random(); // 추후 Real Random 함수 작성 후 교체
		if (random < percent * (i + 1)) {
			lvl = lvlMin + i;
			break;
		}
		else {
			continue;
		}
	} return lvl;
}

int SetEnemyType(int PLACE) { // 임시
	int type = 0;
	double random = 0.0f;
	switch (PLACE) {
	case FOREST:
		type = WOLF; break;
	case CAVE:
	{
		if (rand() % 2) type = GOBLIN;
		else type = TROLL;
		break;
	}
	case DESSERT:
	{
		if (rand() % 2) type = SCORPION;
		else type = MUMMY;
		break;
	}
	case MOUNTAIN:
		type = DEMON_KING; break;
	}
	return type;
}

void SetEnemies(int PLACE, Character* Enemy, int enemiesAlive) {
	int lvl = 0;
	int class = 0;
	int type = 0;
	for (int i = 0; i < enemiesAlive; i++) {
		lvl = SetEnemyLvl(PLACE);
		type = SetEnemyType(PLACE);

		Enemy[i].name = EnemyType[type].name;
		class = EnemyType[type].class;
		Enemy[i].type = ENEMY;

		InitCharacter(&Enemy[i], class, lvl);

		Enemy[i].exp = lvl * 15;
		Enemy[i].gold = lvl * 30 * (random() + 0.5);
	}
}

void PrintClass(int class) {
	switch (class) {
	case WARRIOR: printf("WARRIOR"); break;
	case ARCHOR: printf("ARCHOR"); break;
	case THIEF: printf("THIEF"); break;
	case COMMON: printf("COMMON"); break;
	}
}

void PrintHealth(Character* Who) {
	int maxHp = Who->maxHp;
	int hp = Who->hp;

	float hpRemain = 0;
	if (maxHp != 0) {
		hpRemain = ((float)hp / maxHp) * 100;
	}
	else {
		printf("maxHp == 0!!");
	}hpRemain = ((float)hp / maxHp) * 100;
	printf("    HP : %d / %d (%.00f%%)", Who->hp, Who->maxHp, hpRemain);
}

void PrintHealthBar(Character* Who) {
	int maxHp = Who->maxHp;
	int hp = Who->hp;

	float hpRemain = ((float)hp / maxHp) * 100;
	float hpPerBox = 0;

	if (HEALTH_BAR_LENGTH) {
		hpPerBox = 100 / HEALTH_BAR_LENGTH;
	}
	else {
		printf("HEALTH_BAR_LENGTH = 0!!");
	}
	for (int i = 1; i <= HEALTH_BAR_LENGTH; i++) {

		if ((int)hpRemain > hpPerBox * i) {
			printf("■");
		}
		else {
			printf("□");
		}
	}
}

void CombatPrintCharacters(Character* Ally, Character* Enemy) {
	Character* Team = Ally;

	int room = 0;
	for (int row = 0; row < COMBAT_INFO_ROW; row++) {
		for (int team = 0; team < 2; team++) {
			if (Team->isAlive == 0) {
				printf(" ");
			}
			else if (Team != NULL) {
				switch (row) {
				case NAME_AND_LEVEL:
					printf("%s  ", Team->name);
					printf("Lvl %d", Team->lvl);
					room = HEALTH_BAR_LENGTH / 2 - strlen(Team->name);
					printf("               ");
					break;
				case CLASS_AND_HEALTH:
					PrintClass(Team->class);
					PrintHealth(Team);
					break;
				case HEALTH_BAR:
					PrintHealthBar(Team);
					break;
				case STAT:
					printf("ATK : %d | DEF : %d | SPD : %d", Team->atk, Team->def, Team->spd);
					break;
				}
			}
			switch (team) {
			case HERO: {
				Team = Enemy;
				printf("                        ");
				break;
			} case ENEMY: {
				Team = Ally;
				printf("\n");
				break;
			}
			}
		}
	}
}

void Combat(int PLACE) {
	alliesAlive = 0;
	//Character Ally[4];
	for (int i = 0; i < PARTY_MAX; i++) { // Ally 생성 후 전투용 캐릭터 생성
	//	memcpy(&Ally[i], &Hero[i], sizeof(Character));
		switch (Hero[i].isAlive) {
		case true: {
			alliesAlive++;
		} case false: {
			continue;
		}
		}
	}
	int enemies = enemiesAlive = HowManyEnemies(PLACE);
	//    Character* Enemy = (Character*)calloc(enemiesAlive, sizeof(Character));
	SetEnemies(PLACE, Enemy, enemiesAlive);

	int turn = HERO; // 무조건 플레이어 선공
	int target = 0; // 공격대상

	while (true) {
		alliesAlive = 0;
		enemiesAlive = 0;
		for (int i = 0; i < PARTY_MAX; i++) {
			if (Hero[i].isAlive) alliesAlive++;
			if (Enemy[i].isAlive) enemiesAlive++;
		}
		
		if (enemiesAlive <= 0 || alliesAlive <= 0) {  // 양쪽 중 한 쪽이라도 전멸 시 전투 종료
			break;
		}
		else {
			system("cls");
			for (int i = 0; i < PARTY_MAX; i++) {
				CombatPrintCharacters(&Hero[i], &Enemy[i]);
				printf("\n");
			}

			for (int i = 0; i < PARTY_MAX; i++) {
				switch (Hero[i].spd) {

				}
			}

			Character* Attacker = &Hero[0];
			Character* Defender;

			if (turn == HERO) {
				printf("============================================\n");
				printf("1.공격   2. 스킬사용   3.아이템사용   4.도망\n");
				printf("============================================\n");
				printf("행동을 선택해주세요 : ");
				int action;
				scanf_s("%d", &action);
				rewind(stdin);

				switch (action) {
				case ATTACK:
					printf("============================================\n");
					for (int i = 0; i < enemies; i++) {
						if (Enemy[i].isAlive) {
							printf("%d.%s   ", i + 1, Enemy[i].name);
						}
					}
					printf("\n============================================\n");
					printf("대상을 선택해주세요 : ");
					scanf_s("%d", &target);
					rewind(stdin);
					CommonAttack(Attacker, &Enemy[target - 1]);
					break;

				case USE_SKILL:
					printf("개발중...");
					break;

				case USE_ITEM:
					printf("개발중...");
					break;

				case RUNAWAY:
					printf("개발중...");
					break;
				}
			}
			else {

			}

			if (turn == HERO) {
				turn = ENEMY;
			}
			else {
				turn = HERO;
			}
		}
	}

	if (enemiesAlive == 0) {
		int sumExp = 0; int sumGold = 0;
		for (int i = 0; i < enemies; i++) {
			sumExp += Enemy[i].exp;
			sumGold += Enemy[i].gold;
		}
		printf("============================================\n");
		for (int i = 0; i < PARTY_MAX; i++) {
			switch (Hero[i].isAlive) {
			case true:
				Hero[i].exp += sumExp;
				printf("%s 의 경험치가 %d 올랐다!\n", Hero[i].name, sumExp);
				delay(SYSTEM_MESSAGE_DELAY);
			case false: continue;
			}
		}
		gold += sumGold;
		printf("%dG를 획득했다. ( 현재 골드 : %d )\n", sumGold, gold);
		delay(SYSTEM_MESSAGE_DELAY);
		printf("============================================\n");

	}
}
void CommonAttack(Character* Attacker, Character* Defender) {
	int damage = 0;
	printf("%s 가 %s를 공격", Attacker->name, Defender->name);
	for (int i = 0; i < 3; i++) {
		printf(" .");
		delay(500);
	}
	if (Attacker->atk > Defender->def) {
		damage = Attacker->atk - Defender->def;
	}
	else {
		damage = 0;
	}

	Defender->hp -= damage; // 공격
	printf("%d 만큼의 피해를 입혔다!\n", damage);
	delay(SYSTEM_MESSAGE_DELAY);
	if (Defender->hp <= 0) {
		Defender->hp = 0;
		Defender->isAlive = 0;
		printf("%s 는 쓰러졌다!\n", Defender->name);
		delay(SYSTEM_MESSAGE_DELAY);
	}
	else {
		printf("%s 의 반격", Defender->name);
		for (int i = 0; i < 3; i++) {
			printf(" .");
			delay(500);
		}
		if (Defender->atk > Attacker->def) {
			damage = Defender->atk - Attacker->def;
		}
		else {
			damage = 0;
		}
		if (damage < 0) {
			damage = 0;
		}

		Attacker->hp -= damage; // 반격
		printf("%d 만큼의 피해를 입혔다!\n", damage);
		delay(SYSTEM_MESSAGE_DELAY);

		if (Attacker->hp <= 0) {
			Attacker->hp = 0;
			printf("%s 는 쓰러졌다!\n", Attacker->name);
			Attacker->isAlive = 0;
			delay(SYSTEM_MESSAGE_DELAY);
		}
	}
}