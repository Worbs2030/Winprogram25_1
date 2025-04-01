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
    // ���κ� ��� �׸��� (����)
    for (int i = 0; i < width; i++) {
        gotoxy(i, 0);   
        printf("-");
    }

    // �� ��° ���� �׸��� (���κа� �ٷ� ����ǵ���)
    for (int i = 0; i < width; i++) {
        gotoxy(i, 2);
        printf("-");
    }

    // ���ʰ� ������ ��� �׸��� (���� �� ���� ������ �߰�)
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

    printf("���� ���̸� �Է��ϼ���: ");
    while (scanf("%d", &width) != 1) {  
        printf("�߸��� �Է��Դϴ�. ������ �Է��ϼ���: ");
        while (getchar() != '\n');  
    }

    printf("���� ���̸� �Է��ϼ���: ");
    while (scanf("%d", &height) != 1) {  
        printf("�߸��� �Է��Դϴ�. ������ �Է��ϼ���: ");
        while (getchar() != '\n');  
    }

    system("cls");

    drawWindow(width, height);

    return 0;
}