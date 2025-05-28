#pragma comment(lib, "Opengl32.lib")
#include <GLFW/glfw3.h>
#include <math.h>
#include <time.h>
#include <stdio.h>

#define PI 3.14159265f

const int DIGIT_WIDTH = 3;
const int DIGIT_HEIGHT = 5;

const char* DIGITS[] = {
    "111101101101111", // 0
    "010010010010010", // 1
    "111001111100111", // 2
    "111001111001111", // 3
    "101101111001001", // 4
    "111100111001111", // 5
    "111100111101111", // 6
    "111001001001001", // 7
    "111101111101111", // 8
    "111101111001111", // 9
    "000010000010000"  // :
};

void circle(float cx, float cy, float r, int segments, float red, float green, float blue) {
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(red, green, blue);
    glVertex2f(cx, cy);
    for (int i = 0; i <= segments; i++) {
        float angle = 2.0f * PI * i / segments;
        float x = r * cosf(angle);
        float y = r * sinf(angle);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

void drawLine(float x1, float y1, float x2, float y2, float r, float g, float b, float width) {
    glLineWidth(width);
    glColor3f(r, g, b);
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

void getEndpoint(float angleDegrees, float length, float* outX, float* outY) {
    float angleRadians = (PI / 180.0f) * angleDegrees;
    *outX = length * sinf(angleRadians);
    *outY = length * cosf(angleRadians);
}

void drawClockTicks(float cx, float cy, float radius, int count, float longLen, float shortLen, int thickEvery, float thickWidth, float thinWidth) {
    for (int i = 0; i < count; i++) {
        float angle = i * 360.0f / count;
        float sx, sy, ex, ey;
        float len = (i % thickEvery == 0) ? longLen : shortLen;
        float width = (i % thickEvery == 0) ? thickWidth : thinWidth;

        getEndpoint(angle, radius, &sx, &sy);
        getEndpoint(angle, radius - len, &ex, &ey);

        drawLine(cx + sx, cy + sy, cx + ex, cy + ey, 0.0f, 0.0f, 0.0f, width);
    }
}

void drawDigit(float x, float y, float size, int digit, float r, float g, float b) {
    if (digit < 0 || digit > 10) return;
    const char* bitmap = DIGITS[digit];
    float pixelSize = size;

    for (int row = 0; row < DIGIT_HEIGHT; row++) {
        for (int col = 0; col < DIGIT_WIDTH; col++) {
            int index = row * DIGIT_WIDTH + col;
            if (bitmap[index] == '1') {
                float px = x + col * pixelSize;
                float py = y - row * pixelSize;
                glColor3f(r, g, b);
                glBegin(GL_QUADS);
                glVertex2f(px, py);
                glVertex2f(px + pixelSize, py);
                glVertex2f(px + pixelSize, py - pixelSize);
                glVertex2f(px, py - pixelSize);
                glEnd();
            }
        }
    }
}

void drawTimeString(const char* str, float startX, float startY, float size, float spacing, float r, float g, float b) {
    float x = startX;
    for (int i = 0; str[i]; i++) {
        int digit;
        if (str[i] >= '0' && str[i] <= '9') {
            digit = str[i] - '0';
        }
        else if (str[i] == ':') {
            digit = 10;
        }
        else {
            continue;
        }
        drawDigit(x, startY, size, digit, r, g, b);
        x += (DIGIT_WIDTH + spacing) * size;
    }
}

int main(void) {
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(700, 700, "GLFW: 한국시간 시계", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        time_t rawTime;
        time(&rawTime);
        struct tm* kst = gmtime(&rawTime);
        kst->tm_hour += 9;
        if (kst->tm_hour >= 24) kst->tm_hour -= 24;

        int hour = kst->tm_hour;
        int minute = kst->tm_min;
        int second = kst->tm_sec;

        float hourAngle = (hour % 12 + minute / 60.0f) * 30.0f;
        float minuteAngle = (minute + second / 60.0f) * 6.0f;
        float secondAngle = second * 6.0f;

        float hx, hy, mx, my;
        getEndpoint(hourAngle, 0.45f, &hx, &hy);
        getEndpoint(minuteAngle, 0.72f, &mx, &my);

        float sx, sy;
        getEndpoint(secondAngle, 0.2f, &sx, &sy);
        sx += -0.54f;

        // 줄인 시계 본체
        circle(0.0f, 0.0f, 0.9f, 100, 1.0f, 1.0f, 1.0f);

        // 회색 테두리 줄이기
        glLineWidth(7.0f);
        glBegin(GL_LINE_LOOP);
        glColor3f(0.5f, 0.5f, 0.5f);
        for (int i = 0; i <= 100; i++) {
            float angle = 2.0f * PI * i / 100;
            float x = cosf(angle) * 0.9f;
            float y = sinf(angle) * 0.9f;
            glVertex2f(x, y);
        }
        glEnd();

        // 눈금 줄이기
        drawClockTicks(0.0f, 0.0f, 0.9f, 60, 0.09f, 0.045f, 5, 3.0f, 1.2f);

        // 중심 점
        circle(0.0f, 0.0f, 0.02f, 30, 0.0f, 0.0f, 0.0f);

        // 시침, 분침
        drawLine(0.0f, 0.0f, hx, hy, 0.0f, 0.0f, 0.0f, 8.0f);
        drawLine(0.0f, 0.0f, mx, my, 0.0f, 0.0f, 0.0f, 5.0f);

        // 초침 보조 시계 및 초침
        circle(-0.54f, 0.0f, 0.22f, 50, 0.5f, 0.5f, 0.5f);
        drawClockTicks(-0.54f, 0.0f, 0.22f, 60, 0.03f, 0.018f, 10, 2.2f, 1.0f);
        circle(-0.54f, 0.0f, 0.012f, 30, 0.0f, 0.0f, 0.0f);
        drawLine(-0.54f, 0.0f, sx, sy, 1.0f, 0.0f, 0.0f, 2.5f);

        // 디지털 시계
        char timeStr[9];
        snprintf(timeStr, sizeof(timeStr), "%02d:%02d:%02d", hour, minute, second);
        drawTimeString(timeStr, -0.35f, -0.40f, 0.025f, 0.3f, 0.0f, 0.0f, 0.0f);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}