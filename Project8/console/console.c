#include <stdio.h>
#include <windows.h>

// ȭ�� ũ�⸦ �����ϱ� ���� ��ũ�� ����
#define SCREEN_WIDTH 120
#define SCREEN_HEIGHT 25

// �ƽ�Ű �ڵ�� ��� ���� ����
void setBackgroundColor(int color) {
    printf("\033[42m", color);
}

// ���� �ʱ�ȭ
void resetColor() {
    printf("\033[0m");  // ���� �ʱ�ȭ
}

// Ŀ�� ��ġ ����
void gotoxy(int x, int y) {
    COORD Cur;
    Cur.X = x;
    Cur.Y = y;
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, Cur);
}

// �������� �Ӽ��� ��Ÿ���� ����ü
typedef struct {
    int width;  // �������� �ʺ�
    int height; // �������� ����
    int posX;   // �������� X ��ǥ
    int posY;   // �������� Y ��ǥ
    char name[30]; // ������ �̸�
    int color;  // ������ ���� (ANSI ���� �ڵ�)
} Window;

// �����츦 �׸��� �Լ�
void drawWindow(Window win) {
    // ������ ���� ����
    printf("\033[%dm", win.color); // ���� ����

    // ������ â �׸���
    for (int i = win.posY; i < win.posY + win.height; i++) {
        gotoxy(win.posX, i);

        // �������� ���, �߰�, �ϴ��� �׸� ��
        if (i == win.posY) {
            // ���
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
            // �ϴ�
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
            // �߰�
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

    // �̸� ���
    gotoxy(win.posX + 1, win.posY + 1);
    printf("%s", win.name);

    // ���� �ʱ�ȭ
    printf("\033[0m");  // ���� �ʱ�ȭ
}

// �ʷϻ� ����� ������Ʈ ��ü�� ä��� �Լ�
void fillBackground(int color) {
    system("cls");  // ȭ���� ����
    setBackgroundColor(color);  // ���� ����

    // �ܼ� ȭ���� ä��� ����
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        for (int j = 0; j < SCREEN_WIDTH; j++) {
            printf(" ");  // ȭ���� ������ ä���
        }
        printf("\n");  // �ٹٲ�
    }

    resetColor();  // ���� �ʱ�ȭ
}

int main() {
    // �ʷϻ� ����� ������Ʈ ȭ�鿡 ä���
    fillBackground("\033[42m");  // 2�� �ʷϻ� ��� (ANSI 256�� �ȷ�Ʈ����)

    // ������ â�� �Ӽ� ����
    Window win1 = { 20, 7, 10, 3, "����� ������ â 1", 41 }; // ������ ��� (41)
    Window win2 = { 20, 7, 15, 5, "����� ������ â 2", 44 }; // �Ķ��� ��� (44)

    // ������ 1 �׸���
    drawWindow(win1);

    // ������ 2 �׸���
    drawWindow(win2);

    gotoxy(10, 25);

    return 0;
}
