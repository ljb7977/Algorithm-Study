#include <stdio.h>
#include <stdlib.h>

int main()
{
    int score[100] = {0,};
    int used[100] = {0,};
    int mode, i;
    int student, temp;
    int num;
    double sum;

    while(1){
        printf("성적 관리 프로그램입니다. 모드를 선택해주세요.\n");
        printf("1. 입력 및 수정  2. 전체 출력  3. 평균  4. 최고점  5. 최저점  6. 종료\n");
        scanf("%d", &mode);
        switch(mode){
        case 1:
            printf("입력할 학생 번호와 점수를 입력하세요\n");
            scanf("%d %d", &student, &temp);
            score[student] = temp;
            used[student] = 1;
            break;
        case 2:
            printf("전체 학생 성적을 출력합니다.\n");
            for(i = 0; i<100; i++){
                if(used[i]){
                    printf("%d : %d\n", i, score[i]);
                }
            }
            break;
        case 3:
            printf("평균 점수를 출력합니다.\n");
            sum = 0;
            num = 0;
            for(i = 0; i<100; i++){
                if(used[i]){
                    sum += score[i];
                    num++;
                }
            }
            printf("%.2f\n", sum/num);
            break;
        case 4:
            printf("최고 점수를 출력합니다.\n");
            temp = 0;
            for(i = 1; i<100; i++){
                if(used[i]){
                    if(score[i] > score[temp]){
                        temp = i;
                    }
                }
            }
            printf("%d번 %d점\n", temp, score[temp]);
            break;
        case 5:
            printf("최저 점수를 출력합니다.\n");
            temp = 0;
            for(i = 1; i<100; i++){
                if(used[i]){
                    if(score[i] < score[temp]){
                        temp = i;
                    }
                }
            }
            printf("%d번 %d점\n", temp, score[temp]);
            break;
        case 6:
            printf("프로그램을 종료합니다.\n");
            return 0;
        }
    }

    return 0;
}
