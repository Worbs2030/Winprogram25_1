#include <stdio.h>
#include <windows.h>

// 아스키 코드로 배경 색상 설정
void setBackgroundColor(int color) {
    printf("\033[42m", color); // 48;5는 256색 팔레트를 사용하기 위한 코드
}

// 색상 초기화
resetColor() {
    printf("\033[0m");  // 색상 초기화
}

// 커서 위치 조정
void gotoxy(int x, int y) {
    COORD Cur;
    Cur.X = x;
    Cur.Y = y;
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, Cur);  // 커서 이동
}

// 윈도우의 속성을 나타내는 구조체
struct Window {
    int width;  // 윈도우의 너비
    int height; // 윈도우의 높이
    int posX;   // 윈도우의 X 좌표
    int posY;   // 윈도우의 Y 좌표
    char name[30]; // 윈도우 이름
    int color;  // 윈도우 색상 (ANSI 색상 코드)
};

// 윈도우를 그리는 함수
void drawWindow(struct Window win) {
    // 윈도우 색상 설정
    printf("\033[%dm", win.color); // 색상 설정

    // 윈도우 창 상단 그리기
    gotoxy(win.posX, win.posY);
    printf("--------------------");

    // 윈도우 창 중간선 그리기 (윗 선에서 2칸 떨어져서 중간선)
    for (int i = win.posY + 1; i < win.posY + win.height - 1; i++) {
        gotoxy(win.posX, i);
        if (i == win.posY + 2) { // 윗 선에서 2칸 떨어져서 중간선
            printf("|------------------|");
        }
        else {
            printf("|                  |");
        }
    }

    // 윈도우 창 하단 그리기
    gotoxy(win.posX, win.posY + win.height - 1);
    printf("--------------------");

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
    int i, j;
    for (i = 0; i < 24; i++) {  // 화면의 높이 (여기서는 30줄로 설정)
        for (j = 0; j < 120; j++) {  // 화면의 너비 (여기서는 120칸으로 설정)
            printf(" ");  // 화면을 색으로 채운다
        }
        printf("\n");  // 줄바꿈
    }

    resetColor();  // 색상 초기화
}

int main() {
    // 초록색 배경을 프롬프트 화면에 채우기
    fillBackground(2);  // 2는 초록색 배경 (ANSI 256색 팔레트에서)

    // 윈도우 창의 속성 설정
    struct Window win1 = { 20, 7, 10, 3, "Window 1", 41 }; // 빨간색 배경 (41)
    struct Window win2 = { 20, 7, 15, 5, "Window 2", 44 }; // 파란색 배경 (44)

    // 윈도우 1 그리기
    drawWindow(win1);

    // 윈도우 2 그리기
    drawWindow(win2);

    gotoxy(10, 24);  // 커서를 화면 하단으로 이동

    return 0;
}