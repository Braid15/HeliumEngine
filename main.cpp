#ifdef _DEBUG
#include "S:\SDKs\Visual_Leak_Detector\include\vld.h"
#endif

#include <helium_std.h>
#include "src\app\app.h"
#include "src\app\app_instance.h"


using namespace HeliumEngine;
AppInstance app_instance;

int main() {

    app_instance.initialize();
    App::set_app_instance(&app_instance);


    while (!glfwWindowShouldClose(&App::get_window())) {
        glClearColor(0.2, 0.2, 0.2, 1.0);

        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(&App::get_window());
        glfwPollEvents();
    }

    app_instance.shutdown();

    system("PAUSE");
    return 0;
}

