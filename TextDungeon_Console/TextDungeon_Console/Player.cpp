#include "Player.h"
#include "Item.h"
#include <iostream>
#include <algorithm>

Player::Player(std::string n, int h, int a, int d, int s)
    : name(n), hp(h), maxHp(h), attack(a), defense(d), spd(s), gold(20), equippedItem(nullptr) {
}

int Player::getTotalAtk() { return attack + (equippedItem ? equippedItem->getAtkBonus() : 0); }
int Player::getTotalDef() { return defense + (equippedItem ? equippedItem->getDefBonus() : 0); }
int Player::getTotalSpd() { return spd + (equippedItem ? equippedItem->getSpdBonus() : 0); }
int Player::getTotalMaxHp() { return maxHp + (equippedItem ? equippedItem->getHpBonus() : 0); }

void Player::takeDamage(int damage) {
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

    // 4. 최소 데미지 1 보장
    if (finalDamage < 1) finalDamage = 1;

    //int actualDamage = std::max(1, damage - defense);
    hp -= finalDamage;
    if (hp < 0) hp = 0;

    /*int actualDamage = std::max(1, damage - getTotalDef());
    hp -= actualDamage;*/
    //if (hp < 0) hp = 0;
    std::cout << "[결과] " << name << "이(가) " << finalDamage << "의 피해를 입었습니다!" << std::endl;
    if (isCritical) std::cout << "[크리티컬!]";
    std::cout << "(남은 HP: " << hp << ")" << std::endl;
}

void Player::rest() {
    hp = getTotalMaxHp();
    std::cout << "\n[💤] 여관에서 휴식했습니다. 모든 HP가 회복되었습니다!" << std::endl;
}

void Player::gainExp(int amount) {
	exp += amount;
	std::cout << "\n[!] " << amount << "의 경험치를 획득했습니다! (현재 EXP: " << exp << " / " << maxExp << ")" << std::endl;

    while (exp >= maxExp) {
        levelUp();
    }
}

void Player::levelUp() {
    exp -= maxExp;
    level++;
    statPoints += 3; // 레벨업 시 스탯 포인트 5점 획득
    maxExp = static_cast<int>(maxExp * 1.2); // 다음 레벨업까지 필요한 경험치 증가

	hp = getTotalMaxHp(); // 레벨업 시 체력 완전 회복

    std::cout << "\n================================================================" << std::endl;
    std::cout << "\n[🎉] 레벨업! " << name << "의 레벨이 " << level << "이 되었습니다!" << std::endl;
    std::cout << "[🎁] 스탯 포인트 3점을 획득했습니다! (현재 스탯 포인트: " << statPoints << ")" << std::endl;
    std::cout << "\n================================================================" << std::endl;

}

void Player::useStatPoint(int choice) {
    if (statPoints <= 0) {
        std::cout << "\n[!] 사용 가능한 스탯 포인트가 없습니다!" << std::endl;
        return;
    }

    switch (choice) {
        case 1:
            attack += 2;
            std::cout << "\n[⚔️] 공격력이 2만큼 증가했습니다! (현재 공격력: " << attack << ")" << std::endl;
            break;
        case 2:
            defense += 2;
            std::cout << "\n[🛡️] 방어력이 2만큼 증가했습니다! (현재 방어력: " << defense << ")" << std::endl;
            break;
        case 3:
            spd += 2;
            std::cout << "\n[👟] 스피드가 2만큼 증가했습니다! (현재 스피드: " << spd << ")" << std::endl;
            break;
        case 4:
            maxHp += 10;
            hp += 10; // 최대 체력 증가 시 현재 체력도 함께 증가
            std::cout << "\n[❤️] 최대 체력이 10만큼 증가했습니다! (현재 최대 체력: " << maxHp << ")" << std::endl;
            break;
        default:
            std::cout << "\n[!] 잘못된 선택입니다!" << std::endl;
            return;
    }
    statPoints--;
    std::cout << "[남은 스탯 포인트: " << statPoints << "]" << std::endl;
}

