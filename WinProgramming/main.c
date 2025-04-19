#include <windows.h>
#include <stdio.h>
#include "mywin.h"

#define LEFT_MARGIN     5
#define RIGHT_MARGIN    5
#define TOP_MARGIN      1
#define BOTTOM_MARGIN   3

#define FRAME_COUNT     3

// 애니메이션 프레임
const char* cursorFrames[FRAME_COUNT] = {
    "^_^",
    "o_o",
    "-_-"
};

// 색상 정의
#define BLACK_TEXT_ONLY   (0)
#define YELLOW_TEXT_ONLY  (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY)

void hideConsoleCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 100;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void drawAsciiCursor(HANDLE hConsole, COORD pos, const char* frame, WORD textColor) {
    DWORD written;
    WORD currentAttr;
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    // 가운데 정렬 위해 시작 위치 조정
    COORD drawPos = { (SHORT)(pos.X - 1), pos.Y };

    for (int i = 0; i < 3; ++i) {
        COORD p = { (SHORT)(drawPos.X + i), drawPos.Y };

        // 기존 속성 얻기
        ReadConsoleOutputAttribute(hConsole, &currentAttr, 1, p, &written);
        WORD bg = currentAttr & 0xF0;
        WORD finalAttr = bg | textColor;

        FillConsoleOutputCharacterA(hConsole, frame[i], 1, p, &written);
        FillConsoleOutputAttribute(hConsole, finalAttr, 1, p, &written);
    }
}

void clearAsciiCursor(HANDLE hConsole, COORD pos, WORD bgColor) {
    DWORD written;
    COORD drawPos = { (SHORT)(pos.X - 1), pos.Y };

    for (int i = 0; i < 3; ++i) {
        COORD p = { (SHORT)(drawPos.X + i), drawPos.Y };
        FillConsoleOutputCharacterA(hConsole, ' ', 1, p, &written);
        FillConsoleOutputAttribute(hConsole, bgColor, 1, p, &written);
    }
}

int main() {
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleMode(hInput, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
    hideConsoleCursor();

    int width = getConsoleWidth();
    int height = getConsoleHeight();
    int fillWidth = width - LEFT_MARGIN - RIGHT_MARGIN;
    int fillHeight = height - TOP_MARGIN - BOTTOM_MARGIN;
    WORD blueBg = BACKGROUND_BLUE;

    // 파란 배경 그리기
    for (int row = 0; row < fillHeight; row++) {
        int consoleRow = TOP_MARGIN + row;
        COORD coord = { (SHORT)LEFT_MARGIN, (SHORT)consoleRow };
        DWORD charsWritten;
        FillConsoleOutputCharacterA(hConsole, ' ', fillWidth, coord, &charsWritten);
        FillConsoleOutputAttribute(hConsole, blueBg, fillWidth, coord, &charsWritten);
    }

    // 마우스 이벤트 루프
    INPUT_RECORD inputRecord;
    DWORD events;
    COORD lastPos = { -1, -1 };
    WORD currentColor = BLACK_TEXT_ONLY;
    int frameIndex = 0;

    while (1) {
        ReadConsoleInput(hInput, &inputRecord, 1, &events);

        if (inputRecord.EventType == MOUSE_EVENT) {
            MOUSE_EVENT_RECORD mouse = inputRecord.Event.MouseEvent;
            COORD pos = mouse.dwMousePosition;

            if (pos.X >= LEFT_MARGIN + 1 && pos.X < (width - RIGHT_MARGIN - 1) &&
                pos.Y >= TOP_MARGIN && pos.Y < (height - BOTTOM_MARGIN)) {

                if (lastPos.X != -1 && lastPos.Y != -1) {
                    clearAsciiCursor(hConsole, lastPos, blueBg);
                }

                lastPos = pos;

                // 색상 처리
                if (mouse.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) {
                    currentColor = YELLOW_TEXT_ONLY;
                }
                else {
                    currentColor = BLACK_TEXT_ONLY;
                }

                // 프레임 출력
                drawAsciiCursor(hConsole, pos, cursorFrames[frameIndex], currentColor);

                // 프레임 넘김
                frameIndex = (frameIndex + 1) % FRAME_COUNT;
            }
        }
    }

    return 0;
}
