/*
 easyMelts (c) 2020 Einari Suikkanen
*/

#ifndef IMGUI_INPUT_HPP
#define IMGUI_INPUT_HPP

#include "GLFW/glfw3.h"
#include "imgui/imgui.h"

class Input {
private:
    Input() {}
    virtual ~Input() {}
public:
    static void SetUpInput(GLFWwindow* window, ImGuiIO &io);

    static const char* GetClipboardText(void* user_data);
    static void SetClipboardText(void* user_data, const char* text);
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

    static void CharCallback(GLFWwindow* window, unsigned int c);
    static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    static void CursorPosCallback(GLFWwindow* window, double xPos, double yPos);
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    static void UpdateMouse(GLFWwindow* window);
};
#endif /* IMGUI_INPUT_HPP */

