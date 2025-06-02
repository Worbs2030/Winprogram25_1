#pragma comment(lib, "opengl32.lib")

#include <GLFW/glfw3.h>
#include <math.h>

#define PI 3.14159265f

float timeSpeed = 1.0f;  // �ð� ���� �ӵ�: +1 �Ǵ� -1

// ���� �׸��� �Լ�
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

// Ű �Է� �ݹ�
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

    GLFWwindow* window = glfwCreateWindow(800, 800, "�¾�-����-�� ���� �� ����", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    // ��ǥ�� ����
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        float time = glfwGetTime() * timeSpeed;

        // -------------------------
        // �¾�
        // -------------------------
        glColor3f(1.0f, 1.0f, 0.0f); // �����
        drawCircle(0.0f, 0.0f, 0.2f, 100);

        // -------------------------
        // ���� ���� (�ݽð� ����)
        // -------------------------
        float earthOrbitRadius = 0.6f;
        float earthAngle = time;  // ���� ����
        float earthX = earthOrbitRadius * cosf(earthAngle);
        float earthY = earthOrbitRadius * sinf(earthAngle);

        glPushMatrix();
        glTranslatef(earthX, earthY, 0.0f);        // ���� ��ġ
        glRotatef(-time * 180.0f / PI, 0, 0, 1);   // ���� ���� (�ð� ����)
        glColor3f(0.0f, 0.5f, 1.0f);               // �Ķ���
        drawCircle(0.0f, 0.0f, 0.1f, 100);

        // -------------------------
        // �� ���� (���� �߽ɿ��� �ݽð� ����)
        // -------------------------
        float moonOrbitRadius = 0.2f;
        float moonAngle = time * 5.0f;  // ���� �� ������ ����
        float moonX = moonOrbitRadius * cosf(moonAngle);
        float moonY = moonOrbitRadius * sinf(moonAngle);

        glPushMatrix();
        glTranslatef(moonX, moonY, 0.0f);          // �� ��ġ
        glRotatef(-time * 360.0f / PI, 0, 0, 1);   // �� ����
        glColor3f(0.6f, 0.6f, 0.6f);               // ȸ��
        drawCircle(0.0f, 0.0f, 0.05f, 100);
        glPopMatrix();

        glPopMatrix(); // ���� matrix

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
