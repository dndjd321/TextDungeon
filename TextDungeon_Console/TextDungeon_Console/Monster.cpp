#include "Monster.h"
#include <iostream>
#include <algorithm>

// 생성자 구현 (spd 추가됨)
Monster::Monster(std::string n, int h, int a, int d, int s)
    : name(n), hp(h), attack(a), defense(d), spd(s) {
}

void Monster::takeDamage(int damage) {
    int actualDamage = std::max(1, damage - defense);
    hp -= actualDamage;
    if (hp < 0) hp = 0;

    std::cout << name << "에게 " << actualDamage << "의 피해를 입혔습니다! "
        << "(남은 HP: " << hp << ")" << std::endl;
}