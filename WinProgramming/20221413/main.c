#include <stdio.h>
#include <windows.h>

// 콘솔 화면 크기 설정 (원하는 값으로 조절 가능)
#define SCREEN_WIDTH 120
#define SCREEN_HEIGHT 30

// 여백 정의
#define MARGIN_LEFT 5
#define MARGIN_RIGHT 5
#define MARGIN_TOP 1
#define MARGIN_BOTTOM 3

// 배경색 설정을 위한 ANSI 코드
void setBackgroundColor(int color) {
    printf("\033[48;5;%dm", color);  // 48;5;color -> 256색 ANSI 배경색 설정
}

// 글자 색상 설정을 위한 ANSI 코드
void setTextColor(int color) {
    printf("\033[38;5;%dm", color);  // 38;5;color -> 256색 ANSI 텍스트 색상 설정
}

// 색상 초기화
void resetColor() {
    printf("\033[0m");  // 색상 초기화
}

// 커서 위치 설정 함수
void gotoxy(int x, int y) {
    printf("\033[%d;%dH", y + 1, x + 1);  // ANSI 코드로 커서 위치 이동 (1 기반)
}

// 콘솔 배경을 파란색으로 채우는 함수
void fillBlueArea() {
    setBackgroundColor(32);  // 파란색 배경 (32는 파란색 ANSI 코드)

    // 여백을 제외한 구간을 파란색으로 채우기
    for (int row = MARGIN_TOP; row < SCREEN_HEIGHT - MARGIN_BOTTOM; row++) {
        gotoxy(MARGIN_LEFT, row);
        for (int col = MARGIN_LEFT; col < SCREEN_WIDTH - MARGIN_RIGHT; col++) {
            printf(" ");  // 파란색으로 화면을 채운다
        }
    }

    resetColor();  // 색상 초기화 (기본 배경색으로 초기화)
}

int main() {
    POINT mousePos;  // 마우스 위치
    int lastX = -1, lastY = -1;  // 이전에 출력된 '+' 위치 추적
    int isClicked = 0;  // 마우스 클릭 상태 (0: 클릭 안됨, 1: 클릭됨)

    // 콘솔 화면 초기화
    system("cls");  // 화면을 지우고 다시 그리기

    // 파란색 배경 채우기
    fillBlueArea();

    while (1) {
        // 현재 마우스 위치 가져오기
        GetCursorPos(&mousePos);

        // 마우스 좌표가 여백을 고려한 파란색 배경 내에 있는지 확인
        int x = (mousePos.x / 8) - MARGIN_LEFT;  // x 좌표는 8로 나누어 비례적으로 맞춤
        int y = (mousePos.y / 19) - MARGIN_TOP;  // y 좌표는 19로 나누어 비례적으로 맞춤

        // 파란색 배경 영역 내에서만 마우스 좌표가 유효하도록 제한
        if (x < 0) x = 0;
        if (y < 0) y = 0;
        if (x >= (SCREEN_WIDTH - MARGIN_LEFT - MARGIN_RIGHT)) x = SCREEN_WIDTH - MARGIN_LEFT - MARGIN_RIGHT - 1;
        if (y >= (SCREEN_HEIGHT - MARGIN_TOP - MARGIN_BOTTOM)) y = SCREEN_HEIGHT - MARGIN_TOP - MARGIN_BOTTOM - 1;

        // 마우스 클릭 상태 감지 (왼쪽 클릭)
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
            isClicked = 1;  // 클릭 상태
        }
        else {
            isClicked = 0;  // 클릭 안됨
        }

        // 화면을 갱신하기 전에 파란색 배경을 덮음
        fillBlueArea(); // 파란색 배경을 덮어줘서 구멍을 막음

        // 이전 위치에 있던 '+' 지우기 (이전 위치에 공백을 출력)
        if (lastX != -1 && lastY != -1) {
            gotoxy(lastX + MARGIN_LEFT, lastY + MARGIN_TOP);  // 이전 위치로 커서 이동
            printf(" ");  // 공백으로 덮어줌
        }

        // 현재 위치에 '+' 출력
        gotoxy(x + MARGIN_LEFT, y + MARGIN_TOP);

        // 클릭 상태에 따라 색상 변경
        if (isClicked) {
            setTextColor(11);  // 노란색 (11은 노란색 ANSI 코드)
        }
        else {
            setTextColor(0);  // 검정색 (0은 기본 검정색 ANSI 코드)
        }

        printf("+");

        // 이전 좌표 갱신
        lastX = x;
        lastY = y;

        // 종료 조건: ESC 키를 누르면 프로그램 종료
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            break;
        }

        Sleep(10); // 10ms 대기
    }

    return 0;
}
