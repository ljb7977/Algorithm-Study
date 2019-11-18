#include <stdio.h>
#include <stdlib.h>

char player_name_1[50];
char player_name_2[50];

int hp[3] = {0, 50, 50};
int energy[3];
int mode[3];
int power[3];

int main()
{
	int player = 1;

	printf("Battle!\n");

	printf("플레이어 1의 이름을 입력하세요 : ");
    gets(player_name_1);

	while(1){
        printf("플레이어 2의 이름을 입력하세요 : ");
        gets(player_name_2);
        if(strcmp(player_name_1, player_name_2) == 0){
            printf("두 플레이어의 이름이 같습니다.\n");
            Sleep(1000);
        } else {
            break;
        }
    }

		Sleep(1000);

	while(1){
		system("cls");
		printf("%s, 무엇을 할지 선택하세요. 현재 에너지는 %d입니다.\n", player_name_1, energy[player]);
		Sleep(1000);
		while(1){
			printf("1. 에너지 모으기   2. 공격하기   3. 방어하기\n");
			scanf("%d", &mode[player]);
			if(mode[player] < 1 || mode[player] > 3){
				printf("올바른 모드를 입력하세요!\n");
			} else {
				break;
			}
		}
		if(mode[player] == 1){
			system("cls");
			printf("===========에너지 모으기==========\n");
			Sleep(1000);

			energy[1]++;
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
            printf("공격력을 %d로 설정했습니다. 남은 에너지: %d\n",
				power[player], energy[player]);
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
            printf("방어력을 %d로 설정했습니다. 남은 에너지: %d\n",
				power[player], energy[player]);
            Sleep(1000);
        }

        if(player == 1){
			player = 2;
        } else if (player == 2){
			player = 1;
			battle();
        }
	}
	return 0;
}

