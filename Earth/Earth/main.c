#pragma comment(lib, "opengl32.lib")

#include <GLFW/glfw3.h>
#include <math.h>

#define PI 3.14159265f

float timeSpeed = 1.0f;  // 시간 진행 속도: +1 또는 -1

// 원을 그리는 함수
void drawCircle(float cx, float cy, float radius, int segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= segments; i++) {
        float angle = 2.0f * PI * i / segments;
        float x = radius * cosf(angle);
        float y = radius * sinf(angle);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

// 키 입력 콜백
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        if (key == GLFW_KEY_RIGHT)
            timeSpeed = 1.0f;
        else if (key == GLFW_KEY_LEFT)
            timeSpeed = -1.0f;
    }
}

int main() {
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(800, 800, "태양-지구-달 자전 및 공전", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    // 좌표계 설정
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        float time = glfwGetTime() * timeSpeed;

        // -------------------------
        // 태양
        // -------------------------
        glColor3f(1.0f, 1.0f, 0.0f); // 노란색
        drawCircle(0.0f, 0.0f, 0.2f, 100);

        // -------------------------
        // 지구 공전 (반시계 방향)
        // -------------------------
        float earthOrbitRadius = 0.6f;
        float earthAngle = time;  // 공전 각도
        float earthX = earthOrbitRadius * cosf(earthAngle);
        float earthY = earthOrbitRadius * sinf(earthAngle);

        glPushMatrix();
        glTranslatef(earthX, earthY, 0.0f);        // 지구 위치
        glRotatef(-time * 180.0f / PI, 0, 0, 1);   // 지구 자전 (시계 방향)
        glColor3f(0.0f, 0.5f, 1.0f);               // 파란색
        drawCircle(0.0f, 0.0f, 0.1f, 100);

        // -------------------------
        // 달 공전 (지구 중심에서 반시계 방향)
        // -------------------------
        float moonOrbitRadius = 0.2f;
        float moonAngle = time * 5.0f;  // 달은 더 빠르게 공전
        float moonX = moonOrbitRadius * cosf(moonAngle);
        float moonY = moonOrbitRadius * sinf(moonAngle);

        glPushMatrix();
        glTranslatef(moonX, moonY, 0.0f);          // 달 위치
        glRotatef(-time * 360.0f / PI, 0, 0, 1);   // 달 자전
        glColor3f(0.6f, 0.6f, 0.6f);               // 회색
        drawCircle(0.0f, 0.0f, 0.05f, 100);
        glPopMatrix();

        glPopMatrix(); // 지구 matrix

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
