#pragma once
#include <string>

enum class StatType { NONE, ATTACK, DEFENSE, SPEED, HP };

class Item {
private:
    std::string name;           // 아이템명
    StatType upStat;            // 상승 능력치 타입
    int upValue;                // 상승 수치
    StatType downStat;          // 하락 능력치 타입
    int downValue;              // 하락 수치
    int price;                  // 강화 가격
	int level;  		        // 아이템 강화 레벨

public:
    Item(std::string n, StatType us, int uv, StatType ds, int dv, int p, int lv)
        : name(n), upStat(us), upValue(uv), downStat(ds), downValue(dv), price(p), level(lv) {
    }

    // 강화 시 호출 함수
    void upgrade() { level++; }

	// 현재 강화 수치가 반영된 이름 반환
    std::string getDisplayName() const {
		if (level == 0) return name;
        return name + " +" + std::to_string(level);
	}

    // 강화 수치에 따른 추가 수치 계산
    int getBoostedValue() const {
        return upValue * level * 0.5; // 상승 수치
	}

	// 강화 가격 계산 (레벨에 따라 증가)
    int getUpgradePrice() const {
		return price + (level * 20); // 기본 가격 + 레벨당 +20 골드 증가
    }

    // Getter 함수들
    std::string getName() const { return name; }
    StatType getUpStat() const { return upStat; }
    int getUpValue() const { return upValue; }
    StatType getDownStat() const { return downStat; }
    int getDownValue() const { return downValue; }
    int getPrice() const { return price; }
};