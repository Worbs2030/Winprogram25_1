#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MONSTER_COUNT 5
#define MAP_WIDTH 200
#define MAP_HEIGHT 20

typedef struct {
    int x, y;
} BodyPart;

typedef struct {
    int x, y, width, height;
} Hitbox;

typedef struct {
    bool isAlive;
    BodyPart head, body, leftLeg, rightLeg;
    int health, attackPower;
    Hitbox hitbox[2];
} Object;

Object monsters[MONSTER_COUNT];

// 🟢 몬스터 랜덤 이동 함수
void moveMonsters(Object monsters[]) {
    for (int i = 0; i < MONSTER_COUNT; i++) {
        if (!monsters[i].isAlive) continue;

        int direction = rand() % 2; // 0: 왼쪽, 1: 오른쪽
        int distance = (rand() % 3) + 1; // 1~3칸
        int dx = (direction == 0) ? -distance : distance;

        // 몬스터의 각 신체 부위가 이동하도록 조정
        monsters[i].head.x += dx;
        monsters[i].body.x += dx;
        monsters[i].leftLeg.x += dx;
        monsters[i].rightLeg.x += dx;
    }
}

int main() {
    srand(time(NULL)); // 랜덤 시드 초기화

    // 몬스터 초기화
    for (int i = 0; i < MONSTER_COUNT; i++) {
        int monsterX = rand() % MAP_WIDTH;
        int monsterY = MAP_HEIGHT - 2;
        monsters[i] = (Object){ true, {monsterX, monsterY}, {monsterX, monsterY + 1},
                                {monsterX - 1, monsterY + 1}, {monsterX + 1, monsterY + 1},
                                10, 5, {{monsterX, monsterY, 1, 1}, {monsterX + 1, monsterY, 1, 1}} };
    }

    // 몬스터 이동 출력
    for (int i = 0; i < 10; i++) { // 10번의 이동 반복
        moveMonsters(monsters);
        printf("이동 후 몬스터 위치:\n");
        for (int i = 0; i < MONSTER_COUNT; i++) {
            printf("몬스터 %d 위치: (x=%d, y=%d)\n", i, monsters[i].head.x, monsters[i].head.y);
        }
        printf("\n");
    }

    return 0;
}
