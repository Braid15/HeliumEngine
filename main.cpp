#ifdef _DEBUG
#include "S:\SDKs\Visual_Leak_Detector\include\vld.h"
#endif

#include <helium_std.h>

#include <glew.h>
#include <glfw3.h>

void error_callback(int nu, const char* msg) {
    std::cout << "[GLFW] - " << msg << "\n";
}

int main() {

    glfwInit();

    glfwSetErrorCallback(error_callback);

    GLFWwindow* window = glfwCreateWindow(1920, 1080, "WINDOW", NULL, NULL);
    if (!window) {
        std::cout << "ERROR!\n";
        glfwTerminate();
        system("PAUSE");
        return -1;
    }

    glfwMakeContextCurrent(window);

    glewExperimental = true;
    glewInit();

    std::cout << glGetString(GL_VERSION) << "\n";
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2, 0.2, 0.2, 1.0);

        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    system("PAUSE");
    return 0;
}

