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
    int myExpectedScore = 62; // 본인의 예상 점수를 여기에 입력하세요
    int result = PassOrFail(myExpectedScore);

    if (result == 1) {
        printf("재시험 없습니다!\n");
    }
    else {
        printf("우리는 망했다… 재시험이다…\n");
    }

    return 0;
}
