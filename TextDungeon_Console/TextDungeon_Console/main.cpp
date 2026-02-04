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

//int main() {
//    srand((unsigned int)time(NULL));
//    // 1. 플레이어 객체 생성
//	Player hero("플레이어", 100, 15, 5, 10);    // (이름, 체력, 공격력, 방어력, 속도)
//    Slime slime;
//	Goblin goblin;
//
//	bool gameRunning = true;    // 게임 진행 상태 변수
//
//    // 게임 진행 메뉴
//    while (gameRunning && hero.getHp() > 0) {
//		system("cls");      // 화면 정리
//		hero.showStatus();  // 플레이어 상태 출력
//
//        cout << "=== [ 마을 ] ===" << endl;
//        cout << "1. 던전 입장 (전투)" << endl;
//        cout << "2. 여관에서 휴식 (HP 회복, 20골드)" << endl;
//        cout << "3. 대장간 방문 (플레이어 강화)" << endl;
//        cout << "4. 게임 종료" << endl;
//        cout << "선택: ";
//
//        int menu;
//        cin >> menu;
//
//        if (menu == 1) {
//            // --- 전투 루프 시작 ---
//            Monster* enemy = nullptr;
//
//            // 50% 확률로 슬라임 또는 고블린 등장
//            if (rand() % 2 == 0) enemy = new Slime();
//            else enemy = new Goblin();
//
//            cout << "\n[!] " << enemy->getName() << "이(가) 나타났습니다!" << endl;
//            enemy->attackEffect();
//
//            // 여기서 전투 로직(누가 먼저 공격할지 spd 비교 등)을 작성...
//            cout << "=== 전투 시작! ===" << endl;
//
//            // 2. 전투 루프 ( 둘 중 하나가 HP 0 이하가 될 때까지 )
//            while (hero.getHp() > 0 && enemy->getHp() > 0) {
//
//                // 1. 속도(spd) 비교를 통한 선공 결정
//                if (hero.getSpd() >= enemy->getSpd()) {
//                    cout << "\n[플레이어 턴]" << endl;
//                    enemy->takeDamage(hero.getAtk());
//
//                    if (enemy->getHp() > 0) {
//                        cout << "[슬라임 턴]" << endl;
//                        hero.takeDamage(enemy->getAtk());
//                    }
//                }
//                else {
//                    cout << "\n[슬라임 턴]" << endl;
//                    hero.takeDamage(enemy->getAtk());
//
//                    if (hero.getHp() > 0) {
//                        cout << "[플레이어 턴]" << endl;
//                        enemy->takeDamage(hero.getAtk());
//                    }
//                }
//
//                system("pause"); // 한 턴마다 멈춰서 확인
//
//                //hero.showStatus();
//
//                //// 잠시 멈춰서 진행 상황 확인 (엔터 키 입력 시 진행)
//                //cout << "엔터 키를 눌러 다음 턴 진행...";
//                //cin.ignore();
//                //cin.get();
//                ////system("pause"); // 한 턴마다 멈춰서 확인
//            }
//
//            if (hero.getHp() > 0) {
//                cout << "승리했습니다!" << endl;
//				hero.gainGold(10 + rand() % 11); // 10~20 골드 획득
//            }
//            else {
//                cout << "패배했습니다..." << endl; 
//            }
//
//			delete enemy;   // 동적 할당 해제
//			system("pause"); // 잠시 멈춤
//        }
//        else if (menu == 2) {   // 여관 기능
//			//  휴식 로직 ( 골드 체크 및 HP 회복 )
//            if (hero.getGold() >= 20) {
//				hero.loseGold(20);              // 20골드 지불
//				hero.rest((hero.getHp() / 2));  // 최대 HP의 절반 회복
//            }
//            else {
//                cout << "\n[!] 골드가 부족합니다! ( 필요 : 20골드 )" << endl;
//            }
//            
//            system("pause");
//        }
//        else if (menu == 3) {   // 대장간 기능
//            bool isForge = true; // 대장간 루프 제어 변수
//
//            while (isForge) {
//                system("cls");
//                hero.showStatus();  // 내 돈과 스택 확인용
//
//				Item* myItem = hero.getEquippedItem(); // 장착 아이템 포인터
//
//                cout << "\n--- [ 대장간 ] ---" << endl;
//                cout << "1. 공격력 강화 - 50골드" << endl; //(공격력 +5)
//                cout << "2. 방어력 강화 - 50골드" << endl; //(방어력 +5)
//                cout << "3. 스피드 강화 - 30골드" << endl; //(스피드 +2)
//                cout << "4. 체력 강화 - 100골드" << endl;  //(최대 체력 +10) 
//                cout << "5. 돌아가기" << endl;
//                cout << "선택: ";
//
//                int shopMenu;
//                cin >> shopMenu;
//
//                if (shopMenu == 1) {        // 나무 검 : 공격 + 5 : 50골
//                    if (hero.getGold() >= 50) {
//                        hero.loseGold(50);
//                        hero.addAtk(5);
//                    }
//                    else {
//                        cout << "\n[!] 골드가 부족합니다." << endl;
//                    }
//                }
//                else if (shopMenu == 2) {   // 강철 검 : 공격 + 12 : 110골
//
//                }
//                else if (shopMenu == 3) {   // 녹슨 방패 : 방어 + 5 : 50골
//
//                }
//                else if (shopMenu == 4) {   // 강철 방패 : 방어 + 12 : 110골
//
//                }
//                else if (shopMenu == 5) {   // 헌 신발 : 스피드 + 2 : 30골
//
//                }
//                else if (shopMenu == 6) {   // 가죽 부츠 : 스피드 +7 : 100골
//
//                }
//                else if (shopMenu == 7) {   // 체력증진물약(소) : 최대체력 + 10 : 100골
//
//                }
//                else if (shopMenu == 8) {   // 체력증진물약(대) : 최대체력 + 25 : 230골
//
//                }
//                else if (shopMenu == 9) {   // 돌아가기
//                    cout << "\n마을로 돌아갑니다..." << endl;
//                    isForge = false; // 루프 탈출하도록 제어 변수 false로 변경
//                }
//                else {
//                    cout << "\n[!] 잘못된 입력입니다." << endl;
//                    system("pause");
//                }
//            }
//            
//
//        }
//        else if (menu == 4) {   // 게임 종료
//            gameRunning = false;
//        }
//    }
//
//	cout << "게임이 종료되었습니다." << endl;
//    return 0;
//}