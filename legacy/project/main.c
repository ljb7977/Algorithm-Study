#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>

char player_name_1[50];
char player_name_2[50];

int energy[3];
int mode[3];
int power[3];
int hp[3]={0, 100, 100};

int battle()
{
    system("cls");
    printf("배틀 시작!\n");
    Sleep(1000);
    if(mode[1] == 1){//player 1 에너지 모으기
        if(mode[2] == 1){
            printf("두 플레이어 모두 에너지를 충전했습니다.\n");
            Sleep(1000);
        } else if (mode[2] == 2){
            printf("%s가 %s를 공격력 %d으로 공격했습니다!\n", player_name_2, player_name_1, power[2]);
            Sleep(500);
            hp[1] -= power[2];
            printf("%s는 에너지를 충전하느라 방어하지 못했습니다...\n", player_name_1);
            Sleep(500);
            printf("%s는 데미지를 %d 받았습니다.\n", player_name_1, power[2]);
            Sleep(1000);
        } else if (mode[2] == 3){
            printf("%s는 에너지를 충전했습니다.\n", player_name_1);
            Sleep(500);
            printf("%s는 방어했습니다.\n", player_name_2);
            Sleep(500);
            printf("아무도 데미지를 입지 않았습니다.\n");
            Sleep(1000);
        }
    } else if(mode[1] == 2){//player 1 공격
        if(mode[2] == 1){
            printf("%s가 %s를 공격력 %d으로 공격했습니다!\n", player_name_1, player_name_2, power[1]);
            Sleep(500);
            hp[2] -= power[1];
            printf("%s는 에너지를 충전하느라 방어하지 못했습니다...\n", player_name_2);
            Sleep(500);
            printf("%s는 데미지를 %d 받았습니다.\n", player_name_2, power[1]);
            Sleep(1000);
        } else if (mode[2] == 2){
            printf("%s가 %s를 공격력 %d으로 공격했습니다!\n", player_name_1, player_name_2, power[1]);
            Sleep(500);
            hp[2] -= power[1];

            printf("%s가 %s를 공격력 %d으로 공격했습니다!\n", player_name_2, player_name_1, power[2]);
            Sleep(500);
            hp[1] -= power[2];

            printf("%s는 데미지를 %d 받았습니다.\n", player_name_1, power[2]);
            Sleep(500);

            printf("%s는 데미지를 %d 받았습니다.\n", player_name_2, power[1]);
            Sleep(1000);
        } else if (mode[2] == 3){
            printf("%s가 %s를 공격력 %d으로 공격했습니다!\n", player_name_1, player_name_2, power[1]);
            Sleep(500);
            printf("%s는 방어력 %d으로 방어했습니다!\n", player_name_2, power[2]);
            Sleep(500);
            if(power[2] >= power[1]){
                printf("%s는 데미지를 입지 않았습니다.\n", player_name_2);
            } else {
                printf("%s는 데미지를 %d 입었습니다.\n", player_name_2, power[1]-power[2]);
                hp[2] -= (power[1]-power[2]);
            }
            Sleep(1000);
        }
    } else if(mode[1] == 3){//player 1 방어
        if(mode[2] == 1){
            printf("%s는 에너지를 충전했습니다.\n", player_name_2);
            Sleep(500);
            printf("%s는 방어했습니다.\n", player_name_1);
            Sleep(500);
            printf("아무도 데미지를 입지 않았습니다.\n");
            Sleep(1000);
        } else if (mode[2] == 2){
            printf("%s가 %s를 공격력 %d으로 공격했습니다!\n", player_name_2, player_name_1, power[2]);
            Sleep(500);
            printf("%s는 방어력 %d으로 방어했습니다!\n", player_name_1, power[1]);
            Sleep(500);
            if(power[1] >= power[2]){
                printf("%s는 데미지를 입지 않았습니다.\n", player_name_1);
            } else {
                printf("%s는 데미지를 %d 입었습니다.\n", player_name_1, power[2]-power[1]);
                hp[1] -= (power[2]-power[1]);
            }
            Sleep(1000);
        } else if (mode[2] == 3){
            printf("%s는 방어했습니다.\n", player_name_1);
            Sleep(500);
            printf("%s도 방어했습니다.\n", player_name_2);
            Sleep(500);
            printf("아무도 데미지를 입지 않았습니다.\n");
            Sleep(1000);
        }
    }

    if(hp[1] <= 0 && hp[2] > 0){
        printf("%s(이)가 승리했습니다!\n", player_name_2);
        Sleep(4000);
        return 1;
    } else if (hp[2] <= 0 && hp[1] > 0){
        printf("%s(이)가 승리했습니다!\n", player_name_1);
        Sleep(4000);
        return 1;
    } else if (hp[2] <= 0 && hp[1] <= 0) {
        printf("무승부입니다.\n");
        Sleep(4000);
        return 1;
    }

    printf("%s의 남은 체력 : %d\n", player_name_1, hp[1]);
    printf("%s의 남은 체력 : %d\n", player_name_2, hp[2]);
    Sleep(1000);
    return 0;
}

