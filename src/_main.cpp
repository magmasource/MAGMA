/*
 easyMelts (c) 2020 Einari Suikkanen

 Changelog:
 0.1 Initial build
 0.2 Added Melts assimilation for complete Melts experience, plotting, and Excel export capability
 0.2.1 Added macOS support
 0.2.2 Added LiberationSans_Regular.cpp and removed dependence on external fonts
 0.2.3 Added .melts out, melt fraction in plots, additional fixes
 0.2.4 Added .melts input, additional fixes

 */
#include <iostream>
#include <signal.h>

#include "glad.h"
#include "GLFW/glfw3.h"

#include "imgui_opengl.hpp"
#include "imgui_input.hpp"

#include "melts_interface.hpp"

#include "e_utility.hpp"

const int INITIAL_VIEWPORT_X = 1280;
const int INITIAL_VIEWPORT_Y = 720;

extern "C" void handle_abort_signal(int signal_number)
{
    if (signal_number == SIGABRT)
    std::cout << "SIGABRT called by Melts" << std::endl;
    else std::cout << "Aborted by Melts" << std::endl;
    exit(EXIT_FAILURE);

}


int main(int argc, char** argv) {

    std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;

    //initialize GLFW
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
    };
    //set required options for GLFW
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE); //user can resize window


#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(INITIAL_VIEWPORT_X, INITIAL_VIEWPORT_Y, "easyMelts 0.3.0", NULL, NULL);
    glfwMakeContextCurrent(window);

    glfwSetWindowSizeLimits(window, 1024, 768, GLFW_DONT_CARE, GLFW_DONT_CARE); //sets minimum window size 1024x768
    //glfwSetWindowAspectRatio(window, 16, 9);                                  //forces aspect ratio when resizing

    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    //OpenGL context
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        return -1;
    }

    //Initial OpenGL options
    glViewport(0, 0, INITIAL_VIEWPORT_X, INITIAL_VIEWPORT_Y);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0, 0.5, 0.8, 1);

    ImGuiOpenGL gui(window);
    Input::SetUpInput(window, ImGui::GetIO());

    signal(SIGABRT, &handle_abort_signal);

    while (!glfwWindowShouldClose(window)) {

#ifdef DEBUG

        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            std::cout << "GL ERROR: " << error << std::endl;
        }
#endif

        glfwPollEvents();

        Input::UpdateMouse(window);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        gui.UpdateAndRender();

        glfwSwapBuffers(window);
    }

    //Delete GUI-related assets
    gui.DestroyAssets();

    //Terminate GLFW context and free any allocated resources related to GLFW
    glfwTerminate();

    return 0;
}



