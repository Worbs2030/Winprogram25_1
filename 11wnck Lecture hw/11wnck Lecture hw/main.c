#pragma comment(lib, "opengl32.lib")
#include <GLFW/glfw3.h>
#include <math.h>

#define PI 3.1415926535f

#define WINDOW_WIDTH 537
#define WINDOW_HEIGHT 445

typedef struct
{
    float x, y;
} Vec2;

typedef struct
{
    Vec2 position;
    float rotation;
    Vec2 scale;
} Transform;

typedef struct
{
    Transform transform;
    int segments;
} Ellipse;

void draw_ellipse(Ellipse* e, float r, float g, float b)
{
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(e->transform.position.x, e->transform.position.y);

    for (int i = 0; i <= e->segments; ++i)
    {
        float angle = 2.0f * PI * i / e->segments;
        float x = e->transform.position.x + cosf(angle) * e->transform.scale.x;
        float y = e->transform.position.y + sinf(angle) * e->transform.scale.y;
        glVertex2f(x, y);
    }
    glEnd();
}

void draw_line(float x1, float y1, float x2, float y2, float r, float g, float b)
{
    glColor3f(r, g, b);
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

int main()
{
    if (!glfwInit())
        return -1;

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "BONOBONO", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1, 1);
    glClearColor(1, 1, 1, 1);

    Ellipse borderEllipse = { { {537 / 2.0f, 445 / 2.0f}, 0, {215, 193.5f} }, 64 };
    Ellipse blueEllipse = { { {537 / 2.0f, 445 / 2.0f}, 0, {213, 191} }, 64 };
    Ellipse eyeEllipse1 = { { {88.1, 268}, 0, {15, 15.5f} }, 48 };
    Ellipse eyeEllipse2 = { { {428.2, 262}, 0, {16, 15} }, 48 };
    Ellipse whiteEllipseleft = { { {235.6, 157}, 0, {43.5f, 40.5f} }, 64 };
    Ellipse whiteEllipseright = { { {316.4, 157}, 0, {43.5f, 40.5f} }, 64 };
    Ellipse noseEllipse = { { {275, 201}, 0, {33, 27.5f} }, 64 };


    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        draw_ellipse(&borderEllipse, 0, 0, 0);
        draw_ellipse(&blueEllipse, 0, 0.439f, 0.753f);
        draw_ellipse(&eyeEllipse1, 0, 0, 0);
        draw_ellipse(&eyeEllipse2, 0, 0, 0);
        draw_ellipse(&whiteEllipseleft, 1, 1, 1);
        draw_ellipse(&whiteEllipseright, 1, 1, 1);
        draw_ellipse(&noseEllipse, 0, 0, 0);

        draw_line(155, 195, 216, 179, 0, 0, 0);
        draw_line(156, 154, 214, 159, 0, 0, 0);
        draw_line(157, 125, 221, 144, 0, 0, 0);
        draw_line(324, 175, 387, 194, 0, 0, 0);
        draw_line(324, 157, 391, 157, 0, 0, 0);
        draw_line(323, 139, 389, 125, 0, 0, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
