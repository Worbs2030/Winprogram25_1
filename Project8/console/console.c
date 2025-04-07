#include <stdio.h>
#include <windows.h>

// 화면 크기를 설정하기 위한 매크로 정의
#define SCREEN_WIDTH 120
#define SCREEN_HEIGHT 25

// 아스키 코드로 배경 색상 설정
void setBackgroundColor(int color) {
    printf("\033[42m", color);
}

// 색상 초기화
void resetColor() {
    printf("\033[0m");  // 색상 초기화
}

// 커서 위치 조정
void gotoxy(int x, int y) {
    COORD Cur;
    Cur.X = x;
    Cur.Y = y;
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, Cur);
}

// 윈도우의 속성을 나타내는 구조체
typedef struct {
    int width;  // 윈도우의 너비
    int height; // 윈도우의 높이
    int posX;   // 윈도우의 X 좌표
    int posY;   // 윈도우의 Y 좌표
    char name[30]; // 윈도우 이름
    int color;  // 윈도우 색상 (ANSI 색상 코드)
} Window;

// 윈도우를 그리는 함수
void drawWindow(Window win) {
    // 윈도우 색상 설정
    printf("\033[%dm", win.color); // 색상 설정

    // 윈도우 창 그리기
    for (int i = win.posY; i < win.posY + win.height; i++) {
        gotoxy(win.posX, i);

        // 윈도우의 상단, 중간, 하단을 그릴 때
        if (i == win.posY) {
            // 상단
            for (int j = 0; j < win.width; j++) {
                if (j == 0 || j == win.width - 1) {
                    printf("|");
                }
                else {
                    printf("-");
                }
            }
        }
        else if (i == win.posY + win.height - 1) {
            // 하단
            for (int j = 0; j < win.width; j++) {
                if (j == 0 || j == win.width - 1) {
                    printf("|");
                }
                else {
                    printf("-");
                }
            }
        }
        else if (i == win.posY + 2) {
            for (int j = 0; j < win.width; j++) {
                if (j == 0 || j == win.width - 1) {
                    printf("|");
                }
                else if (j >= 2 && j <= win.width - 3) {
                    printf("-");
                }
                else {
                    printf(" ");
                }
            }
        }
        else {
            // 중간
            for (int j = 0; j < win.width; j++) {
                if (j == 0 || j == win.width - 1) {
                    printf("|");
                }
                else {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }

    // 이름 출력
    gotoxy(win.posX + 1, win.posY + 1);
    printf("%s", win.name);

    // 색상 초기화
    printf("\033[0m");  // 색상 초기화
}

// 초록색 배경을 프롬프트 전체에 채우는 함수
void fillBackground(int color) {
    system("cls");  // 화면을 지움
    setBackgroundColor(color);  // 배경색 설정

    // 콘솔 화면을 채우는 루프
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        for (int j = 0; j < SCREEN_WIDTH; j++) {
            printf(" ");  // 화면을 색으로 채운다
        }
        printf("\n");  // 줄바꿈
    }

    resetColor();  // 색상 초기화
}

int main() {
    // 초록색 배경을 프롬프트 화면에 채우기
    fillBackground("\033[42m");  // 2는 초록색 배경 (ANSI 256색 팔레트에서)

    // 윈도우 창의 속성 설정
    Window win1 = { 20, 7, 10, 3, "재균의 윈도우 창 1", 41 }; // 빨간색 배경 (41)
    Window win2 = { 20, 7, 15, 5, "재균의 윈도우 창 2", 44 }; // 파란색 배경 (44)

    // 윈도우 1 그리기
    drawWindow(win1);

    // 윈도우 2 그리기
    drawWindow(win2);

    gotoxy(10, 25);

    return 0;
}
