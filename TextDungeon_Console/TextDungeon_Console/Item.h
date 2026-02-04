#pragma once
#include <string>

class Item {
private:
    std::string name;
    // 각 능력치별 강화 단계
    int atkLevel = 0, defLevel = 0, spdLevel = 0, hpLevel = 0;
    int baseUpgradePrice; // 기본 강화 비용

public:
    Item(std::string n, int p) : name(n), baseUpgradePrice(p) {}

    // 강화 실행
    void upgrade(int choice) {
        if (choice == 1) atkLevel++;
        else if (choice == 2) defLevel++;
        else if (choice == 3) spdLevel++;
        else if (choice == 4) hpLevel++;
    }

    // 각 스탯별 현재 강화 비용 계산
    int getStatUpgradePrice(int choice) const {
        int level = 0;
        if (choice == 1) level = atkLevel;
        else if (choice == 2) level = defLevel;
        else if (choice == 3) level = spdLevel;
        else if (choice == 4) level = hpLevel;
        return baseUpgradePrice + (level * 30);
    }

    // 아이템 정보 표시용 이름
    std::string getDisplayName() const {
        return name + 
            " (" + 
            " 공격+" + std::to_string(atkLevel) + 
            " 방어+" + std::to_string(defLevel) +
            " 속도+" + std::to_string(spdLevel) + 
            " 체력+" + std::to_string(hpLevel) + 
            " )";
    }

    // 플레이어 스탯에 합산될 보너스 수치들 (Getter)
    int getAtkBonus() const { return atkLevel * 3; }
    int getDefBonus() const { return defLevel * 2; }
    int getSpdBonus() const { return spdLevel * 2; }
    int getHpBonus() const { return hpLevel * 10; }

    std::string getName() const { return name; }
};


//#pragma once
//#include <string>
//
//enum class StatType { NONE, ATTACK, DEFENSE, SPEED, HP };
//
//class Item {
//private:
//    std::string name;           // 아이템명
//    StatType upStat;            // 상승 능력치 타입
//    int upValue;                // 상승 수치
//    StatType downStat;          // 하락 능력치 타입
//    int downValue;              // 하락 수치
//    int price;                  // 강화 가격
//	
//    // 각 스탯별 강화 레벨
//    int atkLevel;  		        // atk 강화 레벨
//    int defLevel;  		        // def 강화 레벨
//    int spdLevel;  		        // spd 강화 레벨
//    int hpLevel;  		        // hp 강화 레벨
//
//public:
//    Item(std::string n, StatType us, int uv, StatType ds, int dv, int p)
//        : name(n), upStat(us), upValue(uv), downStat(ds), downValue(dv), price(p) {
//    }
//
//    // 강화 시 호출 함수
//    void upgrade(int num) { 
//
//        try {
//            if (num == 1) atkLevel++;
//            else if (num == 2) defLevel++;
//            else if (num == 3) spdLevel++;
//            else if (num == 4) hpLevel++;
//        }
//        catch(exception ex){ }
//    }
//
//	// 현재 강화 수치가 반영된 이름 반환
//    std::string getDisplayName(int num) const {
//        return name + 
//            " (" 
//            +"공격 + " + std::to_string(atkLevel) + 
//            " 방어+" + std::to_string(defLevel) +
//            " 속도+" + std::to_string(spdLevel) + 
//            " 체력+" + std::to_string(hpLevel) + 
//            ")";
//	}
//
//    // 각 능력치별 증가량 계산 (강화 단계당 고정 수치 증가 예시)
//    int getAtkBonus() const { return atkLevel * 3; }
//    int getDefBonus() const { return defLevel * 2; }
//    int getSpdBonus() const { return spdLevel * 2; }
//    int getHpBonus() const { return hpLevel * 10; }
//
//    // 각 스탯별 현재 강화 비용 계산 
//    int getStatUpgradePrice(int num) const {
//        int level = 0;
//        if (num == 1) { level = atkLevel; }
//        else if (num == 2) { level = defLevel; }
//        else if (num == 3) { level = spdLevel; }
//        else if (num == 4) { level = hpLevel; }
//
//        return price + ( level * 30 );
//    }
//
//    // Getter 함수들
//    std::string getName() const { return name; }
//    StatType getUpStat() const { return upStat; }
//    int getUpValue() const { return upValue; }
//    StatType getDownStat() const { return downStat; }
//    int getDownValue() const { return downValue; }
//    int getPrice() const { return price; }
//	//int getLevel() const { return level; }
//};