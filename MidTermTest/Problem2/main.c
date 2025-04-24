#include <stdio.h>
#include <string.h>

#define LEFT_RIGHT_MARGIN 2
#define TOP_BOTTOM_MARGIN 1
#define TASKBAR_HEIGHT 1

// ANSI 배경 색 (0~7)
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

// 점선 테두리 그리기
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

// 윈도우 그리기 함수
void drawConsoleWindow(int startX, int startY, int width, int height, const char* title, int color) {
    for (int row = 0; row < height; row++) {
        // 커서 위치 설정
        printf("\033[%d;%dH", startY + row, startX);

        // 윈도우 상단 (점선 영역)
        if (row == 0) {
            printf("%s", bgColors[color % 8]);
            for (int col = 0; col < width; col++) {
                if (col == 0 || col == width - 1) {
                    printf("|");
                }
                else {
                    drawDottedLine(1); // 점선
                }
            }
            printf("\033[0m");
        }
        else if (row == 1) {
            // 윈도우 제목과 X 버튼
            printf("%s", bgColors[color % 8]);
            int titleLen = strlen(title);
            // 제목 시작 위치를 더 왼쪽으로 보냄
            int titleStart = (width - titleLen - 5) / 2 - 7; // -7로 제목을 왼쪽으로 더 이동

            for (int col = 0; col < width; col++) {
                if (col == titleStart) {
                    printf("%s", title);
                    col += titleLen - 1;
                }
                // X 버튼 위치 (오른쪽 끝에서 3칸)
                else if (col == width - 4) {
                    printf("\033[41m\033[97m X \033[0m%s", bgColors[color % 8]); // 빨간 바탕, 흰색 글자
                    col += 2;
                }
                else {
                    printf(" ");
                }
            }
            printf("\033[0m");
        }
        else if (row == height - 1) {
            // 하단
            printf("%s", bgColors[color % 8]);
            for (int col = 0; col < width; col++) {
                if (col == 0 || col == width - 1) {
                    printf("|");
                }
                else {
                    drawDottedLine(1); // 점선
                }
            }
            printf("\033[0m");
        }
        else {
            // 중간 부분
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

// 배경 그리는 함수
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
            printf("\033[44m"); // 파란 배경
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
            printf("\033[100m"); // 어두운 회색 (작업표시줄)
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

    // 배경 그리기
    DrawBG(width, height);

    // 윈도우 그리기 (Cyan 배경으로)
    drawConsoleWindow(10, 5, 40, 10, "나의 멋진 윈도우", 6); // Cyan 배경

    // 커서 위치 아래로 이동
    printf("\033[%d;0H", 30);

    return 0;
}
