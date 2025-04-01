#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>

void gotoxy(int x, int y)
{
    COORD Cur;
    Cur.X = x;
    Cur.Y = y;
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, Cur);
}

void drawWindow(int width, int height)
{
    // 윗부분 경계 그리기 (수평선)
    for (int i = 0; i < width; i++) {
        gotoxy(i, 0);   
        printf("-");
    }

    // 두 번째 수평선 그리기 (윗부분과 바로 연결되도록)
    for (int i = 0; i < width; i++) {
        gotoxy(i, 2);
        printf("-");
    }

    // 왼쪽과 오른쪽 경계 그리기 (수평선 양 옆에 수직선 추가)
    for (int i = 0; i < height - 1; i++) {
        gotoxy(0, i);
        printf("|");

        gotoxy(width - 1, i); 
        printf("|");
    }

    for (int i = 0; i < width; i++) {
        gotoxy(i, height - 1);  
        printf("-");
    }
}

int main()
{
    int width, height;

    printf("가로 길이를 입력하세요: ");
    while (scanf("%d", &width) != 1) {  
        printf("잘못된 입력입니다. 정수를 입력하세요: ");
        while (getchar() != '\n');  
    }

    printf("세로 길이를 입력하세요: ");
    while (scanf("%d", &height) != 1) {  
        printf("잘못된 입력입니다. 정수를 입력하세요: ");
        while (getchar() != '\n');  
    }

    system("cls");

    drawWindow(width, height);

    return 0;
}