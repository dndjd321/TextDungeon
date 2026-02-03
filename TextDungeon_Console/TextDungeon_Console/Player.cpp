#include "Player.h"
#include <iostream>
#include <algorithm> // max 함수 사용

Player::Player(std::string n, int h, int a, int d, int s)
    : name(n), hp(h), maxHp(h), attack(a), defense(d), spd(s), gold(0) {
}

void Player::takeDamage(int damage) {
    // 받은 데미지에서 방어력을 뺌 (최소 1 데미지는 입도록 설정)
    int actualDamage = std::max(1, damage - defense);
    hp -= actualDamage;
    if (hp < 0) hp = 0;

    std::cout << name << "이(가) " << actualDamage << "의 피해를 입었습니다! "
        << "(남은 HP: " << hp << ")" << std::endl;
}


void Player::showStatus() {
    std::cout << "\n======= " << name << "의 정보 =======" << std::endl;
    std::cout << "HP: " << hp << " / " << maxHp << std::endl;
    std::cout << "ATK: " << attack << " | DEF: " << defense << " | SPD: " << spd << std::endl;
    std::cout << "GOLD: " << gold << std::endl;
    std::cout << "==============================\n" << std::endl;
}

void Player::gainGold(int amount) {
    gold += amount;
    std::cout << name << "이(가) " << amount << " 골드를 얻었습니다! "
        << "(현재 골드: " << gold << ")" << std::endl;
}