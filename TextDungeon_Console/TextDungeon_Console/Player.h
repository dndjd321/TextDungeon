#pragma once
#include <string>
#include "Item.h"

class Player {
private:
    std::string name;
    int hp, maxHp, attack, defense, spd, gold;
	int level = 1;
    int exp = 0;
	int maxExp = 100;   // 다음 레벨업까지 필요한 경험치
	int statPoints = 0; // 레벨업 시 획득하는 스탯 포인트
    Item* equippedItem;

public:
    Player(std::string n, int h, int a, int d, int s);

    // 전투 및 보상 관련
    void takeDamage(int damage);
    void gainGold(int amount) { gold += amount; }
    void loseGold(int amount) { gold -= amount; }
    void rest();
    void showStatus();

    // 경험치 획득 및 레벨업 체크
	void gainExp(int amount);
	void levelUp();

    // 스탯 포인트 투자 함수
	void useStatPoint(int choice);

    // 최종 스탯 계산 (기본 스탯 + 아이템 보너스)
    int getTotalAtk();
    int getTotalDef();
    int getTotalSpd();
    int getTotalMaxHp();

    // 데이터 확인용 Getter
    int getHp() { return hp; }
    int getGold() { return gold; }
	int getLevel() { return level; }
	int getExp() { return exp; }
	int getMaxExp() { return maxExp; }
	int getStatPoints() { return statPoints; }

    std::string getName() { return name; }

    // 아이템 관련
    void setEquippedItem(Item* item) { equippedItem = item; }
    Item* getEquippedItem() { return equippedItem; }
};


//#pragma once // 중복 포함 방지
//
//#include "Item.h"
//#include <string>
//
//class Player {
//private: // 외부에서 직접 수정 못하게 보호 (캡슐화)
//    std::string name;
//    int hp;
//    int maxHp;
//    int attack;
//	int defense;
//    int spd;
//    int gold;
//
//private:
//	Item* equippedItem; // 현재 장착 중인 아이템 포인터
//
//public:
//	Player(std::string n, int h, int a, int d, int s) : equippedItem(nullptr) {}; // 생성자
//
//    // 행동 함수
//	void takeDamage(int damage);								// 데미지 받기
//	void gainGold(int amount);									// 골드 획득
//	void rest(int amount);										// 휴식하여 HP 회복 
//	void addAtk(int amount);									// 공격력 증가
//	void addDef(int amount);									// 방어력 증가
//	void addSpd(int amount);									// 속도 증가
//	void addMaxHp(int amount);									// 최대 체력 증가
//	void loseGold(int amount) { gold -= amount; }				// 골드 감소
//	void useItem(const Item& item);								// 아이템 사용 
//	void applyStatChange(StatType stat, int value);				// 능력치 변화 적용
//	
//	void setEquippedItem(Item* item) { equippedItem = item; }	// 장착 아이템 설정
//	Item* getEquippedItem() { return equippedItem; }			// 장착 아이템 반환
//
//    // 상태 확인용 Getter (출력용)
//    void showStatus();
//	int getAtk() { return attack; } // 공격력 반환
//	int getSpd() { return spd; }    // 속도 반환
//	int getHp() { return hp; }      // 현재 체력 반환
//	int getGold() { return gold; }  // 현재 골드 반환
//	int getTotalAtk() {				// 총 공격력 반환 (장착 아이템 포함)
//		if (equippedItem && equippedItem->getUpStat() == StatType::ATTACK) {
//			return attack + equippedItem->getBoostedValue();
//		}
//		return attack;
//	};
//};