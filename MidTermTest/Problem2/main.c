#include <stdio.h>

#define LEFT_RIGHT_MARGIN 2
#define TOP_BOTTOM_MARGIN 1
#define TASKBAR_HEIGHT 1

void DrawBG(int width, int height) {
    int total_width = width + LEFT_RIGHT_MARGIN * 2;
    int total_height = height + TOP_BOTTOM_MARGIN * 2 + TASKBAR_HEIGHT;

    for (int row = 0; row < total_height; row++) {
        // ��� ����
        if (row < TOP_BOTTOM_MARGIN) {
            for (int col = 0; col < total_width; col++) {
                printf(" ");
            }
        }
        // ����ȭ�� �Ķ���
        else if (row < TOP_BOTTOM_MARGIN + height) {
            for (int col = 0; col < LEFT_RIGHT_MARGIN; col++) {
                printf(" ");
            }
            printf("\033[44m"); // �Ķ� ��� ����
            for (int col = 0; col < width; col++) {
                printf(" ");
            }
            printf("\033[0m");  // ���� ����
            for (int col = 0; col < LEFT_RIGHT_MARGIN; col++) {
                printf(" ");
            }
        }
        // �۾�ǥ���� (�� �Ʒ�)
        else {
            for (int col = 0; col < LEFT_RIGHT_MARGIN; col++) {
                printf(" ");
            }
            printf("\033[100m"); // ��ο� ȸ�� ��� (�۾�ǥ���� ����)
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
    // ���� ����ȭ���� ũ�� = �� �ػ� 80x25���� ���� �� �۾�ǥ���� ����
    int width = 80 - LEFT_RIGHT_MARGIN * 2;
    int height = 25 - TOP_BOTTOM_MARGIN * 2 - TASKBAR_HEIGHT;

    DrawBG(width, height);

    return 0;
}
