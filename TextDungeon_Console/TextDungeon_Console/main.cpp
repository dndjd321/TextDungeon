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
        cout << "3. 게임 종료" << endl;
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
        else if (menu == 2) {
			//  휴식 로직 ( 골드 체크 및 HP 회복 )
            // hero.rest(); 등 함수 구현하기
        }
        else if (menu == 3) {
			gameRunning = false;
        }
    }

	cout << "게임이 종료되었습니다." << endl;
    return 0;
}