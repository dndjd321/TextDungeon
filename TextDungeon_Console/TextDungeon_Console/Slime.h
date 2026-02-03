#pragma once
#include "Monster.h"
#include <iostream>

// Monster 클래스를 public으로 상속받습니다.
class Slime : public Monster {
public:
    // 생성자: 슬라임은 기본적으로 체력이 낮고 속도가 느린 컨셉으로 설정해봅니다.
    // Monster(이름, 체력, 공격력, 방어력, 속도)
    Slime() : Monster("초록 슬라임", 30, 8, 2, 3) {}

    // Monster 클래스에서 virtual로 선언했던 attackEffect를 재정의(Override)합니다.
    void attackEffect() override {
        std::cout << ">> [슬라임] 몸을 부풀려 몸통박치기를 시도합니다! <<" << std::endl;
    }

    // 슬라임만의 특수 능력 (예: 분열, 점액 발사 등)을 추가할 수도 있습니다.
    void jumpAttack() {
        std::cout << ">> [슬라임] 높이 점프하여 깔아뭉갭니다! <<" << std::endl;
    }
};