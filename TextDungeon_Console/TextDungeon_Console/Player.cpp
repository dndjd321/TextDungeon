#include "Player.h"
#include "Item.h"
#include <iostream>
#include <algorithm> // max 함수 사용

// 플레이어 생성자
Player::Player(std::string n, int h, int a, int d, int s)
    : name(n), hp(h), maxHp(h), attack(a), defense(d), spd(s), gold(0) {
}

// 데미지 받기
void Player::takeDamage(int damage) {
    // 받은 데미지에서 방어력을 뺌 (최소 1 데미지는 입도록 설정)
    int actualDamage = std::max(1, damage - defense);
    hp -= actualDamage;
    if (hp < 0) hp = 0;

    std::cout << name << "이(가) " << actualDamage << "의 피해를 입었습니다! "
        << "(남은 HP: " << hp << ")" << std::endl;
}

// 플레이어 상태 출력
void Player::showStatus() {
    std::cout << "\n======= " << name << "의 정보 =======" << std::endl;
    std::cout << "HP: " << hp << " / " << maxHp << std::endl;
    std::cout << "ATK: " << attack << " | DEF: " << defense << " | SPD: " << spd << std::endl;
    std::cout << "GOLD: " << gold << std::endl;
    std::cout << "==============================\n" << std::endl;
}

// 골드 획득
void Player::gainGold(int amount) {
    gold += amount;
    std::cout << name << "이(가) " << amount << " 골드를 얻었습니다! "
        << "(현재 골드: " << gold << ")" << std::endl;
}

// 휴식하여 HP 회복
void Player::rest(int amount) {
    hp += amount;
    if (hp > maxHp) hp = maxHp;
    std::cout << name << "이(가) [💤] 여관에서휴식을 취하여 " << amount << "의 HP를 회복했습니다! "
        << "(현재 HP: " << hp << ")" << std::endl;
}

// 공격력 증가
void Player::addAtk(int amount) {
    attack += amount;
    std::cout << "[⚔️] 무기를 강화하여" << name << "의 공격력이 " << amount << "만큼 증가했습니다! "
        << "(현재 ATK: " << attack << ")" << std::endl;
}

// 방어력 증가
void Player::addDef(int amount) {
    defense += amount;
    std::cout << "[🛡️] 방어구를 강화하여" << name << "의 방어력이 " << amount << "만큼 증가했습니다! "
        << "(현재 DEF: " << defense << ")" << std::endl;
}

// 속도 증가
void Player::addSpd(int amount) {
    spd += amount;
    std::cout << "[👟] 신발을 강화하여" << name << "의 속도가 " << amount << "만큼 증가했습니다! "
        << "(현재 SPD: " << spd << ")" << std::endl;
}

// 최대 체력 증가
void Player::addMaxHp(int amount) {
    maxHp += amount;
    hp += amount; // 최대 체력 증가 시 현재 체력도 함께 증가
    std::cout << "[❤️] 체력을 강화하여" << name << "의 최대 체력이 " << amount << "만큼 증가했습니다! "
        << "(현재 HP: " << hp << " / " << maxHp << ")" << std::endl;
}

// 아이템 사용
void Player::useItem(const Item& item) {
    // 상승 능력치 적용
	applyStatChange(item.getUpStat(), item.getUpValue());

	// 하락 능력치 적용
	applyStatChange(item.getDownStat(), -item.getDownValue());

    std::cout << "\n[!] " << item.getName() << "을(를) 장착/사용했습니다!" << std::endl;
}

// 능력치 변화 적용
void Player::applyStatChange(StatType type, int value) {
    // StatType { NONE, ATTACK, DEFENSE, SPEED, HP };

    switch (type) {
        case StatType::NONE:
            // 변화 없음
			break;
        case StatType::ATTACK:
            addAtk(value);
			break;

    
    }
}
