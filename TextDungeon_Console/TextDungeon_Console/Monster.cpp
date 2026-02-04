#include "Monster.h"
#include <iostream>
#include <algorithm>

// 생성자 구현 (spd 추가됨)
Monster::Monster(std::string n, int h, int a, int d, int s, int minG, int maxG, int exp)
    : name(n), hp(h), attack(a), defense(d), spd(s), minGold(minG), maxGold(maxG), expReward(exp) {
}

void Monster::takeDamage(int damage) {
    // 1. 방어율 계산 ( ex. DEF == 100일 때, DMG 50% 감소 기준 )
	double reduction = 100.0 / (100.0 + defense);

    // 2. 기본 데미지 계산
	double baseDamage = damage * reduction;

    // 3. 크리티컬 판정 
	bool isCritical = (rand() % 100) < 10; // 10% 확률
    double randFactor;

    if (isCritical) {
        // 크리티컬 발생
        randFactor = (rand() % 51 + 150) / 100.0; // 1.5 ~ 2.0
    }
    else {
        // 일반 공격
        randFactor = (rand() % 41 + 80) / 100.0; // 0.8 ~ 1.2
    }
	
    int finalDamage = (int)(baseDamage * randFactor);

	// 5. 최소 데미지 1 보장
	if (finalDamage < 1) finalDamage = 1;

    //int actualDamage = std::max(1, damage - defense);
    hp -= finalDamage;
    if (hp < 0) hp = 0;

    std::cout << name << "에게 " << finalDamage << "의 피해를 입혔습니다! ";
	if (isCritical) std::cout << "[크리티컬!]";
    std::cout << "(남은 HP: " << hp << ")" << std::endl;
}