/*
 * GLFW (Graphics Library Framework)
 * - ũ�ν� �÷��� OpenGL ���ؽ�Ʈ �� ������ ���� ���̺귯��
 * - ������ ����, �Է� ó��, ���ؽ�Ʈ ���� ���� �����ϰ� ����
 * - NuGet ��Ű�� �Ŵ����� ���� glfw3 ��ġ �� ���
 */

#pragma comment(lib, "opengl32.lib")   // OpenGL 1.1 ���̺귯�� �ڵ� ��ŷ

#include <GLFW/glfw3.h>               // GLFW ��� (������ �� ���ؽ�Ʈ ������

int main(void)
{
    // 1. GLFW �ʱ�ȭ: ���� �� GLFW �ý����� ����� �غ� �Ϸ�
    if (!glfwInit()) {
        // �ʱ�ȭ ����: ���α׷� ������ ����
        return -1;
    }

    // 2. ������ ����: ����500, ����500 ũ��� ���� "GLFW: Triangle" ����
    GLFWwindow* window = glfwCreateWindow(
        500, 500,              // ������ ����/���� ũ��
        "GLFW: Triangle",      // ������ Ÿ��Ʋ
        NULL, NULL             // �����(��üȭ��) �� ���� ���ؽ�Ʈ ����
    );
    // ������ ���� ���� �� GLFW ���� �� ������ ����
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // 3. ���� �����忡 �������� OpenGL ���ؽ�Ʈ ���ε�
    glfwMakeContextCurrent(window);

    // 4. ���� ����: �����찡 ���� ������ �ݺ�
    while (!glfwWindowShouldClose(window)) {
        // 4-1. ȭ�� Ŭ����: ���� ���۸� ����
        glClear(GL_COLOR_BUFFER_BIT);

        // 4-2. �ﰢ�� �׸��� ���� ����
        glBegin(GL_TRIANGLES);
        // ������ 1: ���ϴ�, ���� ����
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(-0.5f, -0.5f);

        // ������ 2: ���ϴ�, ���� �ʷ�
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(0.5f, -0.5f);

        // ������ 3: �߾� ���, ���� �Ķ�
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(0.0f, 0.5f);
        glEnd();  // �׸��� ���� ��

        // 4-3. ���� ���� ����: ȭ�� ������ ���� ��� ���
        glfwSwapBuffers(window);
        // 4-4. �̺�Ʈ ó��: Ű����/���콺 �Է�, ������ �̺�Ʈ ��
        glfwPollEvents();
    }

    // 5. ������ �ı�: ������ ������� ����� �ڿ� ����
    glfwDestroyWindow(window);
    // 6. GLFW �ý��� ����: �ʱ�ȭ �� ������ ��� �ڿ� ����
    glfwTerminate();

    return 0;  // ���� ����
}