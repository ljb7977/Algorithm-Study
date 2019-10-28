#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define PAUSE 112
#define ESC 27

#define MAP_X 30
#define MAP_Y 20

void show_title(void); //게임 시작화면
void draw_map(void); // 게임판 테두리를 그림
int move(int dir); //뱀머리를 이동
void pause(void); //일시 정지
void game_over(void); //게임 오버를 확인
void make_food(void); // 음식 생성
void game(void);
void show_score(void);

int x[100], y[100]; //몸의 좌표값, 최대 100개
int food_x, food_y; //food의 좌표값
int length; //몸 길이
int speed; //게임 속도
int score; //점수  --reset함수에 의해 초기화됨
int best_score = 0; //최고 점수 --reset함수에 의해 초기화 되지 않음
int dir; //현재 이동 방향
int key; //입력받은 키

void gotoxy(int x, int y, char* s) { //x값을 2x로 변경, 좌표값에 바로 문자열을 입력할 수 있도록 printf함수 삽입
    COORD pos = {2 * x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    printf("%s", s);
}

int main() {
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.bVisible = 0;
    cursorInfo.dwSize = 1;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo); //delete cursor
    srand(time(NULL));

    while(1){
        show_title();
        game();
        game_over();
    }
}

void game()
{
    int is_game_over = 0;
    while (1) {
        if (kbhit()){
            key = getch();
            if(key == 224)
                key = getch();
        }
        Sleep(speed);

        switch (key) { //입력받은 키에 따라 동작을 분류
        case LEFT:
        case RIGHT:
        case UP:
        case DOWN:
            if ((dir == LEFT && key != RIGHT) || (dir == RIGHT && key != LEFT) ||
                (dir == UP && key != DOWN) ||(dir == DOWN && key != UP)) //180도 회전을 방지
                dir = key;
            key = 0; //키 값 reset
            break;
        case ESC:
            exit(0);
        }
        is_game_over = move(dir);
        show_score();
        if(is_game_over == 1)
            break;
    }
}

void show_title(void) {
    while (kbhit())
        getch(); //버퍼에 있는 키값을 버림

    system("cls");
    draw_map();    //맵 테두리를 그림

    gotoxy(MAP_X / 2 - 7, 5, "+--------------------------+");
    gotoxy(MAP_X / 2 - 7, 6, "|   S N A K E    G A M E   |");
    gotoxy(MAP_X / 2 - 7, 7, "+--------------------------+");

    gotoxy(MAP_X / 2 - 7, 13, "   ◇ ←,→,↑,↓ : Move    ");
    gotoxy(MAP_X / 2 - 7, 14, "   ◇ P : Pause             ");
    gotoxy(MAP_X / 2 - 7, 15, "   ◇ ESC : Quit              ");

    while (1) {
        if (kbhit()) {
            key = getch();
            if (key == ESC)
                exit(0); // ESC키면 종료
            else
                break; //다음 화면으로 넘어가기
        }
        gotoxy(MAP_X / 2 - 7, 10, " < PRESS ANY KEY TO START > ");
        Sleep(400);
        gotoxy(MAP_X / 2 - 7, 10, "                            ");
        Sleep(400);
    }

    system("cls"); //화면을 지움
    draw_map(); //맵 테두리를 그림
    while (kbhit())
        getch(); //flush buffer

    dir = LEFT; // 방향 초기화
    speed = 100; // 속도 초기화
    length = 5; //뱀 길이 초기화
    score = 0; //점수 초기화
    int i;
    for (i = 0; i < length; i++) { //뱀 몸통값 입력
        x[i] = MAP_X / 2 + i;
        y[i] = MAP_Y / 2;
        gotoxy(x[i], y[i], "×");
    }
    gotoxy(x[0], y[0], "○"); //뱀 머리 출력
    make_food(); // food 생성
}

