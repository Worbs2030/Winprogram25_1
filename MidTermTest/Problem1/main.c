#include <stdio.h>

int PassOrFail(int score) {
    if (score >= 50) {
        return 1; // Pass
    }
    else {
        return 0; // Fail
    }
}

int main() {
    int myExpectedScore = 62; // ������ ���� ������ ���⿡ �Է��ϼ���
    int result = PassOrFail(myExpectedScore);

    if (result == 1) {
        printf("����� �����ϴ�!\n");
    }
    else {
        printf("�츮�� ���ߴ١� ������̴١�\n");
    }

    return 0;
}
