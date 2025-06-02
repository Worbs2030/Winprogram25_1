#pragma comment(lib, "opengl32.lib")

#include <GLFW/glfw3.h>
#include <math.h>
#include <stdbool.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define PI 3.14159265f

bool isWinking = false;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_W && action == GLFW_PRESS) {
        isWinking = !isWinking;
    }
}

void drawCircle(float cx, float cy, float r, int segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= segments; ++i) {
        float theta = 2.0f * PI * i / segments;
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

void drawEye(float cx, float cy, float size) {
    glLineWidth(5.0f);  // ´« ¼± ±½±â
    glBegin(GL_LINES);
    glVertex2f(cx - size, cy);
    glVertex2f(cx + size, cy);
    glEnd();
}

void drawWink(float cx, float cy, float size) {
    glLineWidth(5.0f);  // À®Å© ¼± ±½±â
    glBegin(GL_LINES);
    glVertex2f(cx + size, cy + size);
    glVertex2f(cx, cy);
    glVertex2f(cx, cy);
    glVertex2f(cx + size, cy - size);
    glEnd();
}

void drawSmile(float cx, float cy, float r, int segments, float startAngle, float endAngle) {
    glLineWidth(5.0f);  // ÀÔ ¼± ±½±â
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= segments; ++i) {
        float theta = startAngle + (endAngle - startAngle) * i / segments;
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

int main() {
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "½º¸¶ÀÏ ¸Ç", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // ¾ó±¼
        glColor3f(1.0f, 1.0f, 0.0f);
        drawCircle(400, 300, 200, 360);

        // ´«
        glColor3f(0.0f, 0.0f, 0.0f);
        drawEye(330, 370, 10);

        if (isWinking)
            drawWink(470, 370, 10);
        else
            drawEye(470, 370, 10);

        // ÀÔ
        drawSmile(400, 260, 100, 100, PI / 6, 5 * PI / 6);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
