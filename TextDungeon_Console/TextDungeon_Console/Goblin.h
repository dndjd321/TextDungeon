#pragma once
#include "Monster.h"
#include <iostream>

class Goblin : public Monster {
public:
    // 고블린은 슬라임보다 체력은 높고 속도는 빠릅니다.
    // Monster(이름, 체력, 공격력, 방어력, 속도)
    Goblin() : Monster("날쌘 고블린", 50, 12, 3, 15, 40, 70, 30) {}

    void attackEffect() override {
        std::cout << ">> [고블린] 비열하게 웃으며 단검을 휘두릅니다! <<" << std::endl;
    }
};

