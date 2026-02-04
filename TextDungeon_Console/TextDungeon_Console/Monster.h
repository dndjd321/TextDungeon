#pragma once
#include <string>

class Monster {
protected:
    std::string name;
    int hp, attack, defense, spd;
public:
    Monster(std::string n, int h, int a, int d, int s);
    virtual ~Monster() {} // 가상 소멸자
    virtual void attackEffect() = 0;
    void takeDamage(int damage);

    // Getter
    int getHp() { return hp; }
    int getAtk() { return attack; }
    int getSpd() { return spd; }
    std::string getName() { return name; }
};

//#pragma once
//#include <string>
//
//class Monster {
//protected: // 자식 클래스에서는 접근 가능
//    std::string name;
//    int hp;
//    int attack;
//	int defense;
//    int spd;
//
//public:
//    // Monster(std::string n, int h, int a, int d, int s) : name(n), hp(h), attack(a), defense(d), spd(s) {}
//    Monster(std::string n, int h, int a, int d, int s);
//    virtual void attackEffect() = 0; // 순수 가상 함수 (몬스터마다 공격 연출이 다를 때)
//
//    int getHp() { return hp; }
//    int getAtk() { return attack; }
//    int getSpd() { return spd; }
//    //void takeDamage(int damage) { hp -= damage; }
//    void takeDamage(int damage);
//    std::string getName() { return name; }
//};