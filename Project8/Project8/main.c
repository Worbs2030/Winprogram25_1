#include <stdio.h>
#include <stdlib.h>
#include <conio.h>  

//이번에 배운 4주차 c언어 샘플과 0을 좌우로 이동시키는 게임을 합쳐보았습니다.

#define WIDTH 40  //게임화면 크기

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

int showMenu() { // 게임 초기 화면
    puts("************************************");
    puts("*     0을 좌우로 움직이는 게임     *");
    puts("************************************");
    puts("");
    puts("1. 게임시작");
    puts("2. 종료");
    return 0;
}

int main() { //A와 D를 이용하여 0을 움직이게 하는 코드

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
    else if (input == '2') { //숫자키 2를 눌렀을 때 나오는 화면
        puts("게임을 종료합니다.");
    }
    else { //숫자키 1과 2를 제외한 다른 키를 눌렀을 때 나오는 화면
        puts("1번과 2번 중 하나를 눌러주세요.");
    }

    return 0;
}