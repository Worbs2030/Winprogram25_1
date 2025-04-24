#include <stdio.h>

#define LEFT_RIGHT_MARGIN 2
#define TOP_BOTTOM_MARGIN 1
#define TASKBAR_HEIGHT 1

void DrawBG(int width, int height) {
    int total_width = width + LEFT_RIGHT_MARGIN * 2;
    int total_height = height + TOP_BOTTOM_MARGIN * 2 + TASKBAR_HEIGHT;

    for (int row = 0; row < total_height; row++) {
        // 상단 여백
        if (row < TOP_BOTTOM_MARGIN) {
            for (int col = 0; col < total_width; col++) {
                printf(" ");
            }
        }
        // 바탕화면 파란색
        else if (row < TOP_BOTTOM_MARGIN + height) {
            for (int col = 0; col < LEFT_RIGHT_MARGIN; col++) {
                printf(" ");
            }
            printf("\033[44m"); // 파란 배경 시작
            for (int col = 0; col < width; col++) {
                printf(" ");
            }
            printf("\033[0m");  // 색상 리셋
            for (int col = 0; col < LEFT_RIGHT_MARGIN; col++) {
                printf(" ");
            }
        }
        // 작업표시줄 (맨 아래)
        else {
            for (int col = 0; col < LEFT_RIGHT_MARGIN; col++) {
                printf(" ");
            }
            printf("\033[100m"); // 어두운 회색 배경 (작업표시줄 느낌)
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
    // 내부 바탕화면의 크기 = 총 해상도 80x25에서 여백 및 작업표시줄 제외
    int width = 80 - LEFT_RIGHT_MARGIN * 2;
    int height = 25 - TOP_BOTTOM_MARGIN * 2 - TASKBAR_HEIGHT;

    DrawBG(width, height);

    return 0;
}
