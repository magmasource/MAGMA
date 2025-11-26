/*
ImGui input handling
*/

#include "imgui_input.hpp"
#include "imgui/imgui.h"

static bool KEYS[500] = {0};
static bool BUTTONS[32] = {0};

static bool g_MouseJustPressed[5] = {0};


void Input::SetUpInput(GLFWwindow* window, ImGuiIO &io) {
    io.SetClipboardTextFn = SetClipboardText;
    io.GetClipboardTextFn = GetClipboardText;
    io.ClipboardUserData = window;

    glfwSetFramebufferSizeCallback(window, &framebufferSizeCallback);
    glfwSetKeyCallback(window, &keyCallback);
    glfwSetMouseButtonCallback(window, &MouseButtonCallback);
    glfwSetCursorPosCallback(window, &CursorPosCallback);
    glfwSetScrollCallback(window, &MouseScrollCallback);
    glfwSetCharCallback(window, &CharCallback);
}

const char* Input::GetClipboardText(void* user_data) {
    return glfwGetClipboardString((GLFWwindow*) user_data);
}

void Input::SetClipboardText(void* user_data, const char* text) {
    glfwSetClipboardString((GLFWwindow*) user_data, text);
}

void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    ImGuiIO &io = ImGui::GetIO();
    if (action == GLFW_PRESS)
        io.KeysDown[key] = true;
    if (action == GLFW_RELEASE)
        io.KeysDown[key] = false;


    io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
    io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
    io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
    io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

}

void Input::CharCallback(GLFWwindow* window, unsigned int c) {
    ImGuiIO& io = ImGui::GetIO();
    if (c > 0 && c < 0x10000)
        io.AddInputCharacter((unsigned short) c);
}

void Input::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    BUTTONS[button] = action != GLFW_RELEASE;

    if (action == GLFW_PRESS && button >= 0 && button < IM_ARRAYSIZE(g_MouseJustPressed))
        g_MouseJustPressed[button] = true;
}

void Input::MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    ImGuiIO &io = ImGui::GetIO();
    io.MouseWheelH += (float) xoffset;
    io.MouseWheel += (float) yoffset;
}

void Input::CursorPosCallback(GLFWwindow* window, double xPos, double yPos) {

}

void Input::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);

    ImGuiIO &io = ImGui::GetIO();

    int w, h;
    int display_w, display_h;
    glfwGetWindowSize(window, &w, &h);
    glfwGetFramebufferSize(window, &display_w, &display_h);

    io.DisplaySize = ImVec2((float) w, (float) h);
    io.DisplayFramebufferScale = ImVec2(w > 0 ? ((float) display_w / w) : 0, h > 0 ? ((float) display_h / h) : 0);
}

void Input::UpdateMouse(GLFWwindow* window) {
    ImGuiIO &io = ImGui::GetIO();
    for (int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++) {
        io.MouseDown[i] = g_MouseJustPressed[i] || glfwGetMouseButton(window, i) != 0;
        g_MouseJustPressed[i] = false;
    }

    const ImVec2 mouse_position_now = io.MousePos;
    io.MousePos = ImVec2(-FLT_MAX, -FLT_MAX);
    const bool focused = glfwGetWindowAttrib(window, GLFW_FOCUSED) != 0;

    if (focused) {
        if (io.WantSetMousePos) {
            glfwSetCursorPos(window, (double) mouse_position_now.x, (double) mouse_position_now.y);
        } else {
            double mouse_x, mouse_y;
            glfwGetCursorPos(window, &mouse_x, &mouse_y);
            io.MousePos = ImVec2((float) mouse_x, (float) mouse_y);
        }
    }
}