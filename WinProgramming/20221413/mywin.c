// mywin.c
#include <windows.h>
#include <stdio.h>
#include "mywin.h"

// 콘솔 너비 (컬럼 수)를 구하는 함수
int getConsoleWidth(void) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        return csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }
    return -1;  // 실패 시
}

// 콘솔 높이 (줄 수)를 구하는 함수
int getConsoleHeight(void) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }
    return -1;  // 실패 시
}

// 커서 이동 함수: \033[row;colH
void move_cursor(int row, int col) {
    printf("\033[%d;%dH", row, col);
}
