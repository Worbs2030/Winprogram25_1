/*
 * GLFW (Graphics Library Framework)
 * - 크로스 플랫폼 OpenGL 컨텍스트 및 윈도우 생성 라이브러리
 * - 윈도우 관리, 입력 처리, 컨텍스트 설정 등을 간편하게 지원
 * - NuGet 패키지 매니저를 통해 glfw3 설치 후 사용
 */

#pragma comment(lib, "opengl32.lib")   // OpenGL 1.1 라이브러리 자동 링킹

#include <GLFW/glfw3.h>               // GLFW 헤더 (윈도우 및 컨텍스트 관리용

int main(void)
{
    // 1. GLFW 초기화: 성공 시 GLFW 시스템을 사용할 준비 완료
    if (!glfwInit()) {
        // 초기화 실패: 프로그램 비정상 종료
        return -1;
    }

    // 2. 윈도우 생성: 가로500, 세로500 크기로 제목 "GLFW: Triangle" 지정
    GLFWwindow* window = glfwCreateWindow(
        500, 500,              // 윈도우 가로/세로 크기
        "GLFW: Triangle",      // 윈도우 타이틀
        NULL, NULL             // 모니터(전체화면) 및 공유 컨텍스트 없음
    );
    // 윈도우 생성 실패 시 GLFW 종료 후 비정상 종료
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // 3. 현재 스레드에 윈도우의 OpenGL 컨텍스트 바인딩
    glfwMakeContextCurrent(window);

    // 4. 메인 루프: 윈도우가 닫힐 때까지 반복
    while (!glfwWindowShouldClose(window)) {
        // 4-1. 화면 클리어: 색상 버퍼만 지움
        glClear(GL_COLOR_BUFFER_BIT);

        // 4-2. 삼각형 그리기 구간 시작
        glBegin(GL_TRIANGLES);
        // 꼭짓점 1: 좌하단, 색상 빨강
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(-0.5f, -0.5f);

        // 꼭짓점 2: 우하단, 색상 초록
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(0.5f, -0.5f);

        // 꼭짓점 3: 중앙 상단, 색상 파랑
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(0.0f, 0.5f);
        glEnd();  // 그리기 구간 끝

        // 4-3. 더블 버퍼 스왑: 화면 깜빡임 없이 결과 출력
        glfwSwapBuffers(window);
        // 4-4. 이벤트 처리: 키보드/마우스 입력, 윈도우 이벤트 등
        glfwPollEvents();
    }

    // 5. 윈도우 파괴: 생성한 윈도우와 연결된 자원 해제
    glfwDestroyWindow(window);
    // 6. GLFW 시스템 종료: 초기화 중 생성된 모든 자원 해제
    glfwTerminate();

    return 0;  // 정상 종료
}