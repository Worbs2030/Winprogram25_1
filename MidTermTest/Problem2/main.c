#include <stdio.h>
#include <string.h>

#define LEFT_RIGHT_MARGIN 2
#define TOP_BOTTOM_MARGIN 1
#define TASKBAR_HEIGHT 1

// ANSI ��� �� (0~7)
const char* bgColors[] = {
    "\033[40m", // 0: Black
    "\033[41m", // 1: Red
    "\033[42m", // 2: Green
    "\033[43m", // 3: Yellow
    "\033[44m", // 4: Blue
    "\033[45m", // 5: Magenta
    "\033[46m", // 6: Cyan
    "\033[47m"  // 7: White
};

// ���� �׵θ� �׸���
void drawDottedLine(int length) {
    for (int i = 0; i < length; i++) {
        if (i % 2 == 0) {
            printf("-");
        }
        else {
            printf(" ");
        }
    }
}

// ������ �׸��� �Լ�
void drawConsoleWindow(int startX, int startY, int width, int height, const char* title, int color) {
    for (int row = 0; row < height; row++) {
        // Ŀ�� ��ġ ����
        printf("\033[%d;%dH", startY + row, startX);

        // ������ ��� (���� ����)
        if (row == 0) {
            printf("%s", bgColors[color % 8]);
            for (int col = 0; col < width; col++) {
                if (col == 0 || col == width - 1) {
                    printf("|");
                }
                else {
                    drawDottedLine(1); // ����
                }
            }
            printf("\033[0m");
        }
        else if (row == 1) {
            // ������ ����� X ��ư
            printf("%s", bgColors[color % 8]);
            int titleLen = strlen(title);
            // ���� ���� ��ġ�� �� �������� ����
            int titleStart = (width - titleLen - 5) / 2 - 7; // -7�� ������ �������� �� �̵�

            for (int col = 0; col < width; col++) {
                if (col == titleStart) {
                    printf("%s", title);
                    col += titleLen - 1;
                }
                // X ��ư ��ġ (������ ������ 3ĭ)
                else if (col == width - 4) {
                    printf("\033[41m\033[97m X \033[0m%s", bgColors[color % 8]); // ���� ����, ��� ����
                    col += 2;
                }
                else {
                    printf(" ");
                }
            }
            printf("\033[0m");
        }
        else if (row == height - 1) {
            // �ϴ�
            printf("%s", bgColors[color % 8]);
            for (int col = 0; col < width; col++) {
                if (col == 0 || col == width - 1) {
                    printf("|");
                }
                else {
                    drawDottedLine(1); // ����
                }
            }
            printf("\033[0m");
        }
        else {
            // �߰� �κ�
            printf("%s", bgColors[color % 8]);
            for (int col = 0; col < width; col++) {
                if (col == 0 || col == width - 1) {
                    printf("|");
                }
                else {
                    printf(" ");
                }
            }
            printf("\033[0m");
        }
    }
}

// ��� �׸��� �Լ�
void DrawBG(int width, int height) {
    int total_width = width + LEFT_RIGHT_MARGIN * 1;
    int total_height = height + TOP_BOTTOM_MARGIN * 1 + TASKBAR_HEIGHT;

    for (int row = 0; row < total_height; row++) {
        if (row < TOP_BOTTOM_MARGIN) {
            for (int col = 0; col < total_width; col++) {
                printf(" ");
            }
        }
        else if (row < TOP_BOTTOM_MARGIN + height) {
            for (int col = 0; col < LEFT_RIGHT_MARGIN; col++) {
                printf(" ");
            }
            printf("\033[44m"); // �Ķ� ���
            for (int col = 0; col < width; col++) {
                printf(" ");
            }
            printf("\033[0m");
            for (int col = 0; col < LEFT_RIGHT_MARGIN; col++) {
                printf(" ");
            }
        }
        else {
            for (int col = 0; col < LEFT_RIGHT_MARGIN; col++) {
                printf(" ");
            }
            printf("\033[100m"); // ��ο� ȸ�� (�۾�ǥ����)
            for (int col = 0; col < width; col++) {
                printf(" ");
            }
            printf("\033[0m");
            for (int col = 0; col < LEFT_RIGHT_MARGIN; col++) {
                printf(" ");
            }
        }
        printf("\n");
    }
}

int main() {
    int width = 80 - LEFT_RIGHT_MARGIN * 1;
    int height = 25 - TOP_BOTTOM_MARGIN * 1 - TASKBAR_HEIGHT;

    // ��� �׸���
    DrawBG(width, height);

    // ������ �׸��� (Cyan �������)
    drawConsoleWindow(10, 5, 40, 10, "���� ���� ������", 6); // Cyan ���

    // Ŀ�� ��ġ �Ʒ��� �̵�
    printf("\033[%d;0H", 30);

    return 0;
}
