#include <stdio.h>
#include <stdlib.h>
#include <conio.h>  

//�̹��� ��� 4���� c��� ���ð� 0�� �¿�� �̵���Ű�� ������ ���ĺ��ҽ��ϴ�.

#define WIDTH 40  //����ȭ�� ũ��

int print_game(int position) {
    system("cls");

    for (int i = 0; i < WIDTH; i++) {
        if (i == position)
            printf("0");
        else
            printf("_");
    }
    printf("\n");
}

int showMenu() { // ���� �ʱ� ȭ��
    puts("************************************");
    puts("*     0�� �¿�� �����̴� ����     *");
    puts("************************************");
    puts("");
    puts("1. ���ӽ���");
    puts("2. ����");
    return 0;
}

int main() { //A�� D�� �̿��Ͽ� 0�� �����̰� �ϴ� �ڵ�

    showMenu();

    char input = _getch();

    if (input == '1') {
        int position = WIDTH / 2;

        while (1) {
            if (_kbhit()) {
                char ch = _getch();

                if (ch == 'a' || ch == 'A') {
                    if (position > 0)
                        position--;
                }
                else if (ch == 'd' || ch == 'D') {
                    if (position < WIDTH - 1)
                        position++;
                }
            }

            print_game(position);
        }
    }
    else if (input == '2') { //����Ű 2�� ������ �� ������ ȭ��
        puts("������ �����մϴ�.");
    }
    else { //����Ű 1�� 2�� ������ �ٸ� Ű�� ������ �� ������ ȭ��
        puts("1���� 2�� �� �ϳ��� �����ּ���.");
    }

    return 0;
}