void game_over(void) { //게임종료 함수
    gotoxy(MAP_X / 2 - 6, 5, "+----------------------+");
    gotoxy(MAP_X / 2 - 6, 6, "|      GAME OVER..     |");
    gotoxy(MAP_X / 2 - 6, 7, "+----------------------+");
    gotoxy(MAP_X / 2 - 6, 9, "     YOUR SCORE : ");
    printf("%d", score);

    gotoxy(MAP_X / 2 - 7, 12, " Press any key to restart.. ");

    if (score > best_score) {
        best_score = score;
        gotoxy(MAP_X / 2 - 4, 10, "☆ BEST SCORE ☆");
    }
    Sleep(500);
    getch();
}

void draw_map(void) { //맵 테두리 그리는 함수
    int i;
    for (i = 0; i < MAP_X; i++) {
        gotoxy(i, 0, "■");
    }
    for (i = 1; i < MAP_Y - 1; i++) {
        gotoxy(0, i, "■");
        gotoxy(MAP_X - 1, i, "■");
    }
    for (i = 0; i < MAP_X; i++) {
        gotoxy(i, MAP_Y - 1, "■");
    }
}


/*
int move(int dir)
뱀의 몸통을 움직이고, 음식을 만나면 몸의 길이를 늘리며, 자기 자신, 혹은 벽과 충돌한 경우
1을 return하고, 그렇지 않은 경우 0을 return한다.
*/
int move(int dir) {
    int i;

    if (x[0] == 0 || x[0] == MAP_X - 1 || y[0] == 0 || y[0] == MAP_Y - 1) { //벽과 충돌했을 경우
        return 1;
    }
    for (i = 1; i < length; i++) { //자기 몸과 충돌했는가?
        if (x[0] == x[i] && y[0] == y[i]) {
            return 1;
        }
    }

    if (x[0] == food_x && y[0] == food_y) { //food와 충돌했을 경우
        score += 10; //점수 증가
        make_food(); //새로운 food 추가
        length++; //길이증가
        x[length - 1] = x[length - 2]; //새로만든 몸통에 값 입력
        y[length - 1] = y[length - 2];
    } else {
        gotoxy(x[length - 1], y[length - 1], "  "); //몸통 마지막을 지움
    }

    for (i = length - 1; i > 0; i--) { //몸통좌표를 한칸씩 옮김
        x[i] = x[i - 1];
        y[i] = y[i - 1];
    }
    gotoxy(x[0], y[0], "×"); //머리가 있던곳을 몸통으로 고침
    if (dir == LEFT) --x[0]; //방향에 따라 새로운 머리좌표(x[0],y[0])값을 변경
    if (dir == RIGHT) ++x[0];
    if (dir == UP) --y[0];
    if (dir == DOWN) ++y[0];
    gotoxy(x[i], y[i], "○"); //새로운 머리좌표값에 머리를 그림


    return 0;
}

void pause(void) { //일시 정지
    while (1) {
        if (key == PAUSE) {
            gotoxy(MAP_X / 2 - 9, 0, "< PAUSE : PRESS ANY KEY TO RESUME > ");
            Sleep(400);
            gotoxy(MAP_X / 2 - 9, 0, "                                    ");
            Sleep(400);
        }
        else {
            draw_map();
            return;
        }
        if (kbhit()) {
            key = getch();
            if(key == 224){
                key = getch();
            }
        }
    }
}

void make_food(void) {
    int i;
    while (1) {
        food_x = (rand() % (MAP_X - 2)) + 1;
        food_y = (rand() % (MAP_Y - 2)) + 1;

        for (i = 0; i < length; i++) //food가 뱀 몸통과 겹치는지 확인
            if (food_x == x[i] && food_y == y[i])
                break;

        if (i != length)
            continue; //겹쳤을 경우 while문을 다시 시작

        gotoxy(food_x, food_y, "☆"); //안겹쳤을 경우 좌표값에 food를 찍고
        speed -= 3; //속도 증가
        break;
    }
}

void show_score()
{
    gotoxy(5, MAP_Y, " YOUR SCORE: "); //점수표시
    printf("%3d, BEST SCORE: %3d", score, best_score);
}