void Player::showStatus() {
    std::cout << "\n========== [ " << name << " 정보 ] ==========" << std::endl;
    std::cout << "HP: " << hp << " / " << getTotalMaxHp() << std::endl;
    std::cout << "공격력: " << getTotalAtk() << " (기본 " << attack << ")" << std::endl;
    std::cout << "방어력: " << getTotalDef() << " (기본 " << defense << ")" << std::endl;
    std::cout << "스피드: " << getTotalSpd() << " (기본 " << spd << ")" << std::endl;
    std::cout << "소지금: " << gold << " G" << std::endl;
    if (equippedItem) std::cout << "장착 아이템: " << equippedItem->getDisplayName() << std::endl;
    std::cout << "===========================================" << std::endl;
}



//#include "Player.h"
//#include "Item.h"
//#include <iostream>
//#include <algorithm> // max 함수 사용
//
//// 플레이어 생성자
//Player::Player(std::string n, int h, int a, int d, int s)
//    : name(n), hp(h), maxHp(h), attack(a), defense(d), spd(s), gold(0) {
//}
//
//// 데미지 받기
//void Player::takeDamage(int damage) {
//    // 받은 데미지에서 방어력을 뺌 (최소 1 데미지는 입도록 설정)
//    int actualDamage = std::max(1, damage - defense);
//    hp -= actualDamage;
//    if (hp < 0) hp = 0;
//
//    std::cout << name << "이(가) " << actualDamage << "의 피해를 입었습니다! "
//        << "(남은 HP: " << hp << ")" << std::endl;
//}
//
//// 플레이어 상태 출력
//void Player::showStatus() {
//    std::cout << "\n======= " << name << "의 정보 =======" << std::endl;
//    std::cout << "HP: " << hp << " / " << maxHp << std::endl;
//    std::cout << "ATK: " << attack << " | DEF: " << defense << " | SPD: " << spd << std::endl;
//    std::cout << "GOLD: " << gold << std::endl;
//    std::cout << "==============================\n" << std::endl;
//}
//
//// 골드 획득
//void Player::gainGold(int amount) {
//    gold += amount;
//    std::cout << name << "이(가) " << amount << " 골드를 얻었습니다! "
//        << "(현재 골드: " << gold << ")" << std::endl;
//}
//
//// 휴식하여 HP 회복
//void Player::rest(int amount) {
//    hp += amount;
//    if (hp > maxHp) hp = maxHp;
//    std::cout << name << "이(가) [💤] 여관에서휴식을 취하여 " << amount << "의 HP를 회복했습니다! "
//        << "(현재 HP: " << hp << ")" << std::endl;
//}
//
//// 공격력 증가
//void Player::addAtk(int amount) {
//    attack += amount;
//    std::cout << "[⚔️] 무기를 강화하여" << name << "의 공격력이 " << amount << "만큼 증가했습니다! "
//        << "(현재 ATK: " << attack << ")" << std::endl;
//}
//
//// 방어력 증가
//void Player::addDef(int amount) {
//    defense += amount;
//    std::cout << "[🛡️] 방어구를 강화하여" << name << "의 방어력이 " << amount << "만큼 증가했습니다! "
//        << "(현재 DEF: " << defense << ")" << std::endl;
//}
//
//// 속도 증가
//void Player::addSpd(int amount) {
//    spd += amount;
//    std::cout << "[👟] 신발을 강화하여" << name << "의 속도가 " << amount << "만큼 증가했습니다! "
//        << "(현재 SPD: " << spd << ")" << std::endl;
//}
//
//// 최대 체력 증가
//void Player::addMaxHp(int amount) {
//    maxHp += amount;
//    hp += amount; // 최대 체력 증가 시 현재 체력도 함께 증가
//    std::cout << "[❤️] 체력을 강화하여" << name << "의 최대 체력이 " << amount << "만큼 증가했습니다! "
//        << "(현재 HP: " << hp << " / " << maxHp << ")" << std::endl;
//}
//
//// 아이템 사용
//void Player::useItem(const Item& item) {
//    // 상승 능력치 적용
//	applyStatChange(item.getUpStat(), item.getUpValue());
//
//	// 하락 능력치 적용
//	applyStatChange(item.getDownStat(), -item.getDownValue());
//
//    std::cout << "\n[!] " << item.getName() << "을(를) 장착/사용했습니다!" << std::endl;
//}
//
//// 능력치 변화 적용
//void Player::applyStatChange(StatType type, int value) {
//    // StatType { NONE, ATTACK, DEFENSE, SPEED, HP };
//
//    switch (type) {
//        case StatType::NONE:
//            // 변화 없음
//			break;
//        case StatType::ATTACK:
//            addAtk(value);
//			break;
//
//    
//    }
//}
