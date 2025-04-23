// mywin.c
#include <windows.h>
#include <stdio.h>
#include "mywin.h"

// �ܼ� �ʺ� (�÷� ��)�� ���ϴ� �Լ�
int getConsoleWidth(void) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        return csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }
    return -1;  // ���� ��
}

// �ܼ� ���� (�� ��)�� ���ϴ� �Լ�
int getConsoleHeight(void) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }
    return -1;  // ���� ��
}

// Ŀ�� �̵� �Լ�: \033[row;colH
void move_cursor(int row, int col) {
    printf("\033[%d;%dH", row, col);
}
