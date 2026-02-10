#include "Player.h"
#include "Slime.h"
#include "Goblin.h"
#include <iostream>
#include <windows.h>    // 색상 제어를 위해 필요
#include <ctime>

using namespace std;

void SetColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int main() {
    srand((unsigned int)time(NULL));

    Player hero("용사", 100, 15, 5, 10);
    Item* starterWeapon = new Item("낡은 초보자 검", 30);
    hero.setEquippedItem(starterWeapon);

    while (hero.getHp() > 0) {
        system("cls");
        hero.showStatus();
        cout << "\n[1] 던전 입장  [2] 여관 휴식(20G)  [3] 대장간(강화) [4] 상태창/스탯투자 [5] 게임 종료" << endl;
        cout << "입력: ";
        int menu; cin >> menu;

        if (menu == 1) { // 던전
            Monster* enemy = (rand() % 2 == 0) ? (Monster*)new Slime() : (Monster*)new Goblin();
            cout << "\n[!] " << enemy->getName() << "이(가) 나타났습니다!" << endl;

            while (hero.getHp() > 0 && enemy->getHp() > 0) {
                if (hero.getTotalSpd() >= enemy->getSpd()) { // 플레이어 선공
                    cout << "\n[플레이어의 턴]" << endl;
                    enemy->takeDamage(hero.getTotalAtk());
                    if (enemy->getHp() > 0) {
                        enemy->attackEffect();
                        hero.takeDamage(enemy->getAtk());
                    }
                }
                else { // 몬스터 선공
                    cout << "\n[몬스터의 턴]" << endl;
                    enemy->attackEffect();
                    hero.takeDamage(enemy->getAtk());
                    if (hero.getHp() > 0) {
                        cout << "[플레이어의 턴]" << endl;
                        enemy->takeDamage(hero.getTotalAtk());
                    }
                }
                system("pause");
            }
            if (hero.getHp() > 0) {
				int rewardG = enemy->dropGold();
                int rewardE = enemy->getExpReward();
                cout << "\n전투 승리!" << endl;
                cout << "보상 : " << rewardG << "G / " << rewardE << "EXP를 얻었습니다." << endl;
				hero.gainGold(rewardG);
                hero.gainExp(rewardE);
            }
            delete enemy;
            system("pause");
        }
        else if (menu == 2) { // 여관
            if (hero.getGold() >= 20) {
                hero.loseGold(20);
                hero.rest();
            }
            else cout << "\n[!] 골드가 부족합니다." << endl;
            system("pause");
        }
        else if (menu == 3) { // 대장간
            bool inForge = true;
            while (inForge) {
                system("cls");
                Item* item = hero.getEquippedItem();
                cout << "--- [ 대장간: 아이템 강화 ] ---" << endl;
                cout << "현재 장비: " << item->getDisplayName() << endl;
                cout << "소지금: " << hero.getGold() << " G" << endl;
                cout << "-------------------------------" << endl;
                cout << "1. 공격력 강화 (" << item->getStatUpgradePrice(1) << "G)" << endl;
                cout << "2. 방어력 강화 (" << item->getStatUpgradePrice(2) << "G)" << endl;
                cout << "3. 스피드 강화 (" << item->getStatUpgradePrice(3) << "G)" << endl;
                cout << "4. 체력 강화   (" << item->getStatUpgradePrice(4) << "G)" << endl;
                cout << "5. 마을로 돌아가기" << endl;
                cout << "선택: ";
                int fMenu; cin >> fMenu;

                if (fMenu == 5) inForge = false;
                else if (fMenu >= 1 && fMenu <= 4) {
                    int cost = item->getStatUpgradePrice(fMenu);
                    if (hero.getGold() >= cost) {
                        hero.loseGold(cost);
                        if (rand() % 100 < 70) {
                            item->upgrade(fMenu);
                            cout << "\n[★] 강화에 성공했습니다!" << endl;
                        }
                        else cout << "\n[😭] 강화에 실패했습니다." << endl;
                        system("pause");
                    }
                    else {
                        cout << "\n[!] 골드가 부족합니다!" << endl;
                        system("pause");
                    }
                }
            }
        }
        else if (menu == 4) {
            bool isStatMenu = true;
            while (isStatMenu) {
				system("cls");
				hero.showStatus();

                cout << "\n[ 보유 스탯 포인트: " << hero.getStatPoints() << " ]" << endl;
                cout << "1. 공격력 투자 (+2)" << endl;
                cout << "2. 방어력 투자 (+2)" << endl;
                cout << "3. 스피드 투자 (+2)" << endl;
                cout << "4. 체력 투자 (+10)" << endl;
                cout << "5. 나가기" << endl;
                cout << "선택: ";

                int sChoice; cin >> sChoice;
                if (sChoice == 5) isStatMenu = false;
                else if (hero.getStatPoints() > 0) hero.useStatPoint(sChoice);
                else {
                    cout << "포인트가 부족합니다!" << endl;
                    system("pause");
                }
            }
        }
        else if (menu == 5) break;
    }

    delete starterWeapon; // 게임 종료 시 메모리 해제
    cout << "\n게임을 종료합니다. 방문해 주셔서 감사합니다!" << endl;
    return 0;
}