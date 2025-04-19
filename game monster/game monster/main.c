#include <stdio.h>
#include <stdlib.h>

#define WIDTH 20   // 화면의 너비
#define HEIGHT 10  // 화면의 높이
#define MAX_MOVE 5 // 몬스터가 이동할 수 있는 최대 범위

// 몬스터 구조체
typedef struct {
    int x;  // 몬스터의 x 좌표
    int y;  // 몬스터의 y 좌표
} Monster;

// 화면을 초기화하고 빈 공간으로 채우는 함수
void clearScreen() {
    // 콘솔에서 화면을 지우는 명령어
    // Unix/Linux/MacOS에서 작동: system("clear");
    // Windows에서 작동: system("cls");
    printf("\033[H\033[J");
}

// 화면에 몬스터와 배경을 출력하는 함수
void drawMonster(Monster monster) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            // 몬스터가 있는 위치에만 #을 출력
            if (x == monster.x && y == monster.y) {
                printf("#");
            }
            else {
                printf(".");
            }
        }
        printf("\n");
    }
}

// 몬스터를 랜덤하게 이동시키는 함수
void moveMonster(Monster* monster) {
    // 몬스터가 이동할 수 있는 범위 (좌우로 최대 MAX_MOVE 만큼 이동)
    int move_x = (rand() % (2 * MAX_MOVE + 1)) - MAX_MOVE;  // -5 ~ 5 사이의 랜덤값
    int move_y = (rand() % (2 * MAX_MOVE + 1)) - MAX_MOVE;  // -5 ~ 5 사이의 랜덤값

    // 이동 후 좌표가 화면 범위를 벗어나지 않도록 제한
    monster->x += move_x;
    monster->y += move_y;

    // 화면 범위를 벗어나지 않도록 좌표를 조정
    if (monster->x < 0) monster->x = 0;
    if (monster->x >= WIDTH) monster->x = WIDTH - 1;
    if (monster->y < 0) monster->y = 0;
    if (monster->y >= HEIGHT) monster->y = HEIGHT - 1;
}

int main() {
    Monster myMonster = { WIDTH / 2, HEIGHT / 2 };  // 초기 위치는 화면의 중앙

    while (1) {
        clearScreen();  // 화면을 지움
        drawMonster(myMonster);  // 몬스터를 화면에 출력
        moveMonster(&myMonster);  // 몬스터를 랜덤하게 이동
        usleep(500000);  // 0.5초 대기 (500,000 마이크로초)
    }

    return 0;
}
