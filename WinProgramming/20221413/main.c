#include <stdio.h>
#include <windows.h>

// �ܼ� ȭ�� ũ�� ���� (���ϴ� ������ ���� ����)
#define SCREEN_WIDTH 120
#define SCREEN_HEIGHT 30

// ���� ����
#define MARGIN_LEFT 5
#define MARGIN_RIGHT 5
#define MARGIN_TOP 1
#define MARGIN_BOTTOM 3

// ���� ������ ���� ANSI �ڵ�
void setBackgroundColor(int color) {
    printf("\033[48;5;%dm", color);  // 48;5;color -> 256�� ANSI ���� ����
}

// ���� ���� ������ ���� ANSI �ڵ�
void setTextColor(int color) {
    printf("\033[38;5;%dm", color);  // 38;5;color -> 256�� ANSI �ؽ�Ʈ ���� ����
}

// ���� �ʱ�ȭ
void resetColor() {
    printf("\033[0m");  // ���� �ʱ�ȭ
}

// Ŀ�� ��ġ ���� �Լ�
void gotoxy(int x, int y) {
    printf("\033[%d;%dH", y + 1, x + 1);  // ANSI �ڵ�� Ŀ�� ��ġ �̵� (1 ���)
}

// �ܼ� ����� �Ķ������� ä��� �Լ�
void fillBlueArea() {
    setBackgroundColor(32);  // �Ķ��� ��� (32�� �Ķ��� ANSI �ڵ�)

    // ������ ������ ������ �Ķ������� ä���
    for (int row = MARGIN_TOP; row < SCREEN_HEIGHT - MARGIN_BOTTOM; row++) {
        gotoxy(MARGIN_LEFT, row);
        for (int col = MARGIN_LEFT; col < SCREEN_WIDTH - MARGIN_RIGHT; col++) {
            printf(" ");  // �Ķ������� ȭ���� ä���
        }
    }

    resetColor();  // ���� �ʱ�ȭ (�⺻ �������� �ʱ�ȭ)
}

int main() {
    POINT mousePos;  // ���콺 ��ġ
    int lastX = -1, lastY = -1;  // ������ ��µ� '+' ��ġ ����
    int isClicked = 0;  // ���콺 Ŭ�� ���� (0: Ŭ�� �ȵ�, 1: Ŭ����)

    // �ܼ� ȭ�� �ʱ�ȭ
    system("cls");  // ȭ���� ����� �ٽ� �׸���

    // �Ķ��� ��� ä���
    fillBlueArea();

    while (1) {
        // ���� ���콺 ��ġ ��������
        GetCursorPos(&mousePos);

        // ���콺 ��ǥ�� ������ ����� �Ķ��� ��� ���� �ִ��� Ȯ��
        int x = (mousePos.x / 8) - MARGIN_LEFT;  // x ��ǥ�� 8�� ������ ��������� ����
        int y = (mousePos.y / 19) - MARGIN_TOP;  // y ��ǥ�� 19�� ������ ��������� ����

        // �Ķ��� ��� ���� �������� ���콺 ��ǥ�� ��ȿ�ϵ��� ����
        if (x < 0) x = 0;
        if (y < 0) y = 0;
        if (x >= (SCREEN_WIDTH - MARGIN_LEFT - MARGIN_RIGHT)) x = SCREEN_WIDTH - MARGIN_LEFT - MARGIN_RIGHT - 1;
        if (y >= (SCREEN_HEIGHT - MARGIN_TOP - MARGIN_BOTTOM)) y = SCREEN_HEIGHT - MARGIN_TOP - MARGIN_BOTTOM - 1;

        // ���콺 Ŭ�� ���� ���� (���� Ŭ��)
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
            isClicked = 1;  // Ŭ�� ����
        }
        else {
            isClicked = 0;  // Ŭ�� �ȵ�
        }

        // ȭ���� �����ϱ� ���� �Ķ��� ����� ����
        fillBlueArea(); // �Ķ��� ����� �����༭ ������ ����

        // ���� ��ġ�� �ִ� '+' ����� (���� ��ġ�� ������ ���)
        if (lastX != -1 && lastY != -1) {
            gotoxy(lastX + MARGIN_LEFT, lastY + MARGIN_TOP);  // ���� ��ġ�� Ŀ�� �̵�
            printf(" ");  // �������� ������
        }

        // ���� ��ġ�� '+' ���
        gotoxy(x + MARGIN_LEFT, y + MARGIN_TOP);

        // Ŭ�� ���¿� ���� ���� ����
        if (isClicked) {
            setTextColor(11);  // ����� (11�� ����� ANSI �ڵ�)
        }
        else {
            setTextColor(0);  // ������ (0�� �⺻ ������ ANSI �ڵ�)
        }

        printf("+");

        // ���� ��ǥ ����
        lastX = x;
        lastY = y;

        // ���� ����: ESC Ű�� ������ ���α׷� ����
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            break;
        }

        Sleep(10); // 10ms ���
    }

    return 0;
}
