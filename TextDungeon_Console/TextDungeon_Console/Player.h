#pragma once // 중복 포함 방지

#include "Item.h"
#include <string>

class Player {
private: // 외부에서 직접 수정 못하게 보호 (캡슐화)
    std::string name;
    int hp;
    int maxHp;
    int attack;
	int defense;
    int spd;
    int gold;

public:
    Player(std::string n, int h, int a, int d, int s); // 생성자

    // 행동 함수
	void takeDamage(int damage);					// 데미지 받기
	void gainGold(int amount);						// 골드 획득
	void rest(int amount);							// 휴식하여 HP 회복 
	void addAtk(int amount);						// 공격력 증가
	void addDef(int amount);						// 방어력 증가
	void addSpd(int amount);						// 속도 증가
	void addMaxHp(int amount);						// 최대 체력 증가
	void loseGold(int amount) { gold -= amount; }	// 골드 감소
	void useItem(const Item& item);					// 아이템 사용 
	void applyStatChange(StatType stat, int value); // 능력치 변화 적용

    // 상태 확인용 Getter (출력용)
    void showStatus();
	int getAtk() { return attack; } // 공격력 반환
	int getSpd() { return spd; }    // 속도 반환
	int getHp() { return hp; }      // 현재 체력 반환
	int getGold() { return gold; }  // 현재 골드 반환
};