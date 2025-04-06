#include <stdio.h>
#include <windows.h>

// �ƽ�Ű �ڵ�� ��� ���� ����
void setBackgroundColor(int color) {
    printf("\033[42m", color); // 48;5�� 256�� �ȷ�Ʈ�� ����ϱ� ���� �ڵ�
}

// ���� �ʱ�ȭ
resetColor() {
    printf("\033[0m");  // ���� �ʱ�ȭ
}

// Ŀ�� ��ġ ����
void gotoxy(int x, int y) {
    COORD Cur;
    Cur.X = x;
    Cur.Y = y;
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, Cur);  // Ŀ�� �̵�
}

// �������� �Ӽ��� ��Ÿ���� ����ü
struct Window {
    int width;  // �������� �ʺ�
    int height; // �������� ����
    int posX;   // �������� X ��ǥ
    int posY;   // �������� Y ��ǥ
    char name[30]; // ������ �̸�
    int color;  // ������ ���� (ANSI ���� �ڵ�)
};

// �����츦 �׸��� �Լ�
void drawWindow(struct Window win) {
    // ������ ���� ����
    printf("\033[%dm", win.color); // ���� ����

    // ������ â ��� �׸���
    gotoxy(win.posX, win.posY);
    printf("--------------------");

    // ������ â �߰��� �׸��� (�� ������ 2ĭ �������� �߰���)
    for (int i = win.posY + 1; i < win.posY + win.height - 1; i++) {
        gotoxy(win.posX, i);
        if (i == win.posY + 2) { // �� ������ 2ĭ �������� �߰���
            printf("|------------------|");
        }
        else {
            printf("|                  |");
        }
    }

    // ������ â �ϴ� �׸���
    gotoxy(win.posX, win.posY + win.height - 1);
    printf("--------------------");

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
    int i, j;
    for (i = 0; i < 24; i++) {  // ȭ���� ���� (���⼭�� 30�ٷ� ����)
        for (j = 0; j < 120; j++) {  // ȭ���� �ʺ� (���⼭�� 120ĭ���� ����)
            printf(" ");  // ȭ���� ������ ä���
        }
        printf("\n");  // �ٹٲ�
    }

    resetColor();  // ���� �ʱ�ȭ
}

int main() {
    // �ʷϻ� ����� ������Ʈ ȭ�鿡 ä���
    fillBackground(2);  // 2�� �ʷϻ� ��� (ANSI 256�� �ȷ�Ʈ����)

    // ������ â�� �Ӽ� ����
    struct Window win1 = { 20, 7, 10, 3, "Window 1", 41 }; // ������ ��� (41)
    struct Window win2 = { 20, 7, 15, 5, "Window 2", 44 }; // �Ķ��� ��� (44)

    // ������ 1 �׸���
    drawWindow(win1);

    // ������ 2 �׸���
    drawWindow(win2);

    gotoxy(10, 24);  // Ŀ���� ȭ�� �ϴ����� �̵�

    return 0;
}