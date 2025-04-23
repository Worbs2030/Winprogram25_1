// mywin.h
#ifndef MYWIN_H
#define MYWIN_H

// 콘솔 너비 (컬럼 수)를 구하는 함수
int getConsoleWidth(void);

// 콘솔 높이 (줄 수)를 구하는 함수
int getConsoleHeight(void);

// 커서 이동 함수: \033[row;colH
void move_cursor(int row, int col);

#endif // MYWIN_H