int main()
{
    srand(time(0));

    int player = 1;
    printf("Battle!\n");

    printf("플레이어 1의 이름을 입력하세요 : ");
    gets(player_name_1);

    while(1){
        printf("플레이어 2의 이름을 입력하세요 : ");
        gets(player_name_2);
        if(strcmp(player_name_1, player_name_2) == 0){
            printf("두 플레이어의 이름이 같습니다.\n");
        } else {
            break;
        }
    }
    Sleep(1000);

    while(1){
        system("cls");
        if(player == 1){
            printf("%s, 무엇을 할지 선택하세요. 현재 에너지는 %d입니다.\n", player_name_1, energy[player]);
        } else if (player == 2){
            printf("%s, 무엇을 할지 선택하세요. 현재 에너지는 %d입니다.\n", player_name_2, energy[player]);
        }
        printf("1. 에너지 모으기   2. 공격하기   3. 방어하기\n");
        scanf("%d", &mode[player]);
        if(mode[player] == 1){//에너지 모으기
            system("cls");
            printf("============에너지 모으기============\n");
            Sleep(1000);

            int r = rand()%100;
            if(r>=0 && r<=2){
                energy[player] += 10;
            } else if (r >= 3 && r<=6){
                energy[player] += 1;
            } else {
                energy[player] += 3;
            }

            energy[player] += rand()%20;

            printf("에너지가 충전되었습니다. 현재 에너지는 %d입니다.\n", energy[player]);
            Sleep(1000);
        } else if (mode[player] == 2){
            if(energy[player] == 0){
                printf("에너지가 0이어서 공격할 수 없습니다.\n");
                Sleep(1000);
                continue;
            }
            while(1){
                system("cls");
                printf("===========공격 모드===========\n");
                printf("공격력을 선택하세요. 현재 에너지 : %d\n", energy[player]);
                scanf("%d", &power[player]);
                if(power[player] > energy[player]){
                    printf("에너지가 부족합니다!\n");
                    Sleep(1000);
                    continue;
                } else {
                    break;
                }
            }
            energy[player] -= power[player];
            printf("공격력을 %d로 설정했습니다. 남은 에너지: %d\n", power[player], energy[player]);
            Sleep(1000);
        } else if (mode[player] == 3){
            if(energy[player] == 0){
                printf("에너지가 0이어서 방어할 수 없습니다.\n");
                Sleep(1000);
                continue;
            }
            while(1){
                system("cls");
                printf("===========방어 모드===========\n");
                printf("방어력을 선택하세요. 현재 에너지 : %d\n", energy[player]);
                scanf("%d", &power[player]);
                if(power[player] > energy[player]){
                    printf("에너지가 부족합니다!\n");
                    Sleep(1000);
                    continue;
                } else {
                    break;
                }
            }
            energy[player] -= power[player];
            printf("방어력을 %d로 설정했습니다. 남은 에너지: %d\n", power[player], energy[player]);
            Sleep(1000);
        }
        if(player == 1){
            player = 2;
        } else if (player == 2){
            player = 1;
            if (battle() == 1){
                printf("게임이 끝났습니다.\n");
                return 0;
            }
        }
    }
    return 0;
}
