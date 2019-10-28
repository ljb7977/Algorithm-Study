#include <stdio.h>
#include <stdlib.h>

typedef struct student
{
    char name[10];
    int age;
    int gender;
    int year;
    int class;
    float score;
    int valid;
} Student;

Student s[100];

void printStudent(int i)
{
    printf("----학생 정보----\n");
    printf("출석번호 %d번\n", i);
    printf("이름: %s\n", s[i].name);
    printf("나이: %d\n", s[i].age);
    if(s[i].gender == 1)
    {
        printf("성별: 남자\n");
    }
    else
    {
        printf("성별: 여자\n");
    }
    printf("%d학년 %d반\n", s[i].year, s[i].class);
    printf("성적: %.2f\n", s[i].score);
    printf("-----------------\n");
}

void modifyStudent()
{
    int num, mode;
    printf("수정할 학생 번호를 입력하세요\n");
    scanf("%d", &num);
    if(s[num].valid == 0)
    {
        printf("존재하지 않는 학생입니다.\n");
        return;
    }
    printStudent(num);
    printf("수정할 항목을 고르세요\n");
    printf("1:이름  2:나이  3:성별  4:학년  5:반  6:점수\n");
    scanf("%d", &mode);
    if(mode == 1) {
        printf("수정할 이름을 입력하세요\n");
        scanf("%s", s[num].name);
    }
    else if (mode == 2) {
        printf("수정할 나이를 입력하세요\n");
        scanf("%d", &s[num].age);
    }
    else if (mode == 3) {
        printf("수정할 성별을 입력하세요. 남자는 1, 여자는 2\n");
        scanf("%d", &s[num].gender);
    }
    else if (mode == 4) {
        printf("수정할 학년을 입력하세요.\n");
        scanf("%d", &s[num].year);
    }
    else if (mode == 5) {
        printf("수정할 반을 입력하세요.\n");
        scanf("%d", &s[num].class);
    }
    else if (mode == 6) {
        printf("수정할 점수를 입력하세요.\n");
        scanf("%f", &s[num].score);
    }
    else {
        printf("잘못된 모드입니다.\n");
        return;
    }
    printf("수정된 정보입니다.\n");
    printStudent(num);
}

int main()
{
    char command;
    int i;
    int num;
    int mode, temp;
    printf("학생 관리 시스템\n");
    while(1){
        printf("커맨드를 입력하세요.\n");
        printf("q: 종료  i: 추가  d: 삭제  m: 수정\n");
        printf("a: 전체 출력  p: 한 학생 출력\n");
        scanf("%c", &command);
        switch(command) {
        case 'q':
            printf("프로그램을 종료합니다.\n");
            return 0;
        case 'i':
            printf("입력할 학생 번호를 입력하세요\n");
            scanf("%d", &num);
            if(s[num].valid == 1){
                printf("이미 등록된 학생입니다.\n");
                break;
            }
            printf("%d번 학생\n", num);
            printf("이름을 입력하세요: ");
            scanf("%s", s[num].name);
            printf("나이를 입력하세요: ");
            scanf("%d", &s[num].age);
            printf("성별을 입력하세요. 남자는 1, 여자는 2: ");
            scanf("%d", &s[num].gender);
            printf("학년을 입력하세요: ");
            scanf("%d", &s[num].year);
            printf("반을 입력하세요: ");
            scanf("%d", &s[num].class);
            printf("성적을 입력하세요: ");
            scanf("%f", &s[num].score);

            s[num].valid = 1;
            printf("학생이 등록되었습니다.\n");
            printStudent(num);
            break;
        case 'd':
            printf("삭제할 학생 번호를 입력하세요.\n");
            scanf("%d", &num);
            if(s[num].valid == 0){
                printf("존재하지 않는 학생입니다.\n");
                break;
            }
            printStudent(num);
            s[num].valid = 0;
            printf("학생을 삭제했습니다.\n");
            break;
        case 'm':
            modifyStudent();
            break;
        case 'a':
            printf("전체 학생 정보를 출력합니다.\n");
            for(i = 0; i<100; i++)
                if(s[i].valid == 1)
                    printStudent(i);
            break;
        case 'p':
            printf("출력할 학생 번호를 입력하세요\n");
            scanf("%d", &num);
            if(s[num].valid == 0){
                printf("존재하지 않는 학생입니다.\n");
                break;
            }
            printStudent(num);
            break;
        default:
            printf("잘못된 커맨드입니다.\n");
        }
        getchar();
    }
    return 0;
}
