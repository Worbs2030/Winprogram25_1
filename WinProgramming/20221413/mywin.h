// mywin.h
#ifndef MYWIN_H
#define MYWIN_H

// �ܼ� �ʺ� (�÷� ��)�� ���ϴ� �Լ�
int getConsoleWidth(void);

// �ܼ� ���� (�� ��)�� ���ϴ� �Լ�
int getConsoleHeight(void);

// Ŀ�� �̵� �Լ�: \033[row;colH
void move_cursor(int row, int col);

#endif // MYWIN_H
