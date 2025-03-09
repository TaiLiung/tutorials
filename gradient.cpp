#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

void DrawGradientSquare()
{
    // Размер квадрата
    ImVec2 squareSize(100.0f, 100.0f);

    // Позиция квадрата
    ImVec2 squarePos = ImGui::GetCursorScreenPos();

    // Цвета для градиента
    ImColor color1(255, 0, 0); // Красный
    ImColor color2(0, 0, 255); // Синий

    // Получаем draw list для текущего окна
    ImDrawList* drawList = ImGui::GetWindowDrawList();

    // Рисуем квадрат с градиентом
    drawList->AddRectFilledMultiColor(
        squarePos, 
        ImVec2(squarePos.x + squareSize.x, squarePos.y + squareSize.y), 
        color1, color2, color2, color1
    );
}

int main()
{
    // Инициализация GLFW и создание окна
    if (!glfwInit())
        return -1;

    GLFWwindow* window = glfwCreateWindow(1280, 720, "ImGui Gradient Square", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Включение вертикальной синхронизации

    // Инициализация ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    // Инициализация ImGui для OpenGL и GLFW
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // Основной цикл
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Начало нового кадра ImGui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Рисуем квадрат с градиентом
        DrawGradientSquare();

        // Рендеринг ImGui
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Обмен буферов
        glfwSwapBuffers(window);
    }

    // Очистка
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
