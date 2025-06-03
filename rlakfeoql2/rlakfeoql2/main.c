#pragma comment(lib, "opengl32.lib")   // OpenGL 1.1 라이브러리 자동 링킹

#include <GLFW/glfw3.h>                // GLFW: 윈도우·컨텍스트·입력 관리
#include <math.h>                      // sinf(), cosf() 등 수학 함수

#define PI 3.1415926535f               // 원주율 상수

 // 2D 벡터 구조체
    typedef struct {
    float x, y;
} Vec2;

// 위치·회전·크기 정보를 담은 변환 구조체
typedef struct {
    Vec2 position;    // 위치 (x, y)
    float rotation;   // 회전 (라디안 단위)
    Vec2 scale;       // 확대/축소 (x, y)
} Transform;

// 삼각형 객체
typedef struct {
    Transform transform;
} Triangle;

// 사각형 객체
typedef struct {
    Transform transform;
} Square;

// 원 객체 (분할 개수 포함)
typedef struct {
    Transform transform;
    int segments;    // 원을 근사할 삼각형 팬의 분할 개수
} Circle;


// 삼각형 그리기 함수
void draw_triangle(Triangle* tri)
{
    glPushMatrix();   // 현재 매트릭스 상태 저장

    // 1) 이동
    glTranslatef(tri->transform.position.x,
        tri->transform.position.y,
        0.0f);
    // 2) 회전 (라디안을 도 단위로 변환)
    glRotatef(tri->transform.rotation * (180.0f / PI),
        0.0f, 0.0f, 1.0f);
    // 3) 스케일
    glScalef(tri->transform.scale.x,
        tri->transform.scale.y,
        1.0f);

    // 삼각형 드로우
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);      // 빨강
    glVertex2f(0.0f, 0.5f);         // 상단 꼭짓점
    glVertex2f(-0.5f, -0.5f);         // 좌하단
    glVertex2f(0.5f, -0.5f);         // 우하단
    glEnd();

    glPopMatrix();    // 매트릭스 상태 복원
}

// 사각형 그리기 함수
void draw_square(Square* sq)
{
    glPushMatrix();

    glTranslatef(sq->transform.position.x,
        sq->transform.position.y,
        0.0f);
    glRotatef(sq->transform.rotation * (180.0f / PI),
        0.0f, 0.0f, 1.0f);
    glScalef(sq->transform.scale.x,
        sq->transform.scale.y,
        1.0f);

    glBegin(GL_QUADS);
    glColor3f(0.0f, 1.0f, 0.0f);      // 초록
    glVertex2f(-0.5f, 0.5f);         // 좌상단
    glVertex2f(0.5f, 0.5f);         // 우상단
    glVertex2f(0.5f, -0.5f);         // 우하단
    glVertex2f(-0.5f, -0.5f);         // 좌하단
    glEnd();

    glPopMatrix();
}

// 원 그리기 함수 (삼각형 팬 사용)
void draw_circle(Circle* c)
{
    glPushMatrix();

    glTranslatef(c->transform.position.x,
        c->transform.position.y,
        0.0f);
    glRotatef(c->transform.rotation * (180.0f / PI),
        0.0f, 0.0f, 1.0f);
    glScalef(c->transform.scale.x,
        c->transform.scale.y,
        1.0f);

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.0f, 0.0f, 1.0f);      // 파랑
    glVertex2f(0.0f, 0.0f);           // 팬의 중심

    // 분할 개수만큼 원 둘레 점 생성
    for (int i = 0; i <= c->segments; ++i)
    {
        float angle = 2.0f * PI * i / c->segments;
        glVertex2f(cosf(angle) * 0.5f,
            sinf(angle) * 0.5f);
    }
    glEnd();

    glPopMatrix();
}


int main(void)
{
    // GLFW 초기화: 실패 시 종료
    if (!glfwInit())
        return -1;

    // 800×600 윈도우 생성
    GLFWwindow* window = glfwCreateWindow(
        800, 600,
        "OpenGL C Demo",
        NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // OpenGL 컨텍스트 바인딩
    glfwMakeContextCurrent(window);

    // 2D용 직교 투영 설정 (좌표 −1…1 범위)
    glOrtho(-1, 1, -1, 1, -1, 1);

    // 객체 초기화
    Triangle tri = { {{ 0.0f,   0.0f}, 0.0f, {1.0f, 1.0f}} };
    Square   sq = { {{-0.5f,  -0.5f}, 0.0f, {1.0f, 1.0f}} };
    Circle   cir = { {{ 0.5f,   0.5f}, 0.0f, {1.0f, 1.0f}}, 32 };

    // 메인 루프: 창이 닫힐 때까지 반복
    while (!glfwWindowShouldClose(window))
    {
        float time = (float)glfwGetTime();  // 경과 시간(sec)

        // 애니메이션 적용
        tri.transform.position.x = sinf(time);              // 좌우 이동
        sq.transform.rotation = time;                    // 회전
        cir.transform.scale.x = 1.0f + 0.5f * sinf(time); // 가로 스케일 변화

        // 화면 초기화 (색 버퍼만)
        glClear(GL_COLOR_BUFFER_BIT);

        // 도형 그리기
        draw_triangle(&tri);
        draw_square(&sq);
        draw_circle(&cir);

        // 버퍼 스왑 & 이벤트 처리
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 종료 처리
    glfwTerminate();
    return 0;
}