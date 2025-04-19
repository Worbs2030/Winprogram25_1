#ifndef MYWIN_H
#define MYWIN_H

// 콘솔 너비 (컬럼 수)를 구하는 함수
int getConsoleWidth();

// 콘솔 높이 (줄 수)를 구하는 함수
int getConsoleHeight();

// 콘솔 커서를 지정한 위치로 이동시키는 함수
void move_cursor(int row, int col);

#endif // MYWIN_H

// 구조체 정의
typedef struct {
    int x, y;
    int width, height;
    char name[100];
    int color;     // Windows 콘솔 색상 코드 (배경색)
    int isMax;     // 0 or 1
} MyWin;

// 함수 선언
int getConsoleWidth();
int getConsoleHeight();
void move_cursor(int row, int col);
void DrawWin(MyWin a);

#endif // MYWIN_H

