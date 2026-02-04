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
    // 1. 플레이어 객체 생성
	Player hero("플레이어", 100, 15, 5, 10);    // (이름, 체력, 공격력, 방어력, 속도)
    Slime slime;
	Goblin goblin;

	bool gameRunning = true;    // 게임 진행 상태 변수

    // 게임 진행 메뉴
    while (gameRunning && hero.getHp() > 0) {
		system("cls");      // 화면 정리
		hero.showStatus();  // 플레이어 상태 출력

        cout << "=== [ 마을 ] ===" << endl;
        cout << "1. 던전 입장 (전투)" << endl;
        cout << "2. 여관에서 휴식 (HP 회복, 20골드)" << endl;
        cout << "3. 무기 상점 방문 (플레이어 강화)" << endl;
        cout << "4. 게임 종료" << endl;
        cout << "선택: ";

        int menu;
        cin >> menu;

        if (menu == 1) {
            // --- 전투 루프 시작 ---
            Monster* enemy = nullptr;

            // 50% 확률로 슬라임 또는 고블린 등장
            if (rand() % 2 == 0) enemy = new Slime();
            else enemy = new Goblin();

            cout << "\n[!] " << enemy->getName() << "이(가) 나타났습니다!" << endl;
            enemy->attackEffect();

            // 여기서 전투 로직(누가 먼저 공격할지 spd 비교 등)을 작성...
            cout << "=== 전투 시작! ===" << endl;

            // 2. 전투 루프 ( 둘 중 하나가 HP 0 이하가 될 때까지 )
            while (hero.getHp() > 0 && enemy->getHp() > 0) {

                // 1. 속도(spd) 비교를 통한 선공 결정
                if (hero.getSpd() >= enemy->getSpd()) {
                    cout << "\n[플레이어 턴]" << endl;
                    enemy->takeDamage(hero.getAtk());

                    if (enemy->getHp() > 0) {
                        cout << "[슬라임 턴]" << endl;
                        hero.takeDamage(enemy->getAtk());
                    }
                }
                else {
                    cout << "\n[슬라임 턴]" << endl;
                    hero.takeDamage(enemy->getAtk());

                    if (hero.getHp() > 0) {
                        cout << "[플레이어 턴]" << endl;
                        enemy->takeDamage(hero.getAtk());
                    }
                }

                system("pause"); // 한 턴마다 멈춰서 확인

                //hero.showStatus();

                //// 잠시 멈춰서 진행 상황 확인 (엔터 키 입력 시 진행)
                //cout << "엔터 키를 눌러 다음 턴 진행...";
                //cin.ignore();
                //cin.get();
                ////system("pause"); // 한 턴마다 멈춰서 확인
            }

            if (hero.getHp() > 0) {
                cout << "승리했습니다!" << endl;
				hero.gainGold(10 + rand() % 11); // 10~20 골드 획득
            }
            else {
                cout << "패배했습니다..." << endl; 
            }

			delete enemy;   // 동적 할당 해제
			system("pause"); // 잠시 멈춤
        }
        else if (menu == 2) {   // 여관 기능
			//  휴식 로직 ( 골드 체크 및 HP 회복 )
            if (hero.getGold() >= 20) {
				hero.loseGold(20);              // 20골드 지불
				hero.rest((hero.getHp() / 2));  // 최대 HP의 절반 회복
            }
            else {
                cout << "\n[!] 골드가 부족합니다! ( 필요 : 20골드 )" << endl;
            }
            
            system("pause");
        }
        else if (menu == 3) {   // 상점 기능
            bool isShop = true; // 상점 루프 제어 변수

            while (isShop) {
                system("cls");
                hero.showStatus();  // 내 돈과 스택 확인용

                cout << "\n--- [ 무기 상점 ] ---" << endl;
                cout << "1. 나무 검 (공격력 +5) - 50골드" << endl;
                cout << "2. 강철 검 (공격력 +12) - 110골드" << endl;
                cout << "3. 녹슨 방패 (방어력 +5) - 50골드" << endl;
                cout << "4. 강철 방패 (방어력 +12) - 110골드" << endl;
                cout << "5. 헌 신발 (스피드 +2) - 30골드" << endl;
                cout << "6. 가죽 부츠(스피드 +7) - 100골드" << endl;
                cout << "7. 체력증진물약(소) (최대 체력 +10) - 100골드" << endl;
                cout << "8. 체력증진물약(대) (최대 체력 +25) - 230골드" << endl;
                cout << "9. 돌아가기" << endl;
                cout << "구매할 아이템: ";

                int shopMenu;
                cin >> shopMenu;

                if (shopMenu == 1) {        // 나무 검 : 공격 + 5 : 50골
                    if (hero.getGold() >= 50) {
                        hero.loseGold(50);
                        hero.addAtk(5);
                    }
                    else {
                        cout << "\n[!] 골드가 부족합니다." << endl;
                    }
                }
                else if (shopMenu == 2) {   // 강철 검 : 공격 + 12 : 110골

                }
                else if (shopMenu == 3) {   // 녹슨 방패 : 방어 + 5 : 50골

                }
                else if (shopMenu == 4) {   // 강철 방패 : 방어 + 12 : 110골

                }
                else if (shopMenu == 5) {   // 헌 신발 : 스피드 + 2 : 30골

                }
                else if (shopMenu == 6) {   // 가죽 부츠 : 스피드 +7 : 100골

                }
                else if (shopMenu == 7) {   // 체력증진물약(소) : 최대체력 + 10 : 100골

                }
                else if (shopMenu == 8) {   // 체력증진물약(대) : 최대체력 + 25 : 230골

                }
                else if (shopMenu == 9) {   // 돌아가기
                    cout << "\n마을로 돌아갑니다..." << endl;
                    isShop = false; // 루프 탈출하도록 제어 변수 false로 변경
                }
                else {
                    cout << "\n[!] 잘못된 입력입니다." << endl;
                    system("pause");
                }
            }
            

        }
        else if (menu == 4) {   // 게임 종료
            gameRunning = false;
        }
    }

	cout << "게임이 종료되었습니다." << endl;
    return 0;
